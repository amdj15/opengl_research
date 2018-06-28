#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "model_loader.h"

class AssimpLoader : public ModelLoader {
  public:
    AssimpLoader(std::string pathToFile);
    ~AssimpLoader();

    void Load() override;

  private:
    void processMesh(const aiMesh* mesh);
};
