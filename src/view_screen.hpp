#ifndef VIEW_SCREEN_HPP
#define VIEW_SCREEN_HPP

#include "color.hpp"

class view_screen
{
    int m_width;
    int m_height;
    sdl_image field;
    SDL_Rect base_rect;
    hex_colors base_color;
public:
    view_screen(int width, int height) : m_width(width), m_height(height), field(width,height) {
        base_color = hex_colors::LightGray;
        base_rect.w = width;
        base_rect.h = height;
        base_rect.x = width;
        base_rect.y = 0;
        field.draw_rect(0, 0, width, height, static_cast<uint32_t> (base_color));
    }
    ~view_screen(){}
    SDL_Rect* get_field_rectangle(){
        return &base_rect;
    }
    void* get_field_pixels_buffer(){
        return field.get_pixels_buffer();
    }
    int get_pitch(){
        return field.get_pitch();
    }
    int draw_rect(int x, int y, int width, int height, hex_colors color){
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = width;
        rect.h = height;
        return field.draw_rect(rect, static_cast<uint32_t> (color));
    }
    int draw_rect(const SDL_Rect& rect, hex_colors color){
        return field.draw_rect(rect, static_cast<uint32_t> (color));
    }
    int draw_view_strip(point_position view_pos, point_position end_ray_pos, uint32_t color, int counter) {
        int dx = abs(view_pos.x - end_ray_pos.x);
        int dy = abs(view_pos.y - end_ray_pos.y);
        double len = sqrt(dx*dx + dy*dy);
        double alpha = 25000;
        double height = alpha*(1/len);

        SDL_Rect rect;
        const int pixel_width = 10;
        rect.x = pixel_width*counter;
        rect.y = (m_height - height)/2;
        rect.w = pixel_width;
        rect.h = height;
        field.draw_rect(rect, color);
    }
    void clear(){
        field.draw_rect(0, 0, m_width, m_height, static_cast<uint32_t> (base_color));
    }
};


#endif  /* VIEW_SCREEN_HPP */
