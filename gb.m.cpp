#include <cpu.h>
#include <iostream>


int main() {
    CPU cpu; 
    cpu.memory.cartridge.load_rom("../res/opus5.gb");

    cpu.print_state();

//    for (int i = 0; i < 6 + 3 * (0x9FFF - 0x8000) + 26 + 30 + 50 + 3948 + 46 + 6 + 58 + 79 + 120 + 13 + 18500 + 375 + 102; i++) {
    int i = 0;
    while (true) {
        i++;
        //cpu.memory.graphics.dump_tiles();
        cpu.fetch_and_execute();
        cpu.print_state();
        cpu.memory.graphics.step(1);
        if ((i % 300) == 0) cpu.memory.graphics.dump_display();
    }

    //cpu.memory.graphics.dump_state();
    //cpu.memory.graphics.dump_tiles();
    //cpu.memory.graphics.dump_map_indices();

    std::cout << std::endl; //XXX: Voodoo...
    return 0; 
}
