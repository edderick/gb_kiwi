#include "Memory.h"
#include <iostream>
#include <iomanip> 
#include <string>

bool Memory::is_DMG() {
    return (*this)[0xFF50] == 0x00; 
}

unsigned char& Memory::operator[](unsigned int i) {
    if (i < 256 && is_DMG()) {
        //Bootstrapping ROM 
        return bootstrap[i];
    } else if (i < 0x4000) {
        //ROM Bank 0
        return cartridge[i];
    } else if (i < 0x8000) {
        //Switchable ROM Bank 
        return NONE;
    } else if (i < 0xA000) {
        //Video RAM 
        return NONE;
    } else if (i < 0xC000) {
        //Switchable RAM Bank 
        return NONE; 
    } else if (i < 0xE000) {
        //Internal RAM
        return main_mem[i - 0xC000];
    } else if (i < 0xFE00) {
        //Echo of Internal RAM
        return main_mem[i - 0xE000];
    } else if (i < 0xFEA0) {
        //Sprite Attrib Memory (OAM)
        return NONE;
    } else if (i < 0xFF00) {
        //Empty but unusable I/O
        return NONE;
    } else if (i < 0xFF4C) {
        //I/O Ports
        return NONE;
    } else if (i < 0xFF80) {
        //Empty but unusable for I/O
        return NONE;
    } else if (i < 0xFFFF) {
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

/*
int main(){
    Memory m;
    m.cartridge.load_rom("/users/ejfs1g10/Downloads/Pokemon Red/Pokemon Red.gb");
    
    //unsigned char c = m[0];
    //cout << setfill('0') << setw(2) << hex << (unsigned int) c; 

    return 0;
}
*/
