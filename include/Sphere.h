#include "RT.h"
#include <vector>

struct Intersection;

class Light;
class Ray;
class Material;

class Sphere
{
private:
    float radius;
    glm::vec3 position;
    Material* material;
    const float EPSILON_SHADOW = 0.00001f; //Used to put the origin of the shadowray above the sphere
public:
    Sphere(glm::vec3 position, float radius, Material* material);
    ~Sphere();
    /* Returns true if ray hits the sphere and writes position into hit
     * and the normal at hit into normal
     */
    bool Intersect(Ray* ray);
    glm::vec3 CalculateIntensity(Ray* ray, std::vector<Light*>* lights, std::vector<Sphere*>* spheres); // Light with phong
};