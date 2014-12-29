#include <include/WindowWrapper.h>
#include <include/Framebuffer.h>
#include <stdio.h>
#include <math.h>

WindowWrapper::WindowWrapper(int width, int height, Framebuffer* framebuffer)
{
    this->width = width;
    this->height = height;
    this->framebuffer = framebuffer;
    this->active = true;
    
    //Window initialisation
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error initzialising SDL: %s\n",SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow("lightswitch 0.01",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,SDL_WINDOW_SHOWN);
        
        if (window == NULL)
        {
            printf("Error creating window: %s\n",SDL_GetError());
        }
        else
        {
            //rgb masking for the surface
            Uint32 rmask, gmask, bmask, amask;
            #if SDL_BYTEORDER == SDL_BIG_ENDIAN
                rmask = 0xff000000;
                gmask = 0x00ff0000;
                bmask = 0x0000ff00;
                amask = 0x000000ff;
                big_endian = true;
            #else
                rmask = 0x000000ff;
                gmask = 0x0000ff00;
                bmask = 0x00ff0000;
                amask = 0xff000000;
                big_endian = false;
            #endif

            surface = SDL_CreateRGBSurface(0, width, height,32,rmask,gmask,bmask,amask);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            
            
            if (renderer == NULL)
            {
                printf("Error creating renderer: %s\n",SDL_GetError());
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 200,200,200,255);
                SDL_RenderClear(renderer);
            }
            
        }
    }
    
}

WindowWrapper::~WindowWrapper()
{
    SetInactive();
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    texture = NULL;
    surface = NULL;
    renderer = NULL;
    window = NULL;
    SDL_Quit();
}

void WindowWrapper::Refresh()
{
    Uint32 *pixels = (Uint32 *)surface->pixels;
    if (active)
    {     
        
        for(int x=0;x<framebuffer->GetWidth();x++)
        {
            for(int y=0;y<framebuffer->GetHeight();y++)
            {
                glm::vec3 current_pixel = framebuffer->GetPixel(x,y);
                pixels[( y * surface->w ) + x] = ConvertColorToPixel(current_pixel[0],current_pixel[1],current_pixel[2]);
            }
        }
        
    }
    if (texture!=NULL)
    {
        SDL_DestroyTexture(texture);
    }
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void WindowWrapper::SetInactive()
{
    active = false;
}

bool WindowWrapper::IsActive()
{
    return active;
}

void WindowWrapper::HandleEvents()
{
    while (SDL_WaitEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            SetInactive();
            break;
        }
    }
}

Uint32 WindowWrapper::ConvertColorToPixel(float r, float g, float b)
{
    Uint32 result;
    //Convert float in [0,1] to Uint32
    Uint32 converted_r = (Uint32)(r*255);
    Uint32 converted_g = (Uint32)(g*255);
    Uint32 converted_b = (Uint32)(b*255);
    
    if (big_endian)
    {
        result = 0x000000ff + (converted_r<<24) + (converted_g<<16) + (converted_b<<8);
    }
    else
    {
        result = 0xff000000+ (converted_b<<16) + (converted_g<<8) + (converted_r);
    }
    
    return result;
}