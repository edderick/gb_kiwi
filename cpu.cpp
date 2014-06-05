#include "cpu.h"

int CPU::fetch_and_execute() {
    // Read in opcode at PC
    // Execute OP 
    // Update PC?

    return 0;
}

int main() {

    CPU cpu; 
    cpu.memory.cartridge.load_rom("/users/ejfs1g10/Downloads/Pokemon Red/Pokemon Red.gb");

    return 0; 
}
