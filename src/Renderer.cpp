#include <include/Renderer.h>
#include <include/HitCheck.h>
#include <include/Scene.h>
#include <include/Ray.h>
#include <include/Material.h>
#include <include/Light.h>
#include <include/Object.h>
#include <include/Illumination.h>
#include <vector>

Renderer* Renderer::instance = NULL;

Renderer::Renderer()
{
    //default constructor
}

Renderer::~Renderer()
{
    
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

bool Renderer::SetScene(Scene* scene)
{
    this->scene = scene;
    return true;
}

bool Renderer::SetIllumination(Illumination* illumination)
{
    this->illumination = illumination;
    return true;
}

int Renderer::GetWidth()
{
    return width;
}

int Renderer::GetHeight()
{
    return height;
}
    
void Renderer::Render(RenderJob job)
{
    //check for framebuffer, camera
    if (framebuffer==NULL || camera==NULL)
    {
        puts("Error, framebuffer or camera is NULL");
        return;
    }

    //Generate the ray and check for intersections
    Ray* ray = camera->GenerateRay(job.x/(float)width,job.y/(float)height);
    
    if (HitCheck::CheckForIntersection(ray, scene->GetObjects()))
    {
        Object* hit_object = ray->GetIntersection().object;
        glm::vec3 intens = hit_object->CalculateIntensity(illumination, ray);
        //HACK ...But it produces proper results
        for (int i=0;i<3;i++)
        {
            if (intens[i]>1.0f)
            {
                intens[i]=1.0f;
            }
        }
        framebuffer->SetPixel(job.x,job.y,intens);              
    }
    else
    {
        framebuffer->SetPixel(job.x,job.y,illumination->GetSkyColor());
    }
    
    //Clean up
    delete ray;
}

void Renderer::Destroy()
{
    if (instance!=NULL)
    {
        delete instance;
    }
    instance = NULL;
}
