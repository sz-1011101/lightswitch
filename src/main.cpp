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
    const int width = 1000;
    const int height = 600;
    
    Camera* camera = new Camera(glm::vec3(0,1,0),glm::vec3(5,6,7),glm::vec3(0,0,0),width,height); 
    Framebuffer* framebuffer = new Framebuffer(width, height);
    Renderer* renderer = Renderer::GetInstance();
    WindowWrapper* windowwrapper = new WindowWrapper(width, height, framebuffer);
    Scene* scene = new Scene();
    Phong* phong_illumination = new Phong(scene ,3 ,0.00001f, glm::vec3(0.19,0.59,0.95), true);
    MaterialGenerator* material_generator = new MaterialGenerator();
    Material* mat1 = material_generator->GenMaterial(glm::vec3(0.8,0.1,0.5),glm::vec3(0.1,0.1,0.1),glm::vec3(0.4),80);
    Material* mat2 = material_generator->GenMaterial(glm::vec3(0.8,0.1,0.1),glm::vec3(0.5,0.1,0.1),glm::vec3(0.3),50);
    Material* mat3 = material_generator->GenMaterial(glm::vec3(0.25,0.25,0.25),glm::vec3(0.25,0.25,0.25),glm::vec3(0.75),100);
    Material* mat4 = material_generator->GenMaterial(glm::vec3(0.25,0.25,0.25),glm::vec3(0.25,0.25,0.25),glm::vec3(0.0),100);
    
    scene->AddLight(new Light(glm::vec3(6,3,3),20.0f,glm::vec3(1.0f,1.0f,1.0f)));
    scene->AddLight(new Light(glm::vec3(3,3,6),10.0f,glm::vec3(1.0f,1.0f,0.0f)));
    
    scene->AddObject(new Sphere(glm::vec3(0,0,0), 2, mat1));
    scene->AddObject(new Sphere(glm::vec3(3,0,0), 1, mat2));
    scene->AddObject(new Sphere(glm::vec3(0,3,0), 1, mat2));
    scene->AddObject(new Sphere(glm::vec3(0,0,3), 1, mat2));
    scene->AddObject(new Sphere(glm::vec3(5,0,0), 0.75, mat3));
    scene->AddObject(new Sphere(glm::vec3(0,5,0), 0.75, mat3));
    scene->AddObject(new Sphere(glm::vec3(0,0,5), 0.75, mat3));
    
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