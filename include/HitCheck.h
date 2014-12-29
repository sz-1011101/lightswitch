#include <vector>
class Ray;
class Sphere;

class HitCheck
{
private:
public:
    static bool CheckForIntersection(Ray* ray, std::vector<Sphere*>* spheres);
    
};