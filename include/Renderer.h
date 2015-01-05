#include "RT.h"
#include "Camera.h"
#include "Framebuffer.h"
#ifndef _RENDERJOB_H
#define _RENDERJOB_H
#include <include/RenderJob.h>
#endif
#include <vector>

class Light;
class Ray;
class Sphere;
class Material;
class Scene;
class Illumination;

class Renderer
{
private:
    Camera* camera;
    Framebuffer* framebuffer;
    static Renderer* instance; //Singleton instance
    Renderer();
    ~Renderer();
    int width;
    int height;
    Scene* scene;
    Illumination* illumination; //The model used to light the scene
public:
    void SetCamera(Camera* camera);
    void SetFramebuffer(Framebuffer* framebuffer);
    bool SetRenderResolution(int width, int height); //Set the rendered Resolution
    bool SetScene(Scene* scene);
    bool SetIllumination(Illumination* illumination);
    int GetWidth();
    int GetHeight();
    void Render(RenderJob job);
    static Renderer* GetInstance(); //Returns the class'es instance
    void Destroy();
};
