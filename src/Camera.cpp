#include <include/Camera.h>
#include <include/Ray.h>

Camera::Camera(glm::vec3 up,glm::vec3 e, glm::vec3 z,int width, int height)
{
    this->e = e;
    this->z = z;
    this->d = height/2;
    this->up = glm::normalize(up);
    this->w = glm::normalize(e-z);
    this->u = glm::normalize(glm::cross(up,w));
    this->v = glm::normalize(glm::cross(w,u));
    
    r = width/2;
    l = -r;
    t = height/2;
    b = -t;   
}

Camera::~Camera()
{
    //default destructor
}

Ray* Camera::GenerateRay(int x, int y, int width, int height)
{
    //Use offset of 0.5 to hit the center of the pixel
    float lr_factor = l +(r-l) * (x+0.5) / width;
    float tb_factor = b +(t-b) * (y+0.5) / height;
    glm::vec3 s = (lr_factor * u) + (tb_factor * v) - (d * w);
    glm::vec3 dir = normalize(s-e);
    return new Ray(e, dir);
}