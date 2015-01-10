#include <include/RenderWorker.h>
#include <include/RenderThread.h>
#include <stdio.h>

RenderWorker::RenderWorker(RenderThread* render_thread)
{
    this->render_thread = render_thread;
    thread_id = SDL_CreateThread(RenderWorker::RenderJobs, "render worker", this);
}

RenderWorker::~RenderWorker()
{
    SDL_WaitThread(thread_id, NULL);
}

RenderThread* RenderWorker::GetRenderThread()
{
    return render_thread;
}

int RenderWorker::RenderJobs(void* pointer_to_render_worker)
{
    RenderThread* ptr = ((RenderWorker*) pointer_to_render_worker)->GetRenderThread(); //pointer to Renderer instance
    RenderJob job;

    bool active= true;
    puts("Initialized Thread");
    
    while (active)
    {
        ptr->PreRetrieveJob();
        
        if (ptr->IsAllJobsAssigned())
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
            ptr->Render(job); //Render the quad
            ptr->SignalRefresh(); //Signal that a new quad is done
        }

    }
    
    puts("Thread finishing");
    return 0;
}
