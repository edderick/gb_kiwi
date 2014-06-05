#ifndef MEMORY_H
#define MEMORY_H

#include "Cart.h"
#include "Bootstrap.h"

class Memory {
    unsigned char interrupt_enable_register; 
    unsigned char NONE; // Placeholder...
    unsigned char main_mem[0xE000 - 0xC000];
    unsigned char hi_mem[0xFFFF - 0xFF80];
    unsigned char IO_Ports[0xFF4C - 0xFF00];
    bool is_DMG();
public: 
    Cartridge cartridge; 
    Bootstrap bootstrap;
    unsigned char& operator[](unsigned int); 
};

#endif
