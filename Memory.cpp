#include "Memory.h"
#include <iostream>
#include <iomanip> 
#include <string>

Memory::Memory() : IO_Ports() {

}

bool Memory::is_DMG() {
    return (*this)[0xFF50] == 0x00; 
}

unsigned char& Memory::operator[](unsigned int i) {
    if (i < 0x0100 && is_DMG()) {
        //Bootstrapping ROM 
        return bootstrap[i];
    } else if (i < 0x4000) {
        //ROM Bank 0
        return cartridge[i];

    } else if ((i >= 0x4000) && (i < 0x8000)) {
        //Switchable ROM Bank 
        return cartridge[i];

    } else if ((i >= 0x8000) && (i < 0xA000)) {
        //Video RAM 
        return graphics[i];

    } else if ((i >= 0xA000) && (i < 0xC000)) {
        //Switchable RAM Bank 
        return cartridge[i]; 

    } else if ((i >= 0xC000) && (i < 0xE000)) {
        //Internal RAM
        return main_mem[i - 0xC000];

    } else if ((i >= 0xE000) && (i < 0xFE00)) {
        //Echo of Internal RAM
        return main_mem[i - 0xE000];

    } else if ((i >= 0xFE00) && (i < 0xFEA0)) {
        //Sprite Attrib Memory (OAM)
        return graphics[i];

    } else if ((i >= 0xFEA0) && (i < 0xFF00)) {
        //*** UNUSED ***
        return unused[i - 0xFEA0];

    } else if ((i >= 0xFF00) && (i < 0xFF4C)) {
        //I/O Ports
        return handle_IO(i);

    } else if ((i >= 0xFF4C) && (i < 0xFF80)) {
        //*** UNUSED?? ***
        return handle_IO(i);

    } else if ((i >= 0xFF80) && (i < 0xFFFF)) {
        //Internal RAM 
        return hi_mem[i - 0xFF80]; 

    } else if (i == 0xFFFF) {
        // Interrupt Enable Register
        return interrupt_enable_register;

    } else { 
        //Some  kind of error? 
        return NONE;
    }
}

unsigned char& Memory::handle_IO(unsigned int i) {
    switch (i) {
        case 0xFF40: // LCDC
            return graphics.LCDC; 
        case 0xFF41: // LCDC Status
            return graphics.LCDC_status; 
        case 0xFF42: // Scroll Y
            return graphics.scroll_y;
        case 0xFF43: // Scroll X
            return graphics.scroll_x; 
        case 0xFF44: // Line Y
            return graphics.line_y;
        case 0xFF45: // Line Y Compare 
            return graphics.line_y_cmp;
        case 0xFF46: // DMA Start address
            return graphics.DMA_addr;
        case 0xFF47: // BG & Window Pallete Data
            return graphics.bgp;
        case 0xFF48: // Object Pallette 0 Data
            return graphics.obp0;
        case 0xFF49: // Object Pallette 1 Data
            return graphics.obp1;
        case 0xFF4A: // Window Y
            return graphics.window_y;
        case 0xFF4B: // Window X
            return graphics.window_x;
    }

    //Error?
    return IO_Ports[i - 0xFF00];
}

/*
int main(){
    Memory m;
    m.cartridge.load_rom("/users/ejfs1g10/Downloads/Pokemon Red/Pokemon Red.gb");
    
    //unsigned char c = m[0];
    //cout << setfill('0') << setw(2) << hex << (unsigned int) c; 

    return 0;
}
*/
