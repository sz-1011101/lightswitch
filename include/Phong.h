#include "Illumination.h"

class Phong : public Illumination
{
private:
    glm::vec3 sky;
    bool use_sky_color; //Set this to use the skys color when illuminating
public:
    Phong(Scene* scene, int maximum_recursion_depth, float epsilon, glm::vec3 sky, bool use_sky_color);
    ~Phong();
    virtual glm::vec3 CalculateIntensity(Ray* ray, int recursion_depth); 
    glm::vec3 GetSkyColor();
};