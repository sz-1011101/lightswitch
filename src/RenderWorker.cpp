#include <include/RenderWorker.h>
#include <include/RenderThread.h>
#include <include/Renderer.h>
#include <stdio.h>

int RenderWorker::RenderJobs(void* pointer_to_render_thread)
{
    RenderThread* ptr = (RenderThread*) pointer_to_render_thread;
    RenderJob job;

    bool active= true;
    puts("Initialized Thread");
    
    while (active)
    {
        ptr->PreRetrieveJob();
        
        if (ptr->IsAllJobsDone())
        {
            active = false;
        }
        else
        {
            job = ptr->RetrieveJob();
        }
        
        ptr->PostRetrieveJob();
        
        if (active) //There is a valid job assigned, so do it
        {
            ptr->GetRenderer()->Render(job); //Render the quad
            ptr->Signal(); //Signal that a new quad is done
        }

    }
    
    puts("Thread finishing");
    return 0;
}
