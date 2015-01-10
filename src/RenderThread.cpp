#include <include/RenderThread.h>
#include <include/Renderer.h>
#include <include/RenderWorker.h>

RenderThread::RenderThread(Renderer* renderer)
{
    this->renderer = renderer;
    semaphore_1 = SDL_CreateSemaphore(1);
    semaphore_2 = SDL_CreateSemaphore(1);
    SDL_SemWait(semaphore_1); //Stop renderthread from rendering prematurly

    //these are semaphores used for job retrieval sync
    semaphore_job_avaible = SDL_CreateSemaphore(1);
    semaphore_job_waiting = SDL_CreateSemaphore(1);
    semaphore_job_protect = SDL_CreateSemaphore(1);
    SDL_SemWait(semaphore_job_avaible);
    
    //job.x, job.y = -1 mean there is no job avaible currently
    job.x = -1;
    job.y = -1;
    job.cell_width_height = -1;
    
    active = true;
    jobs_assigned = false;
    thread_amount = SDL_GetCPUCount(); //Maximum amount of threads that will be created when rendering
    
    main_thread_id = SDL_CreateThread(RenderAll, "Main Render Thread", this);
}

RenderThread::~RenderThread()
{
    SDL_WaitThread(main_thread_id, NULL);
    
    SDL_DestroySemaphore(semaphore_1);
    SDL_DestroySemaphore(semaphore_2);
    
    SDL_DestroySemaphore(semaphore_job_avaible);
    SDL_DestroySemaphore(semaphore_job_waiting);
    SDL_DestroySemaphore(semaphore_job_protect);
}

void RenderThread::WaitRefresh()
{
    SDL_SemWait(semaphore_1);
}
void RenderThread::SignalRefresh()
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

int RenderThread::GetThreadAmount()
{
    return thread_amount;
}

int RenderThread::RenderAll(void* pointer_to_instance)
{
    RenderThread* ptr = (RenderThread*) pointer_to_instance;
    RenderWorker** workers = new RenderWorker*[ptr->GetThreadAmount()]; //pointer to array which holds the workers
        
    for (int i = 0; i < ptr->GetThreadAmount(); i++)
    {
        workers[i] = new RenderWorker(ptr);
    }
    printf("%i Worker threads created\n", ptr->GetThreadAmount());
    
    RenderJob job_to_assign = {-1,-1};
    
    const int CELL_WIDTH_HEIGHT = 128; //How large the quad is the thread handles in a single job

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
    
    for (int i = 0; i < ptr->GetThreadAmount(); i++) //Signal all Workers that no jobs are avaible anymore
    {
        ptr->SignalAllJobsAssigned();
    }
    
    for (int i = 0; i < ptr->GetThreadAmount(); i++)
    { 
        delete workers[i];
        workers[i] = NULL;
    }
    
    ptr->SetRenderDone();
    ptr->SignalRefresh();
    
    return 0;
}

void RenderThread::Render(RenderJob job)
{
    renderer->Render(job);
}

void RenderThread::SetJob(RenderJob job)
{
    SDL_SemWait(semaphore_job_waiting);
    
    SDL_SemWait(semaphore_job_protect);
    
    this->job = job;

    SDL_SemPost(semaphore_job_protect);

    SDL_SemPost(semaphore_job_avaible);
}

void RenderThread::SignalAllJobsAssigned()
{
    SDL_SemWait(semaphore_job_waiting);
    
    SDL_SemWait(semaphore_job_protect);
    
    jobs_assigned = true;
    
    SDL_SemPost(semaphore_job_protect);

    SDL_SemPost(semaphore_job_avaible);
    
}

void RenderThread::PreRetrieveJob()
{
    SDL_SemWait(semaphore_job_avaible);
    
    SDL_SemWait(semaphore_job_protect);
}

RenderJob RenderThread::RetrieveJob()
{
    RenderJob result_job = job;
    
    job.x = -1;
    job.y = -1;
    job.cell_width_height = -1;
    
    return result_job;
}

bool RenderThread::IsAllJobsAssigned()
{
    return jobs_assigned;
}

void RenderThread::PostRetrieveJob()
{
    SDL_SemPost(semaphore_job_protect);
    
    SDL_SemPost(semaphore_job_waiting);
}
