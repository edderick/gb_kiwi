#include "Bootstrap.h"
#include <fstream> 
#include <iostream>
#include <iomanip>  

Bootstrap::Bootstrap() {
    ifstream f("../res/DMG_ROM.bin", ios::binary);
    
    while (f) {
        char c;
        f.get(c);
        if (f) rom.push_back(c);
    }
}

unsigned char& Bootstrap::operator[](unsigned int i) {
    return rom[i];
}

unsigned int Bootstrap::size() {
    return rom.size();
}

/*
int main() {
    Bootstrap b;
    for (unsigned int i = 0; i < b.size(); i++) {
        cout << setw(2) << setfill('0') << hex << (int) b[i] << " ";
    }
    return 0;
}
*/
