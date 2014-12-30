#include <include/Illumination.h>

Illumination::Illumination(Scene* scene, int maximum_recursion_depth, float epsilon)
{
    this->scene = scene;
    this->maximum_recursion_depth = maximum_recursion_depth;
    this->epsilon = epsilon;
}

Illumination::~Illumination()
{
    
}