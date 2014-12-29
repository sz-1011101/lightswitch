#include "RT.h"

class Framebuffer
{
private:
    glm::vec3** pixels;
    int width;
    int height;
public:
    Framebuffer(int width, int height);
    ~Framebuffer();
    void SetPixel(int x, int y, glm::vec3 rgb);
    glm::vec3 GetPixel(int x, int y);
    void Reset(glm::vec3 rgb);
    int GetWidth();
    int GetHeight();
};
