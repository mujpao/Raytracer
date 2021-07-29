#include "importer.h"

#include "materials/diffusematerial.h"
#include "shapes/shapelist.h"
#include "shapes/triangle.h"
#include "textures/imagetexture.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <iostream>

Importer::Importer()
    : m_shapes(std::make_shared<ShapeList>()),
      m_default_material(
          std::make_shared<DiffuseMaterial>(Vec(0.5, 0.5, 0.5))) {}

std::shared_ptr<ShapeList> Importer::read_objects(
    const std::string& directory, const std::string& filename) {
    Assimp::Importer importer;

    m_ai_scene = importer.ReadFile(directory + filename,
        aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs
            | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);

    if (!m_ai_scene) {
        std::cout << "can't read scene" << std::endl;
        return nullptr;
    }

    for (unsigned int i = 0; i < m_ai_scene->mNumMaterials; ++i) {

        if (m_ai_scene->mMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE)
            > 0) {
            // Just support one diffuse texture for now
            aiString str;
            m_ai_scene->mMaterials[i]->GetTexture(
                aiTextureType_DIFFUSE, 0, &str);

            std::cout << str.C_Str() << std::endl;

            std::shared_ptr<Texture> texture
                = std::make_shared<ImageTexture>(directory + str.C_Str(), true);

            m_materials.push_back(std::make_shared<DiffuseMaterial>(texture));

        } else {
            m_materials.push_back(m_default_material);
        }
    }

    process_node(m_ai_scene->mRootNode);

    return m_shapes;
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

        m_shapes->add(
            std::make_shared<Triangle>(Vertex{ positions[0], texcoords[0] },
                Vertex{ positions[1], texcoords[1] },
                Vertex{ positions[2], texcoords[2] },
                m_materials[mesh->mMaterialIndex], tx));
    }

    // std::cout << mesh->HasNormals() << '\n';
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
