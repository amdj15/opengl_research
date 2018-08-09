#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "model_loader.h"

class AssimpLoader : public ModelLoader {
  public:
    AssimpLoader(std::string pathToFile, std::string Directory);
    ~AssimpLoader();

    void Load() override;

  private:
    void processMesh(const aiMesh* mesh, const aiScene *scene);
    void processNode(const aiNode* node, const aiScene *scene);
    bool loadTexture(const aiMaterial *material, aiTextureType type, std::string typeName, std::map<std::string, MeshTexture> &textures, unsigned int slot);
    MeshMaterials processMaterials(aiMaterial *material);
};
