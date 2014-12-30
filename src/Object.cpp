#include <include/Object.h>
#include <include/Material.h>
#include <include/Illumination.h>
#include <stdio.h>

Object::Object(glm::vec3 position, Material* material)
{
    this->position = position;
    this->material = material;
}

Object::~Object()
{
    
}

Material* Object::GetMaterial()
{
    return material;
}

glm::vec3 Object::CalculateIntensity(Illumination* illumination, Ray* ray)
{
    return illumination->CalculateIntensity(ray, 0);
}