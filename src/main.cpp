#include <include/RT.h>
#include <include/Renderer.h>
#include <include/RenderThread.h>
#include <include/WindowWrapper.h>
/*
#include <include/MaterialGenerator.h>
#include <include/Sphere.h>
#include <include/Plane.h>
#include <include/Light.h>
#include <include/Scene.h>
#include <include/Phong.h>
*/
#include <include/Test.h>

int main(int argc, char* args[]) 
{
    //Test scene, hard coded for now
    const int width = 1000;
    const int height = 1000;

    Renderer* renderer = Renderer::GetInstance();
    Framebuffer* framebuffer = new Framebuffer(width, height);
    WindowWrapper* windowwrapper = new WindowWrapper(width, height, framebuffer);
    
    renderer->SetFramebuffer(framebuffer);
    renderer->SetRenderResolution(width,height);
    
    Test* test = new Test(renderer);
    test->TestScene1(); //Load the test scene
    
    RenderThread* renderthread = new RenderThread(renderer);
    
    //main loop
    while (!renderthread->IsRenderingDone() && windowwrapper->IsActive())
    {
        renderthread->WaitRefresh();
        windowwrapper->Refresh();
    }
    windowwrapper->Refresh();
    //make sure the renderer stops in case the user wants to quit the program
    renderthread->SetRenderDone();
    
    //Wait for quit action of user
    if (windowwrapper->IsActive())
    {
        windowwrapper->HandleEvents(false);
    }
    
    delete renderthread;
    delete test;
    delete windowwrapper;
    windowwrapper = NULL;
    renderer->Destroy();
    delete framebuffer;
}

