#include<include/HitCheck.h>
#include<include/Object.h>
#include<include/Ray.h>

bool HitCheck::CheckForIntersection(Ray* ray, std::vector<Object*>* objects)
{
    for (std::vector<Object*>::iterator itr = objects->begin(); itr!=objects->end(); itr++)
    {
        (*itr)->Intersect(ray);

    }
    return ray->GetIntersection().valid;
}


bool HitCheck::CheckForIntersection(Ray* ray, std::vector<Object*>* objects, Object* ignore)
{
    for (std::vector<Object*>::iterator itr = objects->begin(); itr!=objects->end(); itr++)
    {
        if ((*itr)!=ignore)
        {
            (*itr)->Intersect(ray);
        }

    }
    return ray->GetIntersection().valid;
}
