#include "RT.h"
#include <SDL2/SDL_thread.h>

class Framebuffer
{
private:
    glm::vec3** pixels;
    int width;
    int height;
    SDL_sem* framebuffer_semaphore; //used to only let one thread read/write at a time
public:
    Framebuffer(int width, int height);
    ~Framebuffer();
    void SetPixel(int x, int y, glm::vec3 rgb);
    glm::vec3 GetPixel(int x, int y);
    void Reset(glm::vec3 rgb);
    int GetWidth();
    int GetHeight();
};
