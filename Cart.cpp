#include "Cart.h"
#include <fstream> 
#include <iostream>
#include <iomanip>  

void Cartridge::load_rom(string filename) {
    ifstream f(filename, ios::binary);
    
    while (f) {
        char c;
        f.get(c);
        if (f) rom.push_back(c);
    }
}

unsigned char& Cartridge::operator[](unsigned int i) {
    return rom[i];
}

unsigned int Cartridge::size() {
    return rom.size();
}

bool Cartridge::check_graphic() {
    unsigned char expected[] = 
        {0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b, 0x03, 0x73, 0x00, 0x83, 
         0x00, 0x0c, 0x00, 0x0d, 0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e, 
         0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd, 0xd9, 0x99, 0xbb, 0xbb, 0x67, 0x63, 
         0x6e, 0x0e, 0xec, 0xcc, 0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e};

    cout << "Checking Nintendo Graphic: \n";

    for (int i = 0x0104; i <= 0x0133 ; i++) {
        if ((*this)[i]  != expected[i - 0x0104]) {
            return false;  
        }
        cout << setfill('0') << setw(2) << hex << (short) ((unsigned char) ((*this)[i])) << " "; 
    }

    cout << "\nPass!"<< endl;
    return true;
}

string Cartridge::get_title() {
    string title; 
    for (int i = 0x0134; i <= 0x0142 ; i++) {
        title += ((*this)[i]); 
    }
    return title; 
}

bool Cartridge::is_color() {
    return (*this)[0x0143] == 0x80;
}

unsigned char Cartridge::get_type() {
    return (*this)[0x0147];
}

unsigned char Cartridge::get_rom_size_code(){
    return (*this)[0x0148];
}

unsigned char Cartridge::get_ram_size_code(){
    return (*this)[0x0149];
}
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
