#include "RT.h"
#include <include/Intersection.h>

class Ray
{
private:
   glm::vec3 origin;
   glm::vec3 direction;
   Intersection intersection;
public:
    Ray(glm::vec3 origin, glm::vec3 direction);
    ~Ray();
    void SetOrigin(glm::vec3 origin);
    void SetDirection(glm::vec3 direction);
    void SetIntersection(Intersection intersection);
    Intersection GetIntersection();
    
    glm::vec3 GetOrigin();
    glm::vec3 GetDirection();
    
};