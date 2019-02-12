#include <iostream>
#include <SDL2/SDL.h>
#include <thread>
#include "preconstruction_class.hpp"
#include <atomic>

struct world_construction_token{
    SDL_Renderer* renderer;
    SDL_Window*   screen;
    SDL_Texture*  texture;
    std::string error;
    std::atomic_bool loop_stop_flag;
    world_construction_token& operator=(world_construction_token&& token);
    world_construction_token(const world_construction_token& token);
    world_construction_token();
};


class world : public preconstruction_class<world_construction_token>
{
    std::thread loop_thread;
    world();
public:
    static world_construction_token construct_token(const std::string& title, int screen_pos_x, int screen_pos_y, int width, int height);
    world(world_construction_token&& inpt_token);
    void run_loop();
    void start_loop();

    ~world();
};
