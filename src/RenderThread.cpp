#include <include/RenderThread.h>
#include <include/Renderer.h>

RenderThread::RenderThread(Renderer* renderer)
{
    this->renderer = renderer;
    this->semaphore_1 = SDL_CreateSemaphore(1);
    this->semaphore_2 = SDL_CreateSemaphore(1);
    SDL_SemWait(semaphore_1); //Stop renderthread from rendering prematurly
    this->active = true;
    this->main_thread_id = SDL_CreateThread(RenderAll, "Main Render Thread", this);
}

RenderThread::~RenderThread()
{
    SDL_WaitThread(main_thread_id, NULL);
    SDL_DestroySemaphore(semaphore_1);
    SDL_DestroySemaphore(semaphore_2);
}

void RenderThread::Wait()
{
    SDL_SemWait(semaphore_1);
}
void RenderThread::Signal()
{
    SDL_SemPost(semaphore_1);
}

void RenderThread::SetRenderDone()
{
    SDL_SemWait(semaphore_2);
    active = false;
    SDL_SemPost(semaphore_2);
}

bool RenderThread::IsRenderingDone()
{
    bool active;
    SDL_SemWait(semaphore_2);
    active = this->active;
    SDL_SemPost(semaphore_2);
    return !active;
}

Renderer* RenderThread::GetRenderer()
{
    return renderer;
}

int RenderThread::RenderAll(void* pointer_to_instance)
{
    RenderThread* ptr = (RenderThread*) pointer_to_instance;
    RenderJob job = {-1,-1};
    
    for (int y = 0; y < ptr->GetRenderer()->GetHeight();y++)
    {
        for (int x = 0; x < ptr->GetRenderer()->GetWidth();x++)
        {
            if (!ptr->IsRenderingDone()) {
                job.x = x;
                job.y = y;
                ptr->GetRenderer()->Render(job);
                ptr->Signal();
            }
            else
            {
                ptr->Signal();
                return -1; //Rendering stopped
            }
        }
        
    }
    
    ptr->SetRenderDone();
    return 0;
}
