#include <include/RT.h>
#include <vector>

class Material;
class Ray;
class Light;
class Illumination;

class Object
{
protected:
    glm::vec3 position;
    glm::mat4 modelMatrix;
    glm::mat4 modelMatrixInverse;
    Material* material;
public:
    Object(glm::vec3 position, Material* material);
    virtual ~Object() = 0;
    /* Returns true if ray hits the sphere and writes position into hit
     * and the normal at hit into normal
     */
    virtual bool Intersect(Ray* ray) = 0;
    glm::vec3 CalculateIntensity(Illumination* illumination, Ray* ray); // Takes a illumination model and and a ray
    Material* GetMaterial();
    void SetModelMatrix(glm::mat4 modelMatrix);
};
