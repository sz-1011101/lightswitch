#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#ifndef _RENDERJOB_H
#define _RENDERJOB_H
#include <include/RenderJob.h>
#endif

class Renderer;

class RenderThread
{
private:
    SDL_Thread* main_thread_id;
    SDL_sem* semaphore_1; //Used to signal for new calculated pixels
    SDL_sem* semaphore_2; //Used to protect bool active
    SDL_mutex* job_mutex; //mutex to manage job production
    SDL_cond* job_event;
    SDL_cond* job_waiting_for_event;
    
    Renderer* renderer;
    RenderJob job; //Current Job
    bool active;
    bool jobs_done;
public:
    RenderThread(Renderer* renderer);
    ~RenderThread();
    void Wait(); //Use this function to block and wait for the next pixel
    void Signal(); //Call this function to signal for a new pixel
    bool IsRenderingDone();
    void SetRenderDone(); 
    Renderer* GetRenderer();
    
    void SetJob(RenderJob job);
    void SignalAllJobsDone();
    void PreRetrieveJob();
    RenderJob RetrieveJob();
    bool IsAllJobsDone();
    void PostRetrieveJob();
    
    static int RenderAll(void* pointer_to_instance);
};
