#include "RT.h"

class Material
{
private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float phong_exponent;
public:
    Material(glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,float phong_exponent);
    ~Material();
    glm::vec3 GetAmbient();
    glm::vec3 GetDiffuse();
    glm::vec3 GetSpecular();
    float GetPhong_exponent();
};