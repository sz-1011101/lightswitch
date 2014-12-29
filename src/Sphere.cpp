#include <include/Sphere.h>
#include <include/Ray.h>
#include <include/Light.h>
#include <include/Material.h>
#include <include/HitCheck.h>

Sphere::Sphere(glm::vec3 position, float radius, Material* material)
{
    this->position = position;
    this->radius = radius;
    this->material = material;
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
        intersection.valid = true;
        
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
        intersection.sphere = this;
        
        ray->SetIntersection(intersection);
        return true;
        
    }
    
}

    
glm::vec3 Sphere::CalculateIntensity(Ray* ray, std::vector<Light*>* lights, std::vector<Sphere*>* spheres)
{
    //TODO make this readable
    glm::vec3 complete_intensity=glm::vec3(0);
    glm::vec3 ambient_term;
    glm::vec3 diff_term;
    glm::vec3 spec_term;
    glm::vec3 ambient = this->material->GetAmbient();
    glm::vec3 specular = this->material->GetSpecular();
    glm::vec3 diffuse = this->material->GetDiffuse();
    glm::vec3 n = ray->GetIntersection().normal;
    glm::vec3 l;
    glm::vec3 r;
    glm::vec3 v;
    glm::vec3 i_l;
    
    for (std::vector<Light*>::iterator itr = (*lights).begin(); itr != (*lights).end(); itr++)
    {
        l = glm::normalize((*itr)->GetPosition() - ray->GetIntersection().hit); //vector from hit to light
        r = glm::normalize((2.0f*glm::dot(n,l)*n)-l); //Calculate the perfect reflexion from the light on the sphere
        v = glm::normalize(-ray->GetDirection());
        i_l = (*itr)->GetIntensity()*(*itr)->GetRGBColor();
        
        ambient_term = ambient*i_l;
        diff_term = (diffuse*i_l)*glm::dot(n,l);
        spec_term =  (specular*i_l)*((float)pow(glm::dot(r,v),this->material->GetPhong_exponent()));
        
        float distance_to_light = glm::length(ray->GetIntersection().hit-(*itr)->GetPosition());
        
        Ray* shadow_ray = new Ray(ray->GetIntersection().hit+(n*EPSILON_SHADOW),l);
        
        if (HitCheck::CheckForIntersection(shadow_ray, spheres))
        {
            complete_intensity += ambient_term/(distance_to_light*distance_to_light);
        }
        else
        {
            complete_intensity += (ambient_term + diff_term + spec_term)/(distance_to_light*distance_to_light);
        }
        
        delete shadow_ray;
        
        shadow_ray = NULL;
        
        
        
    }
    
   
    
    return complete_intensity;
}