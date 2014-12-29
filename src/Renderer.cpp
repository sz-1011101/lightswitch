#include <include/Renderer.h>
#include <include/HitCheck.h>
#include <include/Ray.h>
#include <include/Sphere.h>
#include "Light.h"
#include <vector>

Renderer* Renderer::instance = NULL;

Renderer::Renderer()
{
    //default constructor
}

Renderer::~Renderer()
{
    if (instance!=NULL)
    {
        delete instance;
    }
    
    //Clean up spheres
    for (std::vector<Sphere*>::iterator itr = spheres.begin(); itr!=spheres.end(); itr++)
    {  
        delete (*itr);
    }
    
    //Clean up lights
    for (std::vector<Light*>::iterator itr = lights.begin(); itr!=lights.end(); itr++)
    {  
        delete (*itr);
    }
}

Renderer* Renderer::GetInstance()
{
    if (instance==NULL)
    {
        instance = new Renderer();
    }
    return instance;
}

void Renderer::SetCamera(Camera* camera)
{
     this->camera = camera;
}

void Renderer::SetFramebuffer(Framebuffer* framebuffer)
{
     this->framebuffer = framebuffer;
}

bool Renderer::SetRenderResolution(int width, int height)
{
    if (width<0 || height<0) {
        return false;
    }
    else
    {
        this->width = width;
        this->height = height;
    }
    return true;
}

bool Renderer::AddSphere(Sphere* sphere)
{
    
    spheres.push_back(sphere);
    printf("Sphere has been added, currently %i spheres in the scene\n",spheres.size());
    return true;
}

bool Renderer::AddLight(Light* light)
{
    lights.push_back(light);
    printf("Light has been added, currently %i lights in the scene\n",lights.size());
    return true;
}

void Renderer::Render()
{
    //check for framebuffer, camera
    if (framebuffer==NULL || camera==NULL)
    {
        puts("Error, framebuffer or camera is NULL");
        return;
    }
    puts("Rendering...");
    //Generate the rays from the camera's position to the imageplane
    for (int x = 0; x<width; x++)
    {
        for (int y = 0; y<height; y++)
        {  
            //Generate the ray and check for intersections
            Ray* ray = camera->GenerateRay(x,y, width, height);
            
            
            if (HitCheck::CheckForIntersection(ray, &spheres))
            {
                Sphere* hit_sphere = ray->GetIntersection().sphere;
                glm::vec3 intens = hit_sphere->CalculateIntensity(ray, &lights, &spheres);
                
                //HACK
                for (int i=0;i<3;i++)
                {
                    if (intens[i]>1.0f)
                    {
                        intens[i]=1.0f;
                    }
                }
                framebuffer->SetPixel(x,y,intens);
                
            }
            
            //Clean up
            delete ray;
        }
    }
}