#include "RT.h"

#ifndef _OBJECT_H
#define _OBJECT_H
#include "Object.h"
#endif

#include <vector>

class Light;
class Ray;
class Material;
class illumination;

class Plane : public Object
{
private:
    glm::vec3 normal;
public:
    Plane(glm::vec3 position, glm::vec3 normal, Material* material);
    ~Plane();
    //Derived
    virtual bool Intersect(Ray* ray);
};
