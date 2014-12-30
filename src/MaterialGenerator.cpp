#include <include/MaterialGenerator.h>
#include <include/Material.h>

MaterialGenerator::MaterialGenerator()
{
    
}

MaterialGenerator::~MaterialGenerator()
{
    for (std::vector<Material*>::iterator itr = materials.begin(); itr!=materials.end();itr++)
    {
        delete (*itr);
    }
}

Material* MaterialGenerator::GenMaterial(glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,float phong_exponent)
{
    Material* material = new Material(ambient, diffuse, specular, phong_exponent);
    materials.push_back(material);
    return  material;
}