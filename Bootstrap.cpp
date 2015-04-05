#include "Bootstrap.h"
#include <fstream> 
#include <iostream>

namespace gbemu {

Bootstrap::Bootstrap() {
    std::ifstream f("../res/DMG_ROM.bin", std::ios::binary);
    
    while (f) {
        char c;
        f.get(c);
        if (f) d_rom.push_back(c);
    }
}

unsigned char& Bootstrap::operator[](unsigned int i) {
    return d_rom[i];
}

unsigned int Bootstrap::size() {
    return d_rom.size();
}

} // Close Namespace gbemu
