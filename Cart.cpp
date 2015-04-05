#include "Cart.h"
#include <fstream> 
#include <sstream>
#include <iostream>
#include <iomanip>  

namespace gbemu {

void Cartridge::load_rom(const std::string &filename) {
    std::ifstream f(filename.c_str(), std::ios::binary);
    
    while (f) {
        char c;
        f.get(c);
        if (f) d_rom.push_back(c);
    }
}

unsigned char& Cartridge::operator[](unsigned int i) {
    return d_rom[i];
}

const unsigned char& Cartridge::operator[](unsigned int i) const {
    return d_rom[i];
}

bool Cartridge::check_graphic() const {
    unsigned char expected[] = 
        {0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b, 0x03, 0x73, 0x00, 0x83, 
         0x00, 0x0c, 0x00, 0x0d, 0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e, 
         0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd, 0xd9, 0x99, 0xbb, 0xbb, 0x67, 0x63, 
         0x6e, 0x0e, 0xec, 0xcc, 0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e};

    // TODO: Find a logging library...
    std::cout << "Checking Nintendo Graphic: \n";

    for (int i = 0x0104; i <= 0x0133 ; i++) {
        if ((*this)[i]  != expected[i - 0x0104]) {
            return false;  
        }
        std::cout << std::setfill('0') << std::setw(2) << std::hex
                  << (short) ((unsigned char) ((*this)[i])) << " ";
    }

    std::cout << "\nPass!\n" << std::flush;
    return true;
}

std::string Cartridge::get_title() const {
    std::stringstream title;
    for (int i = 0x0134; i <= 0x0142 ; i++) {
        title << ((*this)[i]);
    }
    return title.str();
}

bool Cartridge::is_color() const {
    return (*this)[0x0143] == 0x80;
}

unsigned char Cartridge::get_type() const {
    return (*this)[0x0147];
}

unsigned char Cartridge::get_rom_size_code() const {
    return (*this)[0x0148];
}

unsigned char Cartridge::get_ram_size_code() const {
    return (*this)[0x0149];
}

}  // Close Namespace gbemu

// TODO: Pull Out into tests
/*
int main() {
    Cartridge c;
    c.load_rom("/users/ejfs1g10/Downloads/Pokemon Red/Pokemon Red.gb");
    c.check_graphic();
    cout << "Game title: " << c.get_title() << endl;
    cout << "Is Colour: " << c.is_color() << endl;
    cout << "Cart Type: " << hex << (int) c.get_type() << endl;
    cout << "ROM Size Code: " << hex << (int) c.get_rom_size_code() << endl;
    cout << "RAM Size Code: " << hex << (int) c.get_ram_size_code() << endl;
    return 0;
}
*/
