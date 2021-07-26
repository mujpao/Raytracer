#include "importer.h"

#include "materials/diffusematerial.h"
#include "shapes/shapelist.h"
#include "shapes/triangle.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <iostream>

Importer::Importer()
    : m_shapes(std::make_shared<ShapeList>()),
      m_default_material(
          std::make_shared<DiffuseMaterial>(Vec(0.5, 0.5, 0.5))) {
    // TODO read materials from file
}

std::shared_ptr<ShapeList> Importer::read_objects(const std::string& filename) {
    Assimp::Importer importer;

    m_ai_scene = importer.ReadFile(filename,
        aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs
            | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);

    if (!m_ai_scene) {
        std::cout << "can't read scene" << std::endl;
        return nullptr;
    }

    // std::cout << "root name: " << m_ai_scene->mRootNode->mName.C_Str() <<
    // '\n'; std::cout << "num children: " <<
    // m_ai_scene->mRootNode->mNumChildren
    //           << '\n';

    process_node(m_ai_scene->mRootNode);

    return m_shapes;
}

void Importer::process_node(const aiNode* node, const Mat4& parent_tx) {

    Mat4 tx = parent_tx * Importer::ai_mat_to_mat4(node->mTransformation);

    // std::cout << "Processing node " << node->mName.C_Str() << std::endl;

    // std::cout << "relative tx:\n"
    //           << Importer::ai_mat_to_mat4(node->mTransformation) <<
    //           std::endl;

    // std::cout << "tx:\n" << tx << std::endl;

    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        process_mesh(m_ai_scene->mMeshes[node->mMeshes[i]], tx);
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        process_node(node->mChildren[i], tx);
    }
}

void Importer::process_mesh(const aiMesh* mesh, const Mat4& tx) {
    // std::cout << mesh->HasPositions() << '\n';
    // for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {
    //     std::cout << "position " << j << " : " << mesh->mVertices[j][0] << ",
    //     "
    //               << mesh->mVertices[j][1] << ", " << mesh->mVertices[j][2]
    //               << ">\n";
    // }
    // std::cout << mesh->HasFaces() << '\n';
    for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
        // std::cout << "Face: " << mesh->mFaces[j].mNumIndices << '\n';
        // std::cout << "Vertices: " << '\n';
        // std::cout << mesh->mFaces[j].mIndices[0] << ' ';
        // std::cout << mesh->mFaces[j].mIndices[1] << ' ';
        // std::cout << mesh->mFaces[j].mIndices[2] << ' ';

        std::array<Vec, 3> vertices;
        for (unsigned int k = 0; k < 3; ++k) {
            for (unsigned int l = 0; l < 3; ++l) {
                vertices[k][l]
                    = mesh->mVertices[mesh->mFaces[j].mIndices[k]][l];
            }

            vertices[k][3] = 1.0;
        }

        // std::cout << "triangle : ";
        // std::cout << vertices[0] << ", " << vertices[1] << ", " <<
        // vertices[2]
        //           << std::endl;

        m_shapes->add(std::make_shared<Triangle>(
            vertices[0], vertices[1], vertices[2], m_default_material, tx));
    }

    // std::cout << mesh->HasNormals() << '\n';
    // std::cout << mesh->HasTextureCoords(0) << '\n';
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
