#include<include/HitCheck.h>
#include<include/Sphere.h>
#include<include/Ray.h>

bool HitCheck::CheckForIntersection(Ray* ray, std::vector<Sphere*>* spheres)
{
        for (std::vector<Sphere*>::iterator itr = spheres->begin(); itr!=spheres->end(); itr++)
    {
        (*itr)->Intersect(ray);

    }
        
    return ray->GetIntersection().valid;
}