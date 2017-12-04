#include "graphics.h"
#include "cart.h"
#include "cpu.h"

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
    while (true) {
        i++;
        cpu.fetch_and_execute();
        graphics.step(1);
        if ((i % 300) == 0) graphics.dump_display();
    }

    std::cout << std::endl; //XXX: Voodoo...
    return 0; 
}
