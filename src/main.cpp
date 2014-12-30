#include <include/RT.h>
#include <include/Renderer.h>
#include <include/WindowWrapper.h>
#include <include/MaterialGenerator.h>
#include <include/Sphere.h>
#include <include/Light.h>
#include <include/Scene.h>
#include <include/Phong.h>

int main(int argc, char* args[]) 
{
    //Lots of testing
    const int width = 1280;
    const int height = 720;
    
    Camera* camera = new Camera(glm::vec3(0,1,0),glm::vec3(3,5,5),glm::vec3(0,0,0),width,height); 
    Framebuffer* framebuffer = new Framebuffer(width, height);
    Renderer* renderer = Renderer::GetInstance();
    WindowWrapper* windowwrapper = new WindowWrapper(width, height, framebuffer);
    Scene* scene = new Scene();
    Phong* phong_illumination = new Phong(scene ,3 ,0.0001f, glm::vec3(0.19,0.59,0.95), true);
    MaterialGenerator* material_generator = new MaterialGenerator();
    Material* mat1 = material_generator->GenMaterial(glm::vec3(0.5,0.1,0.5),glm::vec3(0.1,0.1,0.1),glm::vec3(0.1),300);
    Material* mat2 = material_generator->GenMaterial(glm::vec3(0.5,0.1,0.1),glm::vec3(0.5,0.1,0.1),glm::vec3(0.5),50);
    
    scene->AddLight(new Light(glm::vec3(5,5,5),100.0f,glm::vec3(1.0f,1.0f,1.0f)));
    
    scene->AddObject(new Sphere(glm::vec3(0,0,0), 2, mat1));
    scene->AddObject(new Sphere(glm::vec3(3,0,0), 1, mat2));
    scene->AddObject(new Sphere(glm::vec3(0,3,0), 1, mat2));
    scene->AddObject(new Sphere(glm::vec3(0,0,3), 1, mat2));
    
    renderer->SetScene(scene);
    renderer->SetRenderResolution(width,height);
    renderer->SetCamera(camera);
    renderer->SetFramebuffer(framebuffer);
    renderer->SetIllumination(phong_illumination);
    renderer->Render();
    
    while (windowwrapper->IsActive())
    {
        windowwrapper->Refresh();
        windowwrapper->HandleEvents();
    }
    
    delete windowwrapper;
    windowwrapper = NULL;
    delete scene;
    delete material_generator;
    delete phong_illumination;
    delete camera;
    renderer->Destroy();
    delete framebuffer;
}