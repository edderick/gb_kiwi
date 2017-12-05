#include "Graphics.h"
#include "Cart.h"
#include "cpu.h"
#include <SDL2/SDL.h>

#include <iostream>

int main(int argc, char *argv[]) {
    using namespace gbemu;

    if (argc != 2) {
        std::cout << "Usage: ./GB_Kiwi <path_to_rom>\n";
        return 1;
    }

    Graphics graphics;
    Cartridge cartridge;
    CPU cpu(&cartridge, &graphics);

    cartridge.load_rom(argv[1]);

    int i = 0;
    SDL_Event event;

    while (true) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                   		case SDLK_LEFT:
                            if (cpu.memory().left) break; 
							std::cout << "Left Pressed\n";
							cpu.memory().left = true;
							break;
						case SDLK_RIGHT:
                            if (cpu.memory().right) break; 
							std::cout << "Right Pressed\n";
							cpu.memory().right = true;
							break;
						case SDLK_UP:
                            if (cpu.memory().up) break; 
							std::cout << "Up Pressed\n";
							cpu.memory().up = true;
							break;
						case SDLK_DOWN:
                            if (cpu.memory().down) break; 
							std::cout << "Down Pressed\n";
							cpu.memory().down = true;
							break; 
						case SDLK_SPACE: 
                            if (cpu.memory().select) break; 
							std::cout << "Select Pressed\n";
							cpu.memory().select = true;
							break;
						case SDLK_RETURN: 
                            if (cpu.memory().start) break; 
							std::cout << "Start Pressed\n";
							cpu.memory().start = true;
							break;
						case SDLK_x:
                            if (cpu.memory().b) break; 
							std::cout << "B Pressed\n";
							cpu.memory().b = true;
							break;
						case SDLK_z: 
                            if (cpu.memory().a) break; 
							std::cout << "A Pressed\n";
							cpu.memory().a = true;
							break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                   		case SDLK_LEFT:
							std::cout << "Left Released\n";
							cpu.memory().left = false;
							break;
						case SDLK_RIGHT:
							std::cout << "Right Released\n";
							cpu.memory().right = false;
							break;
						case SDLK_UP:
							std::cout << "Up Released\n";
							cpu.memory().up = false;
							break;
						case SDLK_DOWN:
							std::cout << "Down Released\n";
							cpu.memory().down = false;
							break; 
						case SDLK_SPACE: 
							std::cout << "Select Released\n";
							cpu.memory().select = false;
							break;
						case SDLK_RETURN: 
							std::cout << "Start Released\n";
							cpu.memory().start = false;
							break;
						case SDLK_x:
							std::cout << "B Released\n";
							cpu.memory().b = false;
							break;
						case SDLK_z: 
							std::cout << "A Released\n";
							cpu.memory().a = false;
							break;
                    }
                    break;

                case SDL_QUIT:
                    printf( "GAME OVER, KIDDO!\n" );
                    return 0; 

                default:
                    break;
            }
        }  

        i++;
        cpu.fetch_and_execute();
        graphics.step(1);
        if ((i % 600) == 0) graphics.dump_display();
    }

    std::cout << std::endl; //XXX: Voodoo...
    return 0; 
}
