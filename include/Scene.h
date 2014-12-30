#include "RT.h"
#include <vector>

class Object;
class Light;

class Scene
{
private:
    std::vector<Object*> objects;
    std::vector<Light*> lights;
public:
    Scene();
    ~Scene();
    bool AddObject(Object* object);
    bool AddLight(Light* light);
    std::vector<Object*>* GetObjects();
    std::vector<Light*>* GetLights();   
};