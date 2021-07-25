#include "camera.h"
#include "image.h"
#include "materials/diffusematerial.h"
#include "raytracer.h"
#include "scene.h"
#include "shapes/shapelist.h"
#include "shapes/triangle.h"

#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/postprocess.h> // Post processing flags
#include <assimp/scene.h> // Output data structure

#include <iostream>

int main() {
    Assimp::Importer importer;

    std::string file("/home/mujpao/Documents/3d/defaultcube.obj");

    const aiScene* ai_scene = importer.ReadFile(file,
        aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs
            | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);

    if (!ai_scene) {
        std::cout << "can't read scene" << std::endl;
    }

    std::cout << ai_scene->HasMeshes() << '\n';
    std::cout << ai_scene->HasMaterials() << '\n';
    std::cout << ai_scene->HasLights() << '\n';
    std::cout << ai_scene->HasTextures() << '\n';
    std::cout << ai_scene->HasCameras() << '\n';
    std::cout << ai_scene->HasAnimations() << '\n';

    std::string outfile("importexample.png");

    int width = 400;
    double aspect = 16.0 / 9.0;
    Camera camera(Vec(-4.0, 0.5, 2.8), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
        45.0, aspect);

    auto diffuse_material
        = std::make_shared<DiffuseMaterial>(Vec(0.5, 0.5, 0.5));

    std::shared_ptr<ShapeList> shapes = std::make_shared<ShapeList>();

    for (unsigned int i = 0; i < ai_scene->mNumMeshes; ++i) {
        std::cout << "mesh " << i << '\n';
        std::cout << ai_scene->mMeshes[i]->HasPositions() << '\n';
        for (unsigned int j = 0; j < ai_scene->mMeshes[i]->mNumVertices; ++j) {
            std::cout << "position " << j << " : "
                      << ai_scene->mMeshes[i]->mVertices[j][0] << ", "
                      << ai_scene->mMeshes[i]->mVertices[j][1] << ", "
                      << ai_scene->mMeshes[i]->mVertices[j][2] << ">\n";
        }
        std::cout << ai_scene->mMeshes[i]->HasFaces() << '\n';
        for (unsigned int j = 0; j < ai_scene->mMeshes[i]->mNumFaces; ++j) {
            std::cout << "Face: " << ai_scene->mMeshes[i]->mFaces[j].mNumIndices
                      << '\n';
            std::cout << "Vertices: " << '\n';
            std::cout << ai_scene->mMeshes[i]->mFaces[j].mIndices[0] << ' ';
            std::cout << ai_scene->mMeshes[i]->mFaces[j].mIndices[1] << ' ';
            std::cout << ai_scene->mMeshes[i]->mFaces[j].mIndices[2] << ' ';

            std::array<Vec, 3> vertices;
            for (unsigned int k = 0; k < 3; ++k) {
                for (unsigned int l = 0; l < 3; ++l) {
                    vertices[k][l]
                        = ai_scene->mMeshes[i]->mVertices
                              [ai_scene->mMeshes[i]->mFaces[j].mIndices[k]][l];
                }

                vertices[k][3] = 1.0;
            }

            std::cout << "triangle : ";
            std::cout << vertices[0] << ", " << vertices[1] << ", "
                      << vertices[2] << std::endl;

            shapes->add(std::make_shared<Triangle>(
                vertices[0], vertices[1], vertices[2], diffuse_material));
        }

        std::cout << ai_scene->mMeshes[i]->HasNormals() << '\n';
        std::cout << ai_scene->mMeshes[i]->HasTextureCoords(0) << '\n';
    }

    Raytracer raytracer(5, 10);
    raytracer.set_background_color(Vec(0.5, 0.7, 1.0));

    Scene scene(shapes);

    Image image = raytracer.raytrace(camera, scene, width, aspect, true);
    image.save(outfile);

    return 0;
}
