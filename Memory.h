#ifndef MEMORY_H
#define MEMORY_H

#include "Cart.h"

class Memory {
    char interrupt_enable_register; 
    char NONE; // Placeholder...
    char main_mem[0xE000 - 0xC000];
    char hi_mem[0xFFFF - 0xFF80];
public: 
    Cartridge cartridge; 
    char& operator[](unsigned int); 
};

#endif
