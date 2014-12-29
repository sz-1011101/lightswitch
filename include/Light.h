#include "RT.h"

class Light
{
private:
    glm::vec3 position;
    float intensity;
    glm::vec3 rgb_color;
public:
    Light(glm::vec3 position, float intensity, glm::vec3 rgb_color);
    ~Light();
    glm::vec3 GetPosition();
    float GetIntensity();
    glm::vec3 GetRGBColor();
    
};