#include <SDL2/SDL.h>


class Framebuffer;

class WindowWrapper
{
private:
    Framebuffer* framebuffer;
    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Event event;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    bool big_endian;
    int width;
    int height;
    bool active; 
    Uint32 ConvertColorToPixel(float r, float g, float b);
public:
    WindowWrapper(int width, int height, Framebuffer* framebuffer);
    ~WindowWrapper();
    void Refresh();
    void refreshTextureAndRender();
    void SetInactive();
    bool IsActive();
    void HandleEvents(bool use_polling);
};
