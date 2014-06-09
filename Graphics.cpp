#include "Graphics.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;
Graphics::Graphics() : VRAM(), line_y(0x90) {
    //XXX: LINE Y SET TO 90 to trick ROM...
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
        stringstream ss; 
        bool b = false;
        for (int j = 0; j < 16; j++) { 
            if (VRAM[i * 16 + j] != 0) b = true;
        }
        
        if (b) {
            cout << "HEX " << setw(3) << setfill('0') << dec << i << ": ";
            for (int j = 0; j < 16; j++) { 
                ss << hex << setw(2) << setfill('0') << (int) VRAM[i * 16 + j];
            }
            cout << ss.str() << endl;
        }
    } 
}

void Graphics::dump_map_indices() {
    for (int i = 0x9800; i < 0x9800 + 32*32*2; i++) {
        stringstream ss; 
        bool b = false;
        if ((*this)[i] != 0) {
            if (i < 0x9C00) { 
                cout << "Map 1 Tile (" 
                     << dec << (i - 0x9800) / 32 << ", "
                     << dec << (i - 0x9800) % 32 << "): ";
            } else { 
                cout << "Map 2 Tile (" 
                     << dec << (i - 0x9C00) / 32 << ", "
                     << dec << (i - 0x9C00) % 32 << "): ";
            }

            ss << dec << (int) (*this)[i];
            cout << ss.str() << endl;
        }
    } 
}

void handle_tile(unsigned char tile[16], unsigned char buf[256][256], int tile_index){
    int x = (tile_index / 32) * 8;
    int y = (tile_index % 32) * 8;
        
    for (int i = 0; i < 16; i+=2) {
        unsigned char t1 = tile[i];
        unsigned char t2 = tile[i+1];
        
        for (int j = 0; j < 8; j++) {
            unsigned char v = 0; 

            if ((t1 & (0x80 >> j)) != 0) {
                v += 2;
            }  
            if ((t2 & (0x80 >> j)) != 0) {
                v += 1;
            }

            buf[x+(i/2)][y+j] = v;
        }
    }
}

unsigned char* Graphics::get_tile(unsigned int tile_offset, unsigned int index) {
    if (tile_offset == 0x8000) {
        return &(*this)[tile_offset + index * 16];
    } else {
        signed char i = (signed char) index; 
        return &(*this)[tile_offset + i * 16];
    }
}

void Graphics::generate_map(unsigned int tile_offset, unsigned int map_offset, unsigned char buf[256][256]) {
    for (int i = 0; i < 32*32; i++) {
        unsigned int index = (*this)[map_offset + i];
        handle_tile(get_tile(tile_offset, index), buf, i);
    }
}

void Graphics::dump_map(unsigned int tile_offset, unsigned int map_offset) {
    unsigned char buf[256][256] = {0};
    generate_map(tile_offset, map_offset, buf);

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            if (buf[i][j] == 0) {
                cout << ".";
            } else { 
                cout << dec << (int) buf[i][j];
            }
        }
        cout << "\n";
    }
}

void Graphics::dump_map_one_tileset_one() {
    dump_map(0x8000, 0x9800);    
}

void Graphics::dump_map_one_tileset_two() {
    dump_map(0x9000, 0x9800);    
}

void Graphics::dump_map_two_tileset_one() {
    dump_map(0x8000, 0x9C00);    
}

void Graphics::dump_map_two_tileset_two() {
    dump_map(0x9000, 0x9C00);    
}

bool is_set(int reg, int i) {
    return (((0x1 << i) & reg) != 0);
}

Graphics::lcdc_info Graphics::decode_LCDC(unsigned char lcdc) {
    Graphics::lcdc_info l;
   
    l.operation = is_set(lcdc, 7);
    l.window_display = is_set(lcdc, 5);
    l.sprite_display = is_set(lcdc, 2);
    l.bg_window_display = is_set(lcdc, 0);

    l.window_tile_map_addr = is_set(lcdc, 6) ?  0x9C00 : 0x9800; 
    l.bg_tile_map_addr = is_set(lcdc, 3) ? 0x9C00 : 0x9800;
    l.tile_data_addr = is_set(lcdc, 4) ? 0x8000 : 0x9000; 

    l.sprite_width = 8;
    l.sprite_height = is_set(lcdc, 2) ? 16 : 8; 

    return l;
}


void Graphics::dump_display(){
    Graphics::lcdc_info l = decode_LCDC(LCDC);

    if (!l.operation) return;

    unsigned char buf[256][256] = {0};
    generate_map(l.tile_data_addr, l.bg_tile_map_addr, buf);

    for (int i = scroll_y; i < scroll_y + 144; i++) {
        for (int j = scroll_x; j < scroll_x + 160; j++) {
          if (buf[i%255][j%255] == 0) {
                cout << ".";
            } else { 
                cout << dec << (int) buf[i%255][j%255];
            }
        }
        cout << endl;
    }
}

