#ifndef CART_H
#define CART_H

#include <string> 
#include <vector>

using namespace std;
class Cartridge {
        vector<unsigned char> rom; 
    public: 
        unsigned int size();
        unsigned char& operator[](unsigned int i);
        void load_rom(string filename);
        bool check_graphic();
        string get_title(); 
        bool is_color();
        unsigned char get_type();
        unsigned char get_rom_size_code();
        unsigned char get_ram_size_code();
};

#endif
