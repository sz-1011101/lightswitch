#include "RT.h"

class Ray;

class Camera
{
private:
   glm::vec3 up;
   glm::vec3 w;
   glm::vec3 u;
   glm::vec3 v;
   glm::vec3 e; //The camera's position
   glm::vec3 z; //Where the camera looks at
   int l;
   int r;
   int t;
   int b;
   float d;
public:
   Camera(glm::vec3 up ,glm::vec3 e, glm::vec3 z,int width, int height);
   ~Camera();
   Ray* GenerateRay(int x, int y, int width, int height); // Generate a ray corresponding to the pixel (x,y) and the width of the rendered image
};