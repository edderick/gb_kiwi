#include "Graphics.h"
#include <iostream>
#include <iomanip>

using namespace std;
Graphics::Graphics() {
    //XXX: LINE Y SET TO 90 to trick ROM...
    line_y = 0x90;
}

void Graphics::step(int clock_cycle_delta) {
    //Do cool graphics stuff
}

unsigned char& Graphics::operator[](unsigned int i){
    return VRAM[i - 0x8000];
}

void Graphics::dump_state() {
   cout << "LCDC: " << hex << (int) LCDC << "  ";
   cout << "LCDC Status: " << hex << (int) LCDC_status << "\n";
   cout << "scroll_y: " << hex << (int) scroll_y << "  ";
   cout << "scroll_x: " << hex << (int) scroll_x << "\n";
   cout << "line_y: " << hex << (int) line_y << "  ";
   cout << "line_y_cmp: " << hex << (int) line_y_cmp << "\n";
   cout << "window_y: " << hex << (int) window_y << "  ";
   cout << "window_x: " << hex << (int) window_x << "\n";
}

void Graphics::dump_tiles() {
    for (int i = 0; i < 384; i++) {
        cout << "HEX " << setw(3) << setfill('0') << dec << i << ": ";
        for (int j = 0; j < 16; j++) { 
            cout << hex << setw(2) << setfill('0') <<(int) VRAM[i * 16 + j];
        }
        cout << endl;
    } 
}
