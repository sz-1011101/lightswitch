#include <include/Sphere.h>
#include <include/Ray.h>
#include <include/Light.h>
#include <include/Material.h>
#include <include/Illumination.h>

Sphere::Sphere(glm::vec3 position, float radius, Material* material) : Object(position, material)
{
    this->radius = radius;
}

Sphere::~Sphere()
{
    //default destructor
}

bool Sphere::Intersect(Ray* ray)
{
    glm::vec3 d = ray->GetDirection();
    float a = glm::dot(d,d);
    glm::vec3 e = ray->GetOrigin();
    float c = glm::dot((e-position),(e-position))-(radius * radius);
    
    float b = 2.0f * glm::dot(d,(e-position));
    float discriminant = (b * b) -(4 * a * c);
    
    
    if (discriminant<0) //there is no intersection between ray and sphere
    {
        return false;
    }
    else //one or more intersections
    {
        
        float t_1 = (-b+sqrt(discriminant))/(2*a);
        float t_2 = (-b-sqrt(discriminant))/(2*a);
        float t;
        
        Intersection intersection;
        
        if (t_1<t_2 && t_1>0)
        {
            t = t_1;
        }
        else if (t_2<=t_1 && t_2>0)
        {
            t = t_2;
        }
        else
        {
            return false;
        }
        
        intersection.hit = e+(t*d);
        intersection.normal = glm::normalize(intersection.hit-position);
        intersection.object = this;
        
        ray->SetIntersection(intersection);
        return true;
        
    }
    
}
