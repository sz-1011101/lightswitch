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
   float l;
   float r;
   float t;
   float b;
   float d;
   float width;
   float height;
public:
   Camera(glm::vec3 up ,glm::vec3 e, glm::vec3 z,float width, float height); // Constructor with up, position e and lookat z vector and the width and height of the viewplane
   ~Camera();
   Ray* GenerateRay(float x, float y); // Generate a ray corresponding to the pixel (x,y) and the width of the rendered image
};
