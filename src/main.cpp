#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <thread>



#include "preconstruction_class.hpp"
#include "world.hpp"


int main(int argc, char const *argv[])
{
    std::cout << "test" << std::endl;
    test_construction_token tok;
    tok.i = 1;
    test tt(std::move(tok));


    std::thread world_thread = std::thread([](){
        world_construction_token&& world_token = world::construct_token("Wolf", 100, 100, 640, 480);
        std::cout << "[" << world_token.error << "]" << std::endl;
        if (world_token.error.empty()) {
            world test_world(std::move(world_token));
            test_world.run_loop();
            sleep(3);
        }
    });

    if (world_thread.joinable()) {
        world_thread.join();
    }

    return 0;
}
