#include <include/RenderThread.h>
#include <include/Renderer.h>
#include <include/RenderWorker.h>

RenderThread::RenderThread(Renderer* renderer)
{
    this->renderer = renderer;
    this->semaphore_1 = SDL_CreateSemaphore(1);
    this->semaphore_2 = SDL_CreateSemaphore(1);
    SDL_SemWait(semaphore_1); //Stop renderthread from rendering prematurly
    
    //job.x, job.y = -1 mean there is no job avaible currently
    this->job.x = -1;
    this->job.y = -1;
    this->job.cell_width_height = -1;
    
    this->job_mutex = SDL_CreateMutex();
    this->job_event = SDL_CreateCond();
    this->job_waiting_for_event = SDL_CreateCond();
    
    this->active = true;
    this->jobs_done = false;
    this->main_thread_id = SDL_CreateThread(RenderAll, "Main Render Thread", this);
}

RenderThread::~RenderThread()
{
    SDL_WaitThread(main_thread_id, NULL);
    
    SDL_DestroySemaphore(semaphore_1);
    SDL_DestroySemaphore(semaphore_2);
    
    SDL_DestroyCond(job_event);
    SDL_DestroyCond(job_waiting_for_event);
    
    SDL_DestroyMutex(job_mutex);
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
    RenderJob job_to_assign = {-1,-1};
    
    int thread_amount = SDL_GetCPUCount();
    
    const int CELL_WIDTH_HEIGHT = 15; //How large the quad is the thread handles in a single job

    SDL_Thread** worker_thread_id = new SDL_Thread*[thread_amount];
    printf("%i Threads created\n", thread_amount);
    
    for (int i = 0; i < thread_amount; i++) //Create a bunch of workers
    {
        worker_thread_id[i] = SDL_CreateThread(RenderWorker::RenderJobs, "render worker", ptr);
    } 

    for (int y = 0; y < ptr->GetRenderer()->GetHeight(); y += CELL_WIDTH_HEIGHT)
    {
        for (int x = 0; x < ptr->GetRenderer()->GetWidth(); x += CELL_WIDTH_HEIGHT)
        {
            if (!ptr->IsRenderingDone()) 
            {
                job_to_assign.x = x;
                job_to_assign.y = y;
                job_to_assign.cell_width_height = CELL_WIDTH_HEIGHT;
                ptr->SetJob(job_to_assign); //Try to set the new job
            }
            else
            {
                puts("Rendering canceled...");
                break;
            }
        }
        
        if (ptr->IsRenderingDone()) 
        {
            break;
        }
    }
    
    puts("Assigned all Jobs");

    ptr->SignalAllJobsDone(); //Waits until the last job has been taken, then sets jobs_done = true
    
    for (int i = 0; i < thread_amount; i++) //Wait for all workers to return
    {
        SDL_WaitThread(worker_thread_id[i], NULL);
    }
    
    delete[] worker_thread_id;
    ptr->SetRenderDone();
    ptr->Signal();

    return 0;
}

void RenderThread::SetJob(RenderJob job)
{
    SDL_LockMutex(job_mutex);
    
    if (this->job.x != -1 || this->job.y != -1) //Job not retrieved yet
    {
        SDL_CondWait(job_event, job_mutex);
    }
    
    this->job = job;
    
    SDL_UnlockMutex(job_mutex);
    
    SDL_CondSignal(job_waiting_for_event);
}

void RenderThread::SignalAllJobsDone()
{
    SDL_LockMutex(job_mutex);
    
    if (this->job.x != -1 || this->job.y != -1) //Job not retrieved yet
    {
        SDL_CondWait(job_event, job_mutex);
    }
    
    jobs_done = true;

    SDL_UnlockMutex(job_mutex);
    
    SDL_CondSignal(job_waiting_for_event);
    
}

void RenderThread::PreRetrieveJob()
{
    SDL_LockMutex(job_mutex);
    
    if (!jobs_done)
    {
        if (this->job.x == -1 && this->job.y == -1) //Job not assigned
        {
            SDL_CondWait(job_waiting_for_event, job_mutex);
        }
    }
    
}

RenderJob RenderThread::RetrieveJob()
{
    RenderJob result_job = job;
    
    job.x = -1;
    job.y = -1;
    job.cell_width_height = -1;
    
    return result_job;
}

bool RenderThread::IsAllJobsDone()
{
    return jobs_done;
}

void RenderThread::PostRetrieveJob()
{
    
    SDL_UnlockMutex(job_mutex);
    
    SDL_CondSignal(job_event);

}
