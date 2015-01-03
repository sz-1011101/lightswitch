#include <include/Plane.h>
#include <include/Ray.h>
#include <include/Light.h>
#include <include/Material.h>
#include <include/Illumination.h>

Plane::Plane(glm::vec3 position, glm::vec3 normal, Material* material) : Object(position, material)
{
	this->normal = normalize(normal);
}

Plane::~Plane()
{
    //default destructor
}

bool Plane::Intersect(Ray* ray)
{
    glm::vec3 d = ray->GetDirection();
    glm::vec3 e = ray->GetOrigin();
    
    if (glm::dot(normal, d)==0)
    {
        return false; //Plane parallel to the ray
    }
    else
    {
        float t = glm::dot(normal,position-e)/dot(normal,d);
        
        if (t>=0)
        {
            Intersection intersection;
            intersection.hit = e + (t*d);
            intersection.normal = normal;
            intersection.object = this;

            ray->SetIntersection(intersection);

            return true;
        }
        else
        {
            return false;
        }
        
    }
}
