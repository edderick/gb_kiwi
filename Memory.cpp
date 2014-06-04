#include "Memory.h"

char& Memory::operator[](unsigned int i) {
    if (i < 0x4000) {
        //ROM Bank 0
        return NULL;
    } else if (i < 0x8000) {
        //Switchable ROM Bank 
        return NULL;
    } else if (i < 0xA000) {
        //Video RAM 
        return NULL;
    } else if (i < 0xC000) {
        //Switchable RAM Bank 
        return NULL; 
    } else if (i < 0xE000) {
        //Internal RAM
        return main_mem[i - 0xC000];
    } else if (i < 0xFE00) {
        //Echo of Internal RAM
        return main_mem[i - 0xE000];
    } else if (i < 0xFEA0) {
        //Sprite Attrib Memory (OAM)
        return NULL;
    } else if (i < 0xFF00) {
        //Empty but unusable I/O
        return NULL;
    } else if (i < 0xFF4C) {
        //I/O Ports
        return NULL;
    } else if (i < 0xFF80) {
        //Empty but unusable for I/O
        return NULL;
    } else if (i < 0xFFFF) {
        //Internal RAM 
        return hi_mem[i - 0xFF80]; 
    } else if (i == 0xFFFF) {
        // Interrupt Enable Register
        return interrupt_enable_register;
    } else {
        //Some kind of error? 
        return NULL;
    }
}

int main(){
    Memory m;
    m[0] = 5; 
    return 0;
}
