#include "RT.h"
#include <vector>

class Ray;
class Scene;

class Illumination
{
protected:
    Scene* scene;
    int maximum_recursion_depth;
    float epsilon; //Used to put the origin of the shadowray/reflexionray above the object
public:
    Illumination(Scene* scene, int maximum_recursion_depth, float epsilon);
    virtual ~Illumination() = 0;
    virtual glm::vec3 CalculateIntensity(Ray* ray, int recursion_depth) = 0;
    virtual glm::vec3 GetSkyColor() = 0; //This function deterimens the color in case no object got hit by a ray
};