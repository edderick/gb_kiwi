#ifndef MEMORY_H
#define MEMORY_H

#include "Cart.h"
#include "Bootstrap.h"
#include "Graphics.h"

namespace gbemu {

class Memory {
    private:
        // PRIVATE DATA
        unsigned char d_interrupt_enable_register;
        unsigned char d_unused[0xFF00 - 0xFEA0]; // Placeholder...
        unsigned char d_NONE; // Placeholder...
        unsigned char d_main_mem[0xE000 - 0xC000];
        unsigned char d_hi_mem[0xFFFF - 0xFF80];
        //TODO: Pull these out into actual classes
        unsigned char d_IO_Ports[0xFF80 - 0xFF00];

        Bootstrap d_bootstrap;
        Cartridge *d_cartridge;
        IGraphics  *d_graphics;

    private:
        // PRIVATE ACCESSORS
        unsigned char& handle_IO(unsigned int i);
        bool is_DMG() const;

    private:
        // NOT IMPLEMENTED
        Memory(const Memory&);           // = delete
        Memory operator=(const Memory&); // = delete

    public:
        // CREATORS
        Memory(Cartridge *cartridge, IGraphics *graphics);

    public:
        // PUBLIC ACCESSORS
        unsigned char& get(unsigned int);
        const unsigned char& get(unsigned int) const;
        unsigned char& operator[](unsigned int);
        const unsigned char& operator[](unsigned int) const;
};

} // Close Namespace gbemu

#endif
