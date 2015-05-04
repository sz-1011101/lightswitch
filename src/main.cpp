#include <include/RT.h>
#include <include/Renderer.h>
#include <include/RenderThread.h>
#include <include/WindowWrapper.h>
#include <include/MaterialGenerator.h>
#include <include/Sphere.h>
#include <include/Plane.h>
#include <include/Light.h>
#include <include/Scene.h>
#include <include/Phong.h>

int main(int argc, char* args[]) 
{
    //Lots of testing
    const int width = 1000;
    const int height = 1000;
    
    Camera* camera = new Camera(glm::vec3(0,1,0),glm::vec3(25,10,25),glm::vec3(0,0,0),1.0f,1.0f); 
    Framebuffer* framebuffer = new Framebuffer(width, height);
    Renderer* renderer = Renderer::GetInstance();
    WindowWrapper* windowwrapper = new WindowWrapper(width, height, framebuffer);
    Scene* scene = new Scene();
    Phong* phong_illumination = new Phong(scene ,3 ,0.00001f, glm::vec3(0.19,0.59,0.95), true);
    MaterialGenerator* material_generator = new MaterialGenerator();
    
    Material* mat1 = material_generator->GenMaterial(glm::vec3(0.8,0.1,0.1),glm::vec3(0.1,0.1,0.1),glm::vec3(0.5),80);
    Material* mat2 = material_generator->GenMaterial(glm::vec3(0.1,0.8,0.1),glm::vec3(0.1,0.1,0.1),glm::vec3(0.5),50);
    Material* mat3 = material_generator->GenMaterial(glm::vec3(0.1,0.1,0.8),glm::vec3(0.1,0.1,0.1),glm::vec3(0.5),100);
    Material* mat4 = material_generator->GenMaterial(glm::vec3(0.5,0.5,0.025),glm::vec3(0.1,0.1,0.1),glm::vec3(0.1),35);
    Material* mat5 = material_generator->GenMaterial(glm::vec3(0.75,0.75,0.75),glm::vec3(0.75,0.75,0.75),glm::vec3(0.01),35);
    
    scene->AddLight(new Light(glm::vec3(6,3,1),15.0f,glm::vec3(1.0f,1.0f,1.0f)));
    scene->AddLight(new Light(glm::vec3(3,3,3),10.0f,glm::vec3(0.5f,0.7f,0.1f)));
    scene->AddLight(new Light(glm::vec3(8,0,0),20.0f,glm::vec3(1.0f,0.7f,0.0f)));
    
    scene->AddObject(new Sphere(glm::vec3(3,0,0), 1, mat1));
    scene->AddObject(new Sphere(glm::vec3(0,3,0), 1, mat2));
    scene->AddObject(new Sphere(glm::vec3(0,0,3), 1, mat3));
    scene->AddObject(new Sphere(glm::vec3(0,0,0), 1, mat4));
    
    scene->AddObject(new Plane(glm::vec3(-1,-1,-1), glm::vec3(1,1,1), mat5));
    
    renderer->SetScene(scene);
    renderer->SetRenderResolution(width,height);
    renderer->SetCamera(camera);
    renderer->SetFramebuffer(framebuffer);
    renderer->SetIllumination(phong_illumination);
    
    RenderThread* renderthread = new RenderThread(renderer);
    
    //main loop
    while (!renderthread->IsRenderingDone() && windowwrapper->IsActive())
    {
        renderthread->WaitRefresh();
        windowwrapper->Refresh();
    }
    windowwrapper->Refresh();
    //make sure the renderer stops in case the user wants to quit the program
    renderthread->SetRenderDone();
    
    //Wait for quit action of user
    if (windowwrapper->IsActive())
    {
        windowwrapper->HandleEvents(false);
    }
    
    
    delete renderthread;
    
    delete windowwrapper;
    windowwrapper = NULL;
    delete scene;
    delete material_generator;
    delete phong_illumination;
    delete camera;
    renderer->Destroy();
    delete framebuffer;
}
