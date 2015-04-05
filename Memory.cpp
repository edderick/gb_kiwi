#include "Memory.h"
#include <iostream>
#include <iomanip> 
#include <string>

namespace gbemu {

Memory::Memory(Cartridge *cartridge,
               IGraphics *graphics)
: d_IO_Ports()
, d_cartridge(cartridge)
, d_graphics(graphics)
{
}

bool Memory::is_DMG() const {
    return this->get(0xFF50) == 0x00;
}

const unsigned char& Memory::operator[](unsigned int i) const {
    return this->get(i);
}

unsigned char& Memory::operator[](unsigned int i) {
    return this->get(i);
}

const unsigned char& Memory::get(unsigned int i) const {
    return (const_cast<Memory*>(this))->get(i);
}

unsigned char& Memory::get(unsigned int i) {
    if (i < 0x0100 && is_DMG()) {
        //Bootstrapping ROM 
        return d_bootstrap[i];
    } else if (i < 0x4000) {
        //ROM Bank 0
        return (*d_cartridge)[i];

    } else if ((i >= 0x4000) && (i < 0x8000)) {
        //Switchable ROM Bank 
        return (*d_cartridge)[i];

    } else if ((i >= 0x8000) && (i < 0xA000)) {
        //Video RAM 
        return (*d_graphics)[i];

    } else if ((i >= 0xA000) && (i < 0xC000)) {
        //Switchable RAM Bank 
        return (*d_cartridge)[i];

    } else if ((i >= 0xC000) && (i < 0xE000)) {
        //Internal RAM
        return d_main_mem[i - 0xC000];

    } else if ((i >= 0xE000) && (i < 0xFE00)) {
        //Echo of Internal RAM
        return d_main_mem[i - 0xE000];

    } else if ((i >= 0xFE00) && (i < 0xFEA0)) {
        //Sprite Attrib Memory (OAM)
        return (*d_graphics)[i];

    } else if ((i >= 0xFEA0) && (i < 0xFF00)) {
        //*** UNUSED ***
        return d_unused[i - 0xFEA0];

    } else if ((i >= 0xFF00) && (i < 0xFF4C)) {
        //I/O Ports
        return handle_IO(i);

    } else if ((i >= 0xFF4C) && (i < 0xFF80)) {
        //*** UNUSED?? ***
        return handle_IO(i);

    } else if ((i >= 0xFF80) && (i < 0xFFFF)) {
        //Internal RAM 
        return d_hi_mem[i - 0xFF80];

    } else if (i == 0xFFFF) {
        // Interrupt Enable Register
        return d_interrupt_enable_register;

    } else { 
        //Some  kind of error? 
        return d_NONE;
    }
}

unsigned char& Memory::handle_IO(unsigned int i) {
    switch (i) {
        case 0xFF40: // LCDC
            return d_graphics->d_LCDC;
        case 0xFF41: // LCDC Status
            return d_graphics->d_LCDC_status;
        case 0xFF42: // Scroll Y
            return d_graphics->d_scroll_y;
        case 0xFF43: // Scroll X
            return d_graphics->d_scroll_x;
        case 0xFF44: // Line Y
            return d_graphics->d_line_y;
        case 0xFF45: // Line Y Compare 
            return d_graphics->d_line_y_cmp;
        case 0xFF46: // DMA Start address
            return d_graphics->d_DMA_addr;
        case 0xFF47: // BG & Window Pallete Data
            return d_graphics->d_bgp;
        case 0xFF48: // Object Pallette 0 Data
            return d_graphics->d_obp0;
        case 0xFF49: // Object Pallette 1 Data
            return d_graphics->d_obp1;
        case 0xFF4A: // Window Y
            return d_graphics->d_window_y;
        case 0xFF4B: // Window X
            return d_graphics->d_window_x;
    }

    //Error?
    return d_IO_Ports[i - 0xFF00];
}

} // Close Namespace gbemu

// TODO: Pull out into tests
/*
int main(){
    Memory m;
    m.cartridge.load_rom("/users/ejfs1g10/Downloads/Pokemon Red/Pokemon Red.gb");
    
    //unsigned char c = m[0];
    //cout << setfill('0') << setw(2) << hex << (unsigned int) c; 

    return 0;
}
*/
