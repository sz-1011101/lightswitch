#include <include/Camera.h>
#include <include/Ray.h>

Camera::Camera(glm::vec3 up,glm::vec3 e, glm::vec3 z,float width, float height)
{
	this->width = width;
	this->height = height;
    this->e = e;
    this->z = z;
    this->d = 1.0;
    this->up = glm::normalize(-up); //HACK It seems like I have to multiply this by -1, or the scene is mirrored...
    this->w = glm::normalize(e-z);
    this->u = glm::normalize(glm::cross(this->up,this->w));
    this->v = glm::normalize(glm::cross(this->w,this->u));

    r = width/2.0f;
    l = -r;
    t = height/2.0f;
    b = -t;   
}

Camera::~Camera()
{
    //default destructor
}

Ray* Camera::GenerateRay(float x, float y)
{
    //Use offset to hit the center of the pixel
    float lr_factor = l +(r-l) * x / width;
    float tb_factor = b +(t-b) * y / height;
    glm::vec3 s = e + (lr_factor * u) + (tb_factor * v) - (d * w);
    glm::vec3 dir = normalize(s-e);
    return new Ray(e, dir);
}
