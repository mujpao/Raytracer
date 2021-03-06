#ifndef IMPORTER_H
#define IMPORTER_H

#include "camera.h"
#include "math/mat4.h"

#include <memory>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/matrix4x4.h>

class Scene;
class ShapeList;
class Material;
class Texture;

struct aiScene;
struct aiNode;
struct aiMaterial;
struct aiMesh;

class Importer {
public:
    Importer();

    // Import mesh data from file
    std::shared_ptr<ShapeList> read_objects(
        const std::string& directory, const std::string& filename);

    // Read scene data from file, including lights and cameras if possible
    Scene read_file(const std::string& directory, const std::string& filename);

private:
    void process_node(const aiNode* node, const Mat4& parent_tx = Mat4(1.0));

    void process_mesh(const aiMesh* mesh, const Mat4& tx = Mat4(1.0));

    void read_diffuse_material(const aiMaterial* material);

    Camera get_camera() const;

    static Mat4 ai_mat_to_mat4(const aiMatrix4x4& tx);
    static Vec ai_vec_to_vec(const aiVector3D& v);

    Assimp::Importer m_importer;

    std::shared_ptr<ShapeList> m_shapes;

    std::shared_ptr<Material> m_default_material;
    std::vector<std::shared_ptr<Material>> m_materials;
    std::vector<std::shared_ptr<Texture>> m_normal_maps;

    const aiScene* m_ai_scene = nullptr;

    std::string m_directory, m_filename;
};

#endif
