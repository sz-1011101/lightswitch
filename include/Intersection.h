#include "RT.h"

class Sphere;

struct Intersection
{
    glm::vec3 hit;
    glm::vec3 normal;
    glm::vec3 reflection;
    bool valid;
    float length;
    Sphere* sphere;
};