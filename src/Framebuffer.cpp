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
    
    if (x>=0 && x<width && y>=0 && y<height)
    {
        pixels[x][y] = rgb;
    }
    
}

glm::vec3 Framebuffer::GetPixel(int x, int y)
{
    return pixels[x][y];
}

void Framebuffer::Reset(glm::vec3 rgb)
{
    for (int i=0;i<width;i++)
    {
        for (int j=0;j<height;j++)
        {
            pixels[i][j] = rgb;
        }
    }
}

int Framebuffer::GetWidth()
{
    return width;
}

int Framebuffer::GetHeight()
{
    return height;
}

