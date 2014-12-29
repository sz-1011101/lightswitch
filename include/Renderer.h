#include "RT.h"
#include "Camera.h"
#include "Framebuffer.h"
#include <vector>

class Light;
class Ray;
class Sphere;

class Renderer
{
private:
    Camera* camera;
    Framebuffer* framebuffer;
    std::vector<Sphere*> spheres; //Holds all spheres in the scene
    std::vector<Light*> lights; //Holds all (Point)Lights
    static Renderer* instance; //Singleton instance
    Renderer();
    ~Renderer();
    int width;
    int height;
public:
    void SetCamera(Camera* camera);
    void SetFramebuffer(Framebuffer* framebuffer);
    bool SetRenderResolution(int width, int height); //Set the rendered Resolution
    bool AddSphere(Sphere* sphere); 
    bool AddLight(Light* light);
    void Render();
    static Renderer* GetInstance(); //Returns the class'es instance
};