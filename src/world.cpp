#include "world.hpp"

world::world(){}

world_construction_token world::construct_token(const std::string &title, int screen_pos_x, int screen_pos_y, int width, int height){
    world_construction_token token;
    token.error = std::string("");
    if(SDL_Init(SDL_INIT_VIDEO)) {
        token.error = "Could not initialize SDL - " + std::string(SDL_GetError());
    } else {
        token.screen = SDL_CreateWindow(title.c_str(), screen_pos_x, screen_pos_y, width, height,
                                        SDL_WINDOW_SHOWN /*| SDL_WINDOW_BORDERLESS*/ | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
        if(!token.screen) {
            SDL_Quit();
            token.error = "SDL: could not set video mode - exiting";
        } else {
            token.renderer = SDL_CreateRenderer(token.screen, -1, 0);
            if (!token.renderer) {
                SDL_DestroyWindow(token.screen);
                SDL_Quit();
                token.error = "SDL: could not create renderer - exiting";
            } else {
                token.texture = SDL_CreateTexture(token.renderer, SDL_PIXELFORMAT_YV12,
                                                  SDL_TEXTUREACCESS_STATIC, width, height);
                if (!token.texture) {
                    SDL_DestroyWindow(token.screen);
                    SDL_DestroyRenderer(token.renderer);
                    SDL_Quit();
                    token.error = "SDL: could not create texture - exiting";
                }
            }
        }
    }
    token.loop_stop_flag.exchange(false);
    return token;
}

world::world(world_construction_token&& inpt_token) {
    this->token = std::move(inpt_token);
}

void world::run_loop(){
    loop_thread = std::thread([this](){
        this->start_loop();
    });
}

void world::start_loop(){
    SDL_Event event;
    while (!token.loop_stop_flag) {
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT ) break;
        }
    }
    token.loop_stop_flag.exchange(false);
}

world::~world(){
    token.loop_stop_flag.exchange(true);
    if (loop_thread.joinable()) {
        loop_thread.join();
    }
    SDL_DestroyTexture(token.texture);
    SDL_DestroyRenderer(token.renderer);
    SDL_DestroyWindow(token.screen);
    SDL_Quit();
}

world_construction_token& world_construction_token::operator=(world_construction_token&& token) {
    renderer = token.renderer;
    screen = token.screen;
    texture = token.texture;
    error = std::string{};
    loop_stop_flag.exchange(token.loop_stop_flag, std::memory_order_acq_rel);
    token.renderer = nullptr;
    token.screen = nullptr;
    token.texture = nullptr;
}

world_construction_token::world_construction_token(const world_construction_token& token) {
    renderer = token.renderer;
    screen = token.screen;
    texture = token.texture;
    error = std::string{};
    loop_stop_flag.exchange(token.loop_stop_flag, std::memory_order_acq_rel);
}

world_construction_token::world_construction_token() : error() {
    loop_stop_flag.exchange(false, std::memory_order_acq_rel);
    renderer = nullptr;
    screen = nullptr;
    texture = nullptr;
}
