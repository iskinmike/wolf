#ifndef GAME_FIELD_HPP
#define GAME_FIELD_HPP

#include "color.hpp"

struct blocks_info{
    int blocks_x;
    int blocks_y;
    int block_x_size;
    int block_y_size;
    blocks_info(int x,int y, int size_x, int size_y) : blocks_x(x), blocks_y(y), block_x_size(size_x), block_y_size(size_y) {}
};


class game_field
{
    sdl_image field;
    int blocks_x;
    int blocks_y;
    int block_x_size;
    int block_y_size;
    std::vector<SDL_Rect> blocks;
    SDL_Rect rectangle;
    std::vector<int> field_description;
public:
    int width;
    int height;
    game_field(int width, int height): width(width), height(height), field(width, height) {
        block_x_size = 20;
        block_y_size = 20;
        blocks_x = width/block_x_size;
        blocks_y = height/block_y_size;
        rectangle.x = 0;
        rectangle.y = 0;
        rectangle.w = width;
        rectangle.h = height;
        blocks.reserve(blocks_x*blocks_y);
        for (int i = 0; i < blocks_x; ++i) {
            for (int j = 0; j < blocks_y; ++j) {
                SDL_Rect rect;
                rect.w = block_x_size;
                rect.h = block_y_size;
                rect.x = i*rect.w;
                rect.y = j*rect.h;

                blocks.push_back(rect);
            }
        }
        field_description = {
          8,8,8,8,8,8,8,8,8,8,8,4,4,4,4,4,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
          8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,
//            1,2,3,4,5,6,7,8,
//            0,0,0,0,0,0,0,0,
//            0,0,0,0,0,0,0,0,
//            0,0,0,0,0,0,0,0,
//            0,0,0,0,0,0,0,0,
//            0,0,0,0,0,0,0,0,
          8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,8,
          8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,8,
          8,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,8,
          8,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,8,
          8,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,8,
          8,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,8,
          8,0,0,0,0,0,0,0,0,5,0,0,0,3,3,5,5,5,3,3,0,0,0,6,0,0,0,0,0,0,0,8,
          8,0,0,0,0,0,0,0,0,5,0,0,0,0,0,2,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,8,
          8,0,0,0,0,0,0,0,0,5,0,0,0,0,0,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,8,
          8,0,0,0,0,0,0,0,0,5,0,0,0,0,0,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,8,
          7,0,0,0,0,0,0,0,0,5,0,0,0,0,0,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,8,
          7,0,0,0,0,0,0,0,0,5,0,0,0,0,0,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,8,
          7,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,
          7,0,0,0,0,0,0,0,0,1,1,1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,
          7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,
          7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,
          8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,
          8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,
          8,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,
          8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,
          8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,
          8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8};
    }

    ~game_field(){
    }

    blocks_info get_blocks_info() {
        std::cout << "blocks_info: [" << blocks_x << ", " << blocks_y << "]: " << blocks_y*blocks_x << std::endl;
        return blocks_info(blocks_x, blocks_y, block_x_size, block_y_size);
    }

    int change_field_background_color(uint32_t color) {
        return field.draw_rect(0, 0, width, height, color);
    }
    void* get_field_pixels_buffer(){
        return field.get_pixels_buffer();
    }
    int get_pitch(){
        return field.get_pitch();
    }

    int set_rect_color(int x, int y, uint32_t color) {
        bool not_draw = false;
        if (x >= blocks_x || y >= blocks_y || 0 > x || 0 > y) {
            not_draw = true; // error
        }
        int pos = x*blocks_y + y;
        if (pos > blocks.size()-1) {
            not_draw = true; // error
        }
//        std::cout << "[" << x << ", " << y<< "]: " << pos << " | " << not_draw << "]" << std::endl;

        if (not_draw) {
            return -1;
        }
        return field.draw_rect(blocks.at(pos), color);
    }

    void generate_game_field(){

        change_field_background_color(static_cast<uint32_t> (hex_colors::white));

        for (int i = 0; i < blocks_x; ++i) {
            for (int j = 0; j < blocks_y; ++j) {
                int pos = j*blocks_x + i;
                switch (field_description.at(pos)) {
                case 1: {
                    set_rect_color(i,j,static_cast<uint32_t> (hex_colors::red));
                    break;
                }
                case 2: {
                    set_rect_color(i,j,static_cast<uint32_t> (hex_colors::blue));
                    break;
                }
                case 3: {
                    set_rect_color(i,j,static_cast<uint32_t> (hex_colors::green));
                    break;
                }
                case 4: {
                    set_rect_color(i,j,static_cast<uint32_t> (hex_colors::FireBrick));
                    break;
                }
                case 5: {
                    set_rect_color(i,j,static_cast<uint32_t> (hex_colors::Gold));
                    break;
                }
                case 6: {
                    set_rect_color(i,j,static_cast<uint32_t> (hex_colors::LightGray));
                    break;
                }
                case 7: {
                    set_rect_color(i,j,static_cast<uint32_t> (hex_colors::LightBlue));
                    break;
                }
                case 8: {
                    set_rect_color(i,j,static_cast<uint32_t> (hex_colors::yellow));
                    break;
                }
                default: {
                    set_rect_color(i,j,static_cast<uint32_t> (hex_colors::white));
                }
                }
            }
        }
    }

    SDL_Rect* get_field_rectangle(){
        return &rectangle;
    }
};


#endif  /* GAME_FIELD_HPP */
