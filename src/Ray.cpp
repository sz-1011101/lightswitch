#include <include/Ray.h>

Ray::Ray(glm::vec3 origin, glm::vec3 direction)
{
    this->origin = origin;
    this->direction = direction;
    intersection.valid = false;
}

Ray::~Ray()
{
    //default destructor
}

void Ray::SetOrigin(glm::vec3 origin)
{
    this->origin = origin;
}

void Ray::SetDirection(glm::vec3 direction)
{   
    this->direction = glm::normalize(direction);
}

glm::vec3 Ray::GetOrigin()
{
    return origin;
}

glm::vec3 Ray::GetDirection()
{
    return direction;
}

void Ray::SetIntersection(Intersection intersection)
{
    if (glm::length(this->intersection.hit-origin)>glm::length(intersection.hit-origin))
    {
        this->intersection = intersection;
    }
}

Intersection Ray::GetIntersection()
{
    return intersection;
}