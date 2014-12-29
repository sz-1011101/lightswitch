#include <include/Material.h>

Material::Material(glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,float phong_exponent)
{
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->phong_exponent = phong_exponent;
}

Material::~Material()
{
    
}

glm::vec3 Material::GetAmbient()
{
    return ambient;
}
glm::vec3 Material::GetDiffuse()
{
    return diffuse;
}
glm::vec3 Material::GetSpecular()
{
    return specular;
}
float Material::GetPhong_exponent()
{
    return phong_exponent;
}