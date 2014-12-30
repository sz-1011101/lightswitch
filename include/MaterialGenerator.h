#include "RT.h"
#include <vector>

class Material;

class MaterialGenerator
{
private:
    std::vector<Material*> materials;
public:
    MaterialGenerator();
    ~MaterialGenerator();
    Material* GenMaterial(glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,float phong_exponent);
};