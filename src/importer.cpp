#include "importer.h"

#include "materials/diffusematerial.h"
#include "scene.h"
#include "shapes/shapelist.h"
#include "shapes/triangle.h"
#include "textures/imagetexture.h"
#include "utils.h"

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <iostream>
#include <queue>

Importer::Importer()
    : m_shapes(std::make_shared<ShapeList>()),
      m_default_material(
          std::make_shared<DiffuseMaterial>(Vec(0.5, 0.5, 0.5))) {}

std::shared_ptr<ShapeList> Importer::read_objects(
    const std::string& directory, const std::string& filename) {
    std::cout << "Reading objects from file: " << directory + filename
              << std::endl;

    m_directory = directory;
    m_filename = filename;

    m_ai_scene = m_importer.ReadFile(directory + filename,
        aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs
            | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);

    if (!m_ai_scene) {
        std::cout << "can't read scene" << std::endl;
        return nullptr;
    }

    for (unsigned int i = 0; i < m_ai_scene->mNumMaterials; ++i) {
        const aiMaterial* material = m_ai_scene->mMaterials[i];

        read_diffuse_material(material);

        if (material->GetTextureCount(aiTextureType_NORMALS) > 0) {
            aiString str;
            material->GetTexture(aiTextureType_NORMALS, 0, &str);
            m_normal_maps.push_back(
                std::make_shared<ImageTexture>(directory + str.C_Str(), true));

        } else {
            m_normal_maps.push_back(nullptr);
        }
    }

    process_node(m_ai_scene->mRootNode);

    return m_shapes;
}

Scene Importer::read_file(
    const std::string& directory, const std::string& filename) {
    std::cout << "Reading scene from file: " << directory + filename
              << std::endl;

    read_objects(directory, filename);

    // TODO lights

    return Scene(m_shapes, std::vector<std::shared_ptr<Light>>(), get_camera());
}

void Importer::process_node(const aiNode* node, const Mat4& parent_tx) {

    Mat4 tx = parent_tx * Importer::ai_mat_to_mat4(node->mTransformation);

    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        process_mesh(m_ai_scene->mMeshes[node->mMeshes[i]], tx);
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        process_node(node->mChildren[i], tx);
    }
}

void Importer::process_mesh(const aiMesh* mesh, const Mat4& tx) {

    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        std::array<Vec, 3> positions;
        std::array<std::pair<double, double>, 3> texcoords;
        for (unsigned int j = 0; j < 3; ++j) {
            for (unsigned int k = 0; k < 3; ++k) {
                positions[j][k]
                    = mesh->mVertices[mesh->mFaces[i].mIndices[j]][k];
            }

            positions[j][3] = 1.0;

            if (mesh->HasTextureCoords(0)) {
                texcoords[j].first
                    = mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].x;
                texcoords[j].second
                    = mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].y;
            }
        }

        if (m_normal_maps[mesh->mMaterialIndex]) {
            Vec e1 = positions[1] - positions[0];
            Vec e2 = positions[2] - positions[1];
            double du1 = texcoords[1].first - texcoords[0].first;
            double dv1 = texcoords[1].second - texcoords[0].second;
            double du2 = texcoords[2].first - texcoords[1].first;
            double dv2 = texcoords[2].second - texcoords[1].second;

            if (Utils::is_small(du1 * dv2 - du2 * dv1)) {
                du1 = dv2 = 1.0;
                du2 = dv1 = 0.0;
            }

            double inv_det = 1.0 / (du1 * dv2 - du2 * dv1);

            Vec tangent;
            for (unsigned int j = 0; j < 3; ++j) {
                tangent[j] = inv_det * (dv2 * e1[j] - dv1 * e2[j]);
            }

            tangent = Vec::normalize(tangent);

            m_shapes->add(
                std::make_shared<Triangle>(Vertex{ positions[0], texcoords[0] },
                    Vertex{ positions[1], texcoords[1] },
                    Vertex{ positions[2], texcoords[2] },
                    m_materials[mesh->mMaterialIndex], tx, true, tangent,
                    m_normal_maps[mesh->mMaterialIndex]));
        } else {

            m_shapes->add(
                std::make_shared<Triangle>(Vertex{ positions[0], texcoords[0] },
                    Vertex{ positions[1], texcoords[1] },
                    Vertex{ positions[2], texcoords[2] },
                    m_materials[mesh->mMaterialIndex], tx));
        }
    }
}

void Importer::read_diffuse_material(const aiMaterial* material) {
    if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        // Just support one diffuse texture for now
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &str);

        std::shared_ptr<Texture> texture
            = std::make_shared<ImageTexture>(m_directory + str.C_Str(), true);

        m_materials.push_back(std::make_shared<DiffuseMaterial>(texture));

    } else {
        m_materials.push_back(m_default_material);
    }
}

Camera Importer::get_camera() const {
    if (m_ai_scene->mNumCameras == 0) {
        std::cout << "No camera found in scene.\n";
        return Camera();
    }

    const aiCamera* camera = m_ai_scene->mCameras[0];
    aiString camera_name = camera->mName;

    std::queue<std::pair<const aiNode*, aiMatrix4x4>> q;
    q.push({ m_ai_scene->mRootNode, m_ai_scene->mRootNode->mTransformation });

    while (!q.empty()) {
        const aiNode* node = q.front().first;
        aiMatrix4x4 tx = q.front().second;
        q.pop();

        if (node->mName == camera_name) {
            Mat4 transform = ai_mat_to_mat4(tx);
            Vec eye
                = transform * Vec::to_point(ai_vec_to_vec(camera->mPosition));
            Vec center = eye
                + Vec::to_point(
                    transform * Vec::to_vec(ai_vec_to_vec(camera->mLookAt)));
            Vec up = transform * Vec::to_vec(ai_vec_to_vec(camera->mUp));

            double aspect = 16.0 / 9.0;
            double fovy = Utils::rad2deg(
                2.0 * std::atan(std::tan(camera->mHorizontalFOV) / aspect));

            return Camera(eye, center, up, fovy, aspect);
        }

        for (unsigned int i = 0; i < node->mNumChildren; ++i) {
            q.push({ node->mChildren[i],
                tx * node->mChildren[i]->mTransformation });
        }
    }

    std::cout << "No camera found in scene.\n";
    return Camera();
}

Mat4 Importer::ai_mat_to_mat4(const aiMatrix4x4& tx) {
    Mat4 result;
    for (unsigned int i = 0; i < 4; ++i) {
        for (unsigned int j = 0; j < 4; ++j) {
            result(i, j) = tx[i][j];
        }
    }

    return result;
}

Vec Importer::ai_vec_to_vec(const aiVector3D& v) {
    Vec result;
    for (unsigned int i = 0; i < 3; ++i) {
        result[i] = v[i];
    }

    return result;
}
