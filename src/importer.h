#ifndef IMPORTER_H
#define IMPORTER_H

#include "math/mat4.h"

#include <memory>
#include <vector>

#include <assimp/matrix4x4.h>

class Scene;
class ShapeList;
class aiScene;
class aiNode;
class aiMesh;
class Material;

class Importer {
public:
    Importer();

    // Imports mesh data from file
    std::shared_ptr<ShapeList> read_objects(
        const std::string& directory, const std::string& filename);

    // Reads data from file, including lights and cameras if possible, and
    // constructs a scene
    // TODO
    // Scene read_file(const std::string& file_name);

private:
    void process_node(const aiNode* node, const Mat4& parent_tx = Mat4(1.0));

    void process_mesh(const aiMesh* mesh, const Mat4& tx = Mat4(1.0));

    static Mat4 ai_mat_to_mat4(const aiMatrix4x4& tx);

    std::shared_ptr<ShapeList> m_shapes;
    std::shared_ptr<Material> m_default_material;
    std::vector<std::shared_ptr<Material>> m_materials;

    const aiScene* m_ai_scene = nullptr;
};

#endif
