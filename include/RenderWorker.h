#include <SDL2/SDL_thread.h>

class RenderThread;

class RenderWorker
{
private:
    SDL_Thread* thread_id;
    RenderThread* render_thread; //this threads' parent
public:
    RenderWorker(RenderThread* render_thread);
    ~RenderWorker();
    RenderThread* GetRenderThread();
    static int RenderJobs(void* pointer_to_render_worker);
};
