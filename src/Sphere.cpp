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
    glm::vec3 d_ws = ray->GetDirection();
    
    glm::vec3 e_ws = ray->GetOrigin();
    glm::vec3 e = glm::vec3(modelMatrixInverse*glm::vec4(e_ws, 1.0));
    glm::vec3 e_ws_plus_d_ws = e_ws + (d_ws);
    glm::vec3 e_plus_d = glm::vec3(modelMatrixInverse*glm::vec4(e_ws_plus_d_ws, 1.0));
    glm::vec3 d = e_plus_d - e;
    
    float a = glm::dot(d,d);
    float b = 2.0f * glm::dot(d, (e));
    float c = glm::dot((e),(e)) - (1.0);
    
    float discriminant = (b * b) - (4 * a * c);
    
    
    if (discriminant<0) //there is no intersection between ray and sphere
    {
        return false;
    }
    else //one or more intersections
    {
        float t_1 = (-b + sqrt(discriminant))/(2*a);
        float t_2 = (-b - sqrt(discriminant))/(2*a);
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
        
        intersection.hit = glm::vec3(modelMatrix*glm::vec4((e+(t*d)),1.0));
        intersection.normal = glm::normalize(e + (t*d));
        intersection.object = this;
        
        ray->SetIntersection(intersection);
        return true;
    }
    
}
