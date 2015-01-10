#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#ifndef _RENDERJOB_H
#define _RENDERJOB_H
#include <include/RenderJob.h>
#endif

class Renderer;
class RenderWorker;

class RenderThread
{
private:
    SDL_Thread* main_thread_id;
    SDL_sem* semaphore_1; //Used to signal for new calculated pixels
    SDL_sem* semaphore_2; //Used to protect bool active
    
    SDL_sem* semaphore_job_avaible;
    SDL_sem* semaphore_job_waiting;
    SDL_sem* semaphore_job_protect;
    
    Renderer* renderer;
    RenderJob job; //Current Job
    bool active;
    bool jobs_assigned;
    int thread_amount;
public:
    RenderThread(Renderer* renderer);
    ~RenderThread();
    void WaitRefresh(); //Use this function to block and wait for the next quad of pixels
    void SignalRefresh(); //Call this function to signal for a new quad of pixels
    bool IsRenderingDone();
    void SetRenderDone(); 
    Renderer* GetRenderer();
    int GetThreadAmount();
    
    void Render(RenderJob job); //Pass the job to the renderer instance
    void SetJob(RenderJob job);
    void SignalAllJobsAssigned();
    void PreRetrieveJob();
    RenderJob RetrieveJob();
    bool IsAllJobsAssigned();
    void PostRetrieveJob();
    
    static int RenderAll(void* pointer_to_instance);
};
