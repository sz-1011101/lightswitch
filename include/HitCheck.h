#include <vector>

class Ray;
class Object;

class HitCheck
{
private:
public:
    //Returns true if a collision happend between the given spheres and ray
    static bool CheckForIntersection(Ray* ray, std::vector<Object*>* objects);
};