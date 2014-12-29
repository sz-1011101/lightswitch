#include <include/RT.h>
#include <include/Renderer.h>
#include <include/WindowWrapper.h>
#include <include/Material.h>
#include <include/Sphere.h>
#include <include/Light.h>

int main(int argc, char* args[]) 
{
    
    const int width = 512;
    const int height = 512;
    
    Camera* camera = new Camera(glm::vec3(0,1,0),glm::vec3(4,4,4),glm::vec3(0,0,0),width,height); 
    Framebuffer* framebuffer = new Framebuffer(width, height);
    Renderer* renderer = Renderer::GetInstance();
    WindowWrapper* windowwrapper = new WindowWrapper(width, height, framebuffer);

    Material* default_mat = new Material(glm::vec3(0.1,0.1,0.0),glm::vec3(0.1,0.1,0.0),glm::vec3(1,1,1),10);
    renderer->AddLight(new Light(glm::vec3(0,0,0),10.0f,glm::vec3(1.0f,1.0f,1.0f)));
    renderer->AddLight(new Light(glm::vec3(2,2,2),5.0f,glm::vec3(1.0f,0.1f,0.1f)));
    
    
    renderer->AddSphere(new Sphere(glm::vec3(0,0,3),1.0f,default_mat));
    renderer->AddSphere(new Sphere(glm::vec3(0,3,0),1.0f,default_mat));
    renderer->AddSphere(new Sphere(glm::vec3(3,0,0),1.0f,default_mat));
    
    renderer->AddSphere(new Sphere(glm::vec3(0,0,5),0.5f,default_mat));

    
    renderer->SetRenderResolution(width,height);
    renderer->SetCamera(camera);
    renderer->SetFramebuffer(framebuffer);
    renderer->Render();
    
    while (windowwrapper->IsActive())
    {
        windowwrapper->Refresh();
        windowwrapper->HandleEvents();
    }
    delete windowwrapper;
    windowwrapper = NULL;
    
}