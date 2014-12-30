#include "RT.h"
#include "Object.h"
#include <vector>

class Light;
class Ray;
class Material;
class illumination;

class Sphere : public Object
{
private:
    float radius;
public:
    Sphere(glm::vec3 position, float radius, Material* material);
    ~Sphere();
    //Derived
    virtual bool Intersect(Ray* ray);
};