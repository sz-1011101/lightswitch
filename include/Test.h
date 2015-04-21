
class Renderer;
class Scene;
class MaterialGenerator;
class Phong;
class Camera;

class Test
{
private:
    Renderer* renderer; //Do not delete!
    Scene* scene;
    MaterialGenerator* material_generator;
    Phong* phong_illumination;
    Camera* camera;
public:
    Test(Renderer* renderer);
    ~Test();
    //Test scene with 4 spheres and 1 plane
    void TestScene1();
};
