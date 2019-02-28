#include "world.hpp"
#include <cmath>

world::world() : field(10, 10), view(10,10), player_1(0,0){}

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
                token.texture = SDL_CreateTexture(token.renderer, SDL_PIXELFORMAT_RGBA8888,
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
    token.win_set.width = width;
    token.win_set.height = height;
    token.win_set.title = title;
    token.win_set.screen_pos_x = screen_pos_x;
    token.win_set.screen_pos_y = screen_pos_y;
    token.loop_stop_flag.exchange(false);
    return token;
}

world::world(world_construction_token&& inpt_token)
        : field(inpt_token.win_set.width/2, inpt_token.win_set.height),
          view(inpt_token.win_set.width/2, inpt_token.win_set.height),
          player_1(100,200) {
    this->token = std::move(inpt_token);

}

void world::run_loop(){
    loop_thread = std::thread([this](){
        this->start_loop();
    });
}

void world::start_loop(){
    SDL_Event event;
    sdl_image img(token.win_set.width, token.win_set.height);
    load_game_field();
    while (!token.loop_stop_flag) {
//        view.clear();
        update_player();
        while (SDL_PollEvent(&event)) {
//            std::cout << "SDL event " << event.type << std::endl;
            if (event.type == SDL_KEYDOWN) {
                const int shift = 10;
                switch (event.key.keysym.sym) {
                case SDLK_RIGHT: {
                    player_1.move_right(shift);
                    break;
                }
                case SDLK_LEFT: {
                    player_1.move_left(shift);
                    break;
                }
                case SDLK_DOWN: {
                    player_1.move_down(shift);
                    break;
                }
                case SDLK_UP: {
                    player_1.move_up(shift);
                    break;
                }
                }
            }  else if(event.type == SDL_QUIT || 256 == event.type) {
                token.loop_stop_flag.exchange(true, std::memory_order_acq_rel);
            }
        }
        update_texture(img);
    }
    token.loop_stop_flag.exchange(false, std::memory_order_acq_rel);
}

void world::load_game_field(){
    blocks_info info = field.get_blocks_info();
//    field.change_field_background_color(static_cast<uint32_t> (hex_colors::white));
//    field.set_rect_color(0,0,static_cast<uint32_t> (hex_colors::purple));
    field.generate_game_field();
//    field.set_rect_color(2,0,static_cast<uint32_t> (hex_colors::purple));
//    field.set_rect_color(4,0,static_cast<uint32_t> (hex_colors::purple));
//    field.set_rect_color(6,0,static_cast<uint32_t> (hex_colors::purple));
//    field.set_rect_color(8,0,static_cast<uint32_t> (hex_colors::purple));
//    for (int i = 0; i < info.blocks_x; ++i) {
//        for (int j = 0; j < info.blocks_y; ++j) {
//            int pos = i + j;
//            if (pos%2) {
//                field.set_rect_color(i,j,static_cast<uint32_t> (hex_colors::purple));
//            }
//        }
//    }
}

void world::load_texture(const std::string &texture_path, int width, int height) {
//    image_texture texture;
//    texture.image_texture
    image img(width, height);
}

void world::update_player(){
    player_1.add_rotate_degree(0.1);
}

void world::update_texture(sdl_image &texture){

//    texture.draw_rect(0,0, 640, 480, static_cast<uint32_t>(hex_colors::white)); // 0xFF00FF00
//    texture.draw_rect(0,0, 100, 100, static_cast<uint32_t>(hex_colors::yellow));
//    texture.draw_rect(200,0, 100, 100, static_cast<uint32_t>(hex_colors::red));
//    texture.draw_rect(0,200, 100, 100, static_cast<uint32_t>(hex_colors::green));

    SDL_UpdateTexture(token.texture, field.get_field_rectangle(), field.get_field_pixels_buffer(), field.get_pitch());
    SDL_UpdateTexture(token.texture, player_1.get_field_rectangle(), player_1.get_field_pixels_buffer(), player_1.get_pitch());
    SDL_UpdateTexture(token.texture, view.get_field_rectangle(), view.get_field_pixels_buffer(), view.get_pitch());

    SDL_RenderClear(token.renderer);
    SDL_RenderCopy(token.renderer, token.texture, nullptr, nullptr);
    view.clear();
    draw_sigh_angle();
    SDL_RenderPresent(token.renderer);

}

void world::draw_sigh_angle(){
    point_position player_pos;
    player_pos.x = player_1.get_pos().x;
    player_pos.y = player_1.get_pos().y;

    double direction_angle = player_1.get_sight().direction_angle;
    double sigh_angle = player_1.get_sight().sigh_angle;

    double start_angle = direction_angle - sigh_angle/2;
    double end_angle = direction_angle + sigh_angle/2;
    double delta_angle = 1;
    double angle = start_angle;
    std::vector<pixel_info> pixel_poses;
    while (angle <= end_angle) {
        auto info = draw_line_of_sight(angle);
        pixel_poses.push_back(info);
        angle += delta_angle;
    }

    int counter = 0;
    for (auto& obstacle : pixel_poses) {
        view.draw_view_strip(player_pos, obstacle.pos, obstacle.color, counter);
        counter++;
    }
//    size_t base_poses_count = pixel_poses.size();
//    for (int i = 0; i < base_poses_count; ++i) {
//    }

}

pixel_info world::draw_line_of_sight(double angle) {
    int x0 = player_1.get_pos().x;
    int y0 = player_1.get_pos().y;

    double radian_scale = 3.14/180;

    std::vector<player_position> sigh_pixels;

    double rad = angle*radian_scale;
    point_position end_pos;
    end_pos.x = 0;
    end_pos.y = 0;

    double x = x0;
    double y = y0;
    double dx = cos(rad);
    double dy = sin(rad);
    while ((x > 0 && x < field.width) && (y > 0 && y < field.height) ) {
        x += dx;
        y += dy;
        player_position pos;
        pos.x = x;
        pos.y = y;
        sigh_pixels.push_back(pos);
    }

    hex_colors sight_color = hex_colors::aqua;
    void* buf = field.get_field_pixels_buffer();
    uint32_t* pixels = static_cast<uint32_t*> (buf);
//    int x_end = 0;
//    int y_end = 0;
    uint32_t pixel_color = 0;
    for (auto& el : sigh_pixels) {
//        int pos = el.y*field.height + el.x;
        int pos = el.y*field.width + el.x;
        pixel_color = pixels[pos];
        if (pixel_color == static_cast<uint32_t>(hex_colors::white)) {
//            pixels[pos] = static_cast<uint32_t>(sight_color);
        } else if (pixel_color != static_cast<uint32_t>(player_1.color)) {
            end_pos.x = el.x;
            end_pos.y = el.y;
            break;
        }
    }

    SDL_RenderDrawLine(token.renderer, x0, y0, end_pos.x, end_pos.y);
    pixel_info info;
    info.pos = end_pos;
    info.color = pixel_color;
    return info;
//    SDL_RenderDrawLine(token.renderer, x0, y0, y_end, x_end);
}


world::~world(){
    token.loop_stop_flag.exchange(true, std::memory_order_acq_rel);
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
    win_set = token.win_set;
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
    win_set = token.win_set;
    error = std::string{};
    loop_stop_flag.exchange(token.loop_stop_flag, std::memory_order_acq_rel);
}

world_construction_token::world_construction_token() : error() {
    loop_stop_flag.exchange(false, std::memory_order_acq_rel);
    renderer = nullptr;
    screen = nullptr;
    texture = nullptr;
}
