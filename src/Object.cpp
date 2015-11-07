#include <include/Object.h>
#include <include/Material.h>
#include <include/Illumination.h>
#include <stdio.h>

Object::Object(glm::vec3 position, Material* material)
{
    this->position = position;
    this->material = material;
    
    this->modelMatrix = glm::mat4(1.0);
    this->modelMatrix[3]= glm::vec4(position,1.0);
    //this->modelMatrixInverse[3] = glm::vec4(-position,1.0);
    this->modelMatrixInverse = glm::inverse(modelMatrix);
    //Matrix output
    /*
    puts("--------------");
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            printf("%f ", modelMatrixInverse[j][i]);
        }
        printf("\n");
    }
    */
    
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

void Object::SetModelMatrix(glm::mat4 modelMatrix)
{
    this->modelMatrix = modelMatrix;
    modelMatrixInverse = glm::inverse(modelMatrix);
}
