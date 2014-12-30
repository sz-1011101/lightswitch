#include <include/Phong.h>
#include <include/Scene.h>
#include <include/Ray.h>
#include <include/HitCheck.h>
#include <include/Object.h>
#include <include/Material.h>
#include <include/Light.h>

Phong::Phong(Scene* scene, int maximum_recursion_depth, float epsilon) : Illumination(scene, maximum_recursion_depth, epsilon)
{
    this->scene = scene;
    this->maximum_recursion_depth = maximum_recursion_depth;
    this->epsilon = epsilon;
}

Phong::~Phong()
{
    
}

glm::vec3 Phong::CalculateIntensity(Ray* ray, int recursion_depth)
{
    //TODO make this readable
    std::vector<Light*>* lights = scene->GetLights();
    std::vector<Object*>* objects = scene->GetObjects();
    Object* current_object = ray->GetIntersection().object;
      
    glm::vec3 complete_intensity=glm::vec3(0);
    glm::vec3 ambient_term;
    glm::vec3 diff_term;
    glm::vec3 spec_term;
    glm::vec3 ambient = current_object->GetMaterial()->GetAmbient();
    glm::vec3 specular = current_object->GetMaterial()->GetSpecular();
    glm::vec3 diffuse = current_object->GetMaterial()->GetDiffuse();
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
        spec_term = (specular*i_l)*((float)pow(glm::dot(r,v),current_object->GetMaterial()->GetPhong_exponent()));
        
        float distance_to_light = glm::length(ray->GetIntersection().hit-(*itr)->GetPosition());
        
        Ray* shadow_ray = new Ray(ray->GetIntersection().hit+(n*epsilon),l);
        
        /* A shadow ray is send from the hit position towards the light.
         * If it hits something the light can't illuminate the hit position. */
        

        if (HitCheck::CheckForIntersection(shadow_ray, objects))
        {
            complete_intensity += ambient_term/(distance_to_light*distance_to_light);
        }
        else
        {
            complete_intensity += (ambient_term + diff_term + spec_term)/(distance_to_light*distance_to_light);
        }
        
        delete shadow_ray;
        shadow_ray = NULL; 
        
        /* Recursive reflexion calculation, just sends another ray off in the reflexion direction of the view vector v
         * and adds the light of this reflexion */
        
        
        glm::vec3 v_r = glm::normalize((2.0f*glm::dot(n,v)*n)-v);
               
        if (recursion_depth<maximum_recursion_depth)
        {
            Ray* reflexion_ray = new Ray(ray->GetIntersection().hit+(n*epsilon),v_r);
            
            if (HitCheck::CheckForIntersection(reflexion_ray, objects))
            {
                Object* reflexion_hit_object = reflexion_ray->GetIntersection().object;
                glm::vec3 reflected_intens = reflexion_hit_object->CalculateIntensity(this, reflexion_ray);
                float distance_to_reflexion = glm::length(reflexion_ray->GetOrigin()-reflexion_ray->GetIntersection().hit);
                complete_intensity += (reflected_intens/(recursion_depth+1.0f))*current_object->GetMaterial()->GetSpecular()/(distance_to_reflexion*distance_to_reflexion);
            }
            
            delete reflexion_ray;
            reflexion_ray = NULL; 
        } 
 
    }

    return complete_intensity;
}