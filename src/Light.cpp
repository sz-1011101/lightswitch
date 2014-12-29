#include <include/Light.h>

Light::Light(glm::vec3 position, float intensity, glm::vec3 rgb_color)
{
    this->position = position;
    this->intensity = intensity;
    this->rgb_color = rgb_color;
}

Light::~Light()
{
    //Default destructor
}

glm::vec3 Light::GetPosition()
{
    return position;
}

float Light::GetIntensity()
{
    return intensity;
}

glm::vec3 Light::GetRGBColor()
{
    return rgb_color;
}