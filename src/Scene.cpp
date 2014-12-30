#include <include/Scene.h>
#include <include/Light.h>
#include <include/Object.h>

Scene::Scene()
{
    
}

Scene::~Scene()
{
    for (std::vector<Object*>::iterator itr = objects.begin(); itr!=objects.end();itr++)
    {
        delete (*itr);
    }
    
    for (std::vector<Light*>::iterator itr = lights.begin(); itr!=lights.end();itr++)
    {
        delete (*itr);
    }
}

bool Scene::AddObject(Object* object)
{
    objects.push_back(object);
    return true;
}

bool Scene::AddLight(Light* light)
{
    lights.push_back(light);
    return true;
}

std::vector<Object*>* Scene::GetObjects()
{
    return &objects;
}

std::vector<Light*>* Scene::GetLights()
{
    return &lights;
}