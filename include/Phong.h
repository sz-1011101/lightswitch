#include "Illumination.h"

class Phong : public Illumination
{
private:
public:
    Phong(Scene* scene, int maximum_recursion_depth, float epsilon);
    ~Phong();
    virtual glm::vec3 CalculateIntensity(Ray* ray, int recursion_depth); 
};