#include "graphics.h"
#include "cart.h"
#include "cpu.h"

#include <iostream>

int main() {
    using namespace gbemu;

    Graphics graphics;

    Cartridge cartridge;

    CPU cpu(&cartridge, &graphics);

    cpu.print_state();
    cartridge.load_rom("../res/Tetris.gb");
//    for (int i = 0; i < 6 + 3 * (0x9FFF - 0x8000) + 26 + 30 + 50 + 3948 + 46 + 6 + 58 + 79 + 120 + 13 + 18500 + 375 + 102; i++) {
    int i = 0;
    while (true) {
        i++;
        //cpu.memory.graphics.dump_tiles();
        cpu.fetch_and_execute();
        cpu.print_state();
        graphics.step(1);
        if ((i % 300) == 0) graphics.dump_display();
    }

    //cpu.memory.graphics.dump_state();
    //cpu.memory.graphics.dump_tiles();
    //cpu.memory.graphics.dump_map_indices();

    std::cout << std::endl; //XXX: Voodoo...
    return 0; 
}
