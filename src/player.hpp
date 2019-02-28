#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "color.hpp"

struct player_position {
	int x,y;
};
struct player_sigh {
    float sigh_angle;
    float direction_angle;
};

const int player_size_x = 10;
const int player_size_y = 10;

class player
{
    player_position position;
    player_sigh direction;
    SDL_Rect rect;
    sdl_image sprite;
//    double radian_scale = 3.14/360;
public:
    hex_colors color;
    player(int x, int y): sprite(player_size_x,player_size_y){
        position.x = x;
        position.y = y;
        direction.direction_angle = 0;
        direction.sigh_angle = 64;
        rect.h = player_size_x;
        rect.w = player_size_y;
        rect.x = position.x;
        rect.y = position.y;
        color = hex_colors::Indigo;
        sprite.draw_rect(0, 0, player_size_x, player_size_y, static_cast<uint32_t> (color));
    }
    ~player(){}
    void teleport_to(int x, int y) {
        position.x = x;
        position.y = y;
    }
    player_position get_pos(){
        return position;
    }

    void rotate(double direction_angle) {
        direction.direction_angle = direction_angle;
    }
    void add_rotate(double direction_angle) {
        direction.direction_angle += direction_angle;
    }
    void add_rotate_degree(double angle) {
        direction.direction_angle += angle;
        if (direction.direction_angle >= 360) {
            direction.direction_angle -= 360;
        }
    }
    player_sigh get_sight(){
        return direction;
    }
    SDL_Rect* get_field_rectangle(){
        return &rect;
    }
    void* get_field_pixels_buffer(){
        return sprite.get_pixels_buffer();
    }
    int get_pitch(){
        return sprite.get_pitch();
    }
    void reset_rect(){
        rect.x = position.x;
        rect.y = position.y;
    }

    void change_pos_x(int shift) {
        position.x += shift;
        reset_rect();
    }
    void change_pos_y(int shift) {
        position.y += shift;
        reset_rect();
    }

    void move_up(int shift){
        change_pos_y((-1)*shift);
    }
    void move_down(int shift){
        change_pos_y(shift);
    }
    void move_left(int shift){
        change_pos_x((-1)*shift);
    }
    void move_right(int shift){
        change_pos_x(shift);
    }
};




#endif  /* PLAYER_HPP */
