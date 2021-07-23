#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/postprocess.h> // Post processing flags
#include <assimp/scene.h> // Output data structure

#include <iostream>

int main() {
    Assimp::Importer importer;

    std::string file("myfile");

    const aiScene* scene = importer.ReadFile(file,
        aiProcess_CalcTangentSpace | aiProcess_Triangulate
            | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

    // If the import failed, report it
    if (!scene) {
        std::cout << "can't read scene" << std::endl;
    }

    std::cout << "here" << std::endl;

    // Now we can access the file's contents.
    // DoTheSceneProcessing(scene);

    return 0;
}
