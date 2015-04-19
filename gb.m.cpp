#include "graphics.h"
#include "cart.h"
#include "cpu.h"

#include <iostream>

int main() {
    using namespace gbemu;

    Graphics graphics;
    Cartridge cartridge;
    CPU cpu(&cartridge, &graphics);

    cartridge.load_rom("../res/Tetris.gb");

    int i = 0;
    while (true) {
        i++;
        cpu.fetch_and_execute();
        graphics.step(1);
        if ((i % 300) == 0) graphics.dump_display();
    }

    std::cout << std::endl; //XXX: Voodoo...
    return 0; 
}
