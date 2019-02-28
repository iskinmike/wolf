#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <thread>
#include <atomic>
#include <map>

#include "stb/stb.h"
#include "stb/stb_image.h"
#include "preconstruction_class.hpp"
#include "color.hpp"
#include "game_field.hpp"
#include "player.hpp"
#include "view_screen.hpp"

struct window_settings{
    std::string title;
    int screen_pos_x;
    int screen_pos_y;
    int width;
    int height;
};

struct world_construction_token{
    window_settings win_set;
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

    std::map<std::string, sdl_image> textures;
    game_field field;
    view_screen view;
    player player_1;
public:
    static world_construction_token construct_token(const std::string& title, int screen_pos_x, int screen_pos_y, int width, int height);
    world(world_construction_token&& inpt_token);
    ~world();

    void run_loop();
    void start_loop();

    void load_game_field();

    void load_texture(const std::string& texture_path, int width, int height);
    void update_player();
    void update_texture(sdl_image& texture);

    void draw_sigh_angle();
    pixel_info draw_line_of_sight(double angle);
};


#endif  /* WORLD_HPP */
