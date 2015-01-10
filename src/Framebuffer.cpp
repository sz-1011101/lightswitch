#include <include/Framebuffer.h>

Framebuffer::Framebuffer(int width, int height)
{
    this->width = width;
    this->height = height;
    this->pixels = new glm::vec3*[width];
    for (int i=0;i<width;i++)
    {
        pixels[i] = new glm::vec3[height];
        for (int j=0;j<height;j++)
        {
            pixels[i][j] = glm::vec3(0,0,0);
        }
    }
    
    framebuffer_semaphore = SDL_CreateSemaphore(1);
    
}
Framebuffer::~Framebuffer()
{
    for (int i=0;i<width;i++)
    {
        delete[] pixels[i];
    }
    delete[] pixels;
}

void Framebuffer::SetPixel(int x, int y, glm::vec3 rgb)
{
    SDL_SemWait(framebuffer_semaphore);
    if (x>=0 && x<width && y>=0 && y<height)
    {
        pixels[x][y] = rgb;
    }
    SDL_SemPost(framebuffer_semaphore);
}

glm::vec3 Framebuffer::GetPixel(int x, int y)
{
    SDL_SemWait(framebuffer_semaphore);
    glm::vec3 result = pixels[x][y];
    SDL_SemPost(framebuffer_semaphore);
    
    return result;
}

void Framebuffer::Reset(glm::vec3 rgb)
{
    SDL_SemWait(framebuffer_semaphore);
    for (int i=0;i<width;i++)
    {
        for (int j=0;j<height;j++)
        {
            pixels[i][j] = rgb;
        }
    }
    SDL_SemPost(framebuffer_semaphore);
}

int Framebuffer::GetWidth()
{
    return width;
}

int Framebuffer::GetHeight()
{
    return height;
}

