#include "Graphics.h"

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

