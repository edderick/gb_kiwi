#ifndef MEMORY_H
#define MEMORY_H

#include "Cart.h"
#include "Bootstrap.h"
#include "Graphics.h"

class Memory {
    unsigned char interrupt_enable_register; 
    unsigned char NONE; // Placeholder...
    unsigned char main_mem[0xE000 - 0xC000];
    unsigned char hi_mem[0xFFFF - 0xFF80];
    //TODO: Pull these out into actual classes
    unsigned char IO_Ports[0xFF4C - 0xFF00];
    unsigned char VRAM[0xA000 - 0x8000];

    unsigned char& handle_IO(unsigned int i);

    bool is_DMG();
public: 
    Cartridge cartridge; 
    Bootstrap bootstrap;
    Graphics graphics; 
    unsigned char& operator[](unsigned int); 
};

#endif
