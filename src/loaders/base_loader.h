#include "model_loader.h"
#include <vector>

class BaseLoader : public ModelLoader {
  private:
    std::vector<int> m_LoadedCoordinates;

  public:
    BaseLoader(std::string pathToFile);
    ~BaseLoader();

    void Load() override;

  private:
    void parseCoordinates(std::vector<glm::vec3> &vertices, std::string line);

    void processVertex(std::vector<glm::vec3> &coordinates, std::vector<glm::vec3> &normals, std::string rawPoint);
};
