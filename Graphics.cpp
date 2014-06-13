#include "Graphics.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;
Graphics::Graphics() : VRAM(), scroll_x(0), line_y(0x90) {
    //XXX: LINE Y SET TO 90 to trick ROM...
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
            cout << "SDL_Init Error: " << SDL_GetError() << endl;
                return;
    }

    sdl_window = SDL_CreateWindow("GB Kiwi", 0, 0, 160, 144, 
                    SDL_WINDOW_SHOWN);
    if (sdl_window == nullptr) {
            cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
                return;
    }

    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 
                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (sdl_renderer == nullptr) {
            cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
                return;
    }
}

Graphics::~Graphics() {
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Graphics::step(int clock_cycle_delta) {
    //Do cool graphics stuff
    //XXX: HACK
    if (line_y < 153) line_y++;
    else line_y = 144;
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
    unsigned char buf[256][256] = {{0}};
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

    unsigned char buf[256][256] = {{0}};
    generate_map(l.tile_data_addr, l.bg_tile_map_addr, buf);

    Uint32 sdl_buf[144][160];
    
    for (int i = 0; i <  144; i++) {
        for (int j = 0; j < 160; j++) {
            unsigned char pixel = buf[(i+scroll_y)%255][(j+scroll_x)%255];
            switch(pixel) {
                case 3:
                    sdl_buf[i][j] = 0x000000FF;
                    break;
                case 2:
                    sdl_buf[i][j] = 0x555555FF;
                    break;
                case 1:
                    sdl_buf[i][j] = 0xAAAAAAFF;
                    break;
                case 0:
                    sdl_buf[i][j] = 0xFFFFFFFF;
                    break;
            }
            
        }
    }

    SDL_Surface *pixels = SDL_CreateRGBSurfaceFrom(&sdl_buf, 160, 144, 32, 160 * 32 / 8,
                    0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    if (pixels == nullptr) {
            std::cout << "SDL_CreateRGBSurfaceFrom Error: " 
                        << SDL_GetError() << std::endl;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(sdl_renderer, pixels);
    SDL_FreeSurface(pixels);
    if (tex == nullptr) {
            std::cout << "SDL_CreateTextureFromSurface Error: "
                        << SDL_GetError() << std::endl;
    }   

    SDL_Rect src_rect;
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = 160;
    src_rect.h = 144;

    SDL_Rect dst_rect;
    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.w = 160;
    dst_rect.h = 144;

    SDL_RenderClear(sdl_renderer);
    SDL_RenderCopy(sdl_renderer, tex, &src_rect, &dst_rect);
    SDL_RenderPresent(sdl_renderer);

    SDL_DestroyTexture(tex);

}

