
#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>
#include <vector>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <memory>

enum class hex_colors : uint32_t {
    red = 0xFF000000,
    green = 0x00FF0000,
    blue = 0x0000FF00,
    white = 0xFFFFFF00,
    black = 0xFFFFFFFF,
    purple = 0xFF00FF00,
    aqua = 0x00FFFF00,
    yellow = 0xFFFF0000,
    DarkGray = 0xA9A9A900,
    DarkSeaGreen = 0x8FBC8F00,
    DarkTurquoise = 0x00CED100,
    FireBrick = 0xB2222200,
    Gainsboro = 0xDCDCDC00,
    Gold = 0xFFD70000,
    Indigo = 0x4B008200,
    LightBlue = 0xADD8E600,
    LightGray = 0xD3D3D300,
    RebeccaPurple = 0x66339900,
};

struct point_position {
    int x,y;
};

struct pixel_info {
    point_position pos;
    uint32_t color;
};


enum class color_pos{
    red = 0, green, blue, alpha
};

union rgba_color {
    uint32_t value;
    uint8_t channels[4]; // r g b a
    rgba_color(uint32_t color_val){
        value = color_val;
    }
    void set_color_value(uint8_t val, color_pos pos){
        channels[static_cast<int>(pos)] = val;
    }
    void set_red_value(uint8_t val) {
        set_color_value(val, color_pos::red);
    }
    void set_green_value(uint8_t val) {
        set_color_value(val, color_pos::green);
    }
    void set_blue_value(uint8_t val) {
        set_color_value(val, color_pos::blue);
    }
    void set_alpha_value(uint8_t val) {
        set_color_value(val, color_pos::alpha);
    }
};
//struct pixel_color {
//    rgba_color color;
//};

class image {
	int width; 
	int height;
    std::vector<rgba_color> pixels;
public:
	image(int width, int height): width(width), height(height) {
        pixels.reserve(width*height);
        pixels.assign(width*height, rgba_color(0xFF00FF00));
	}
    ~image(){}
    rgba_color* get_pixels_buffer(){
        return pixels.data();
    }
};



class sdl_image {
    int width;
    int height;
//    std::vector<rgba_color> pixels;
    std::unique_ptr<SDL_Surface> surface;
public:
    sdl_image(int width, int height): width(width), height(height) {
        Uint32 rmask, gmask, bmask, amask;
        #if SDL_BYTEORDER == SDL_BIG_ENDIAN
            rmask = 0xff000000;
            gmask = 0x00ff0000;
            bmask = 0x0000ff00;
            amask = 0x000000ff;
        #else
            rmask = 0x000000ff;
            gmask = 0x0000ff00;
            bmask = 0x00ff0000;
            amask = 0xff000000;
        #endif
        SDL_Surface* srfc_pointer = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
        surface.reset(srfc_pointer);
    }
    ~sdl_image(){}
    void* get_pixels_buffer(){
        return surface.get()->pixels;
    }
    int get_pitch(){
        return surface.get()->pitch;
    }
    int draw_rect(int x, int y, int width, int height, uint32_t color){
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = width;
        rect.h = height;

        return SDL_FillRect(surface.get(), &rect, color);
    }
    int draw_rect(const SDL_Rect& rect, uint32_t color){
        return SDL_FillRect(surface.get(), &rect, color);
    }
};

#endif  /* COLOR_HPP */
