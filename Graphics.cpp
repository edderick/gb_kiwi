#include "Graphics.h"
#include <iostream>
#include <iomanip>
#include <sstream>

namespace gbemu {

namespace { // Anonymous Namespace
void handle_tile(const unsigned char tile[16],
                 unsigned char buf[256][256],
                 int tile_index) {
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

bool is_set(int reg, int i) {
    return (((0x1 << i) & reg) != 0);
}

} // Close Anonymous namespace

Graphics::Graphics()
: d_VRAM()
, d_OAM()
, d_scroll_x(0)
, d_line_y(0x90)
{
    //XXX: LINE Y SET TO 90 to trick ROM...
   
    d_master_palette[0] = 0xFFFFFFFF;
    d_master_palette[1] = 0xAAAAAAFF;
    d_master_palette[2] = 0x555555FF;
    d_master_palette[3] = 0x000000FF;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: "
                  << SDL_GetError()
                  << '\n' << std::flush;
        return;
    }

    d_sdl_window = SDL_CreateWindow("GB Kiwi",
                                    0, 0, 160, 144,
                                    SDL_WINDOW_SHOWN);
    if (d_sdl_window == nullptr) {
        std::cout << "SDL_CreateWindow Error: "
                  << SDL_GetError()
                  << '\n' << std::flush;
        return;
    }

    d_sdl_renderer = SDL_CreateRenderer(d_sdl_window,
                                        -1,
                                        SDL_RENDERER_ACCELERATED |
                                        SDL_RENDERER_PRESENTVSYNC);
    if (d_sdl_renderer == nullptr) {
        std::cout << "SDL_CreateRenderer Error: "
                  << SDL_GetError()
                  << '\n' << std::flush;
        return;
    }
}

Graphics::~Graphics() {
    SDL_DestroyRenderer(d_sdl_renderer);
    SDL_DestroyWindow(d_sdl_window);
    SDL_Quit();
}

void Graphics::step(int clock_cycle_delta) {
    (void) clock_cycle_delta;

    //Do cool graphics stuff
    //XXX: HACK
    if (d_line_y < 153) {
        d_line_y++;
    } else {
        d_line_y = 144;
    }
}

unsigned char& Graphics::operator[](unsigned int i) {
    if (i >= 0xFE00) {
        return d_OAM[i - 0xFE00];
    }

    return d_VRAM[i - 0x8000];
}

const unsigned char& Graphics::operator[](unsigned int i) const {
    if (i >= 0xFE00) {
        return d_OAM[i - 0xFE00];
    }

    return d_VRAM[i - 0x8000];
}

void Graphics::dump_state() const {
    std::cout << "LCDC: " << std::hex << (int) d_LCDC << "  ";
    std::cout << "LCDC Status: " << std::hex << (int) d_LCDC_status << "\n";
    std::cout << "scroll_y: " << std::hex << (int) d_scroll_y << "  ";
    std::cout << "scroll_x: " << std::hex << (int) d_scroll_x << "\n";
    std::cout << "line_y: " << std::hex << (int) d_line_y << "  ";
    std::cout << "line_y_cmp: " << std::hex << (int) d_line_y_cmp << "\n";
    std::cout << "window_y: " << std::hex << (int) d_window_y << "  ";
    std::cout << "window_x: " << std::hex << (int) d_window_x << "\n";
}

void Graphics::dump_tiles() const {
    for (int i = 0; i < 384; i++) {
        std::stringstream ss;
        bool b = false;
        for (int j = 0; j < 16; j++) { 
            if (d_VRAM[i * 16 + j] != 0) {
                b = true;
            }
        }

        if (b) {
            std::cout << "HEX "
                      << std::setw(3) << std::setfill('0') << std::dec
                      << i << ": ";

            for (int j = 0; j < 16; j++) { 
                ss << std::hex << std::setw(2) << std::setfill('0')
                   << (int) d_VRAM[i * 16 + j];
            }

            std::cout << ss.str() << '\n';
        }
    } 
}

void Graphics::dump_map_indices() const {
    for (int i = 0x9800; i < 0x9800 + 32*32*2; i++) {
        std::stringstream ss;
        if ((*this)[i] != 0) {
            if (i < 0x9C00) { 
                std::cout << "Map 1 Tile ("
                     << std::dec << (i - 0x9800) / 32 << ", "
                     << std::dec << (i - 0x9800) % 32 << "): ";
            } else { 
                std::cout << "Map 2 Tile ("
                     << std::dec << (i - 0x9C00) / 32 << ", "
                     << std::dec << (i - 0x9C00) % 32 << "): ";
            }

            ss << std::dec << (int) (*this)[i];
            std::cout << ss.str() << '\n';
        }
    } 
}

const unsigned char* Graphics::get_tile(unsigned int tile_offset,
                                        unsigned int index) const {
    if (tile_offset == 0x8000) {
        return &(*this)[tile_offset + index * 16];
    } else {
        signed char i = (signed char) index; 
        return &(*this)[tile_offset + i * 16];
    }
}

void Graphics::generate_map(unsigned int tile_offset,
                            unsigned int map_offset,
                            unsigned char buf[256][256]) const {
    for (int i = 0; i < 32*32; i++) {
        unsigned int index = (*this)[map_offset + i];
        handle_tile(get_tile(tile_offset, index), buf, i);
    }
}

void Graphics::dump_map(unsigned int tile_offset,
                        unsigned int map_offset) const {
    unsigned char buf[256][256] = {{0}};
    generate_map(tile_offset, map_offset, buf);

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            if (buf[i][j] == 0) {
                std::cout << '.';
            } else { 
                std::cout << std::dec << (int) buf[i][j];
            }
        }
        std::cout << '\n';
    }
}

void Graphics::dump_map_one_tileset_one() const {
    dump_map(0x8000, 0x9800);    
}

void Graphics::dump_map_one_tileset_two() const {
    dump_map(0x9000, 0x9800);    
}

void Graphics::dump_map_two_tileset_one() const {
    dump_map(0x8000, 0x9C00);    
}

void Graphics::dump_map_two_tileset_two() const {
    dump_map(0x9000, 0x9C00);    
}

Graphics::lcdc_info Graphics::decode_LCDC(unsigned char lcdc) const {
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

void Graphics::use_palettes() {
    //BGP = FF47
    d_bg_palette[0] = d_master_palette[d_bgp & 0x3];
    d_bg_palette[1] = d_master_palette[(d_bgp & (0x3 << 2)) >> 2];
    d_bg_palette[2] = d_master_palette[(d_bgp & (0x3 << 4)) >> 4];
    d_bg_palette[3] = d_master_palette[(d_bgp & (0x3 << 6)) >> 6];

    //OBP0 = FF48
    d_ob0_palette[0] = d_master_palette[d_obp0 & 0x3];
    d_ob0_palette[1] = d_master_palette[(d_obp0 & (0x3 << 2)) >> 2];
    d_ob0_palette[2] = d_master_palette[(d_obp0 & (0x3 << 4)) >> 4];
    d_ob0_palette[3] = d_master_palette[(d_obp0 & (0x3 << 6)) >> 6];

    //OBP1 = FF49
    d_ob1_palette[0] = d_master_palette[d_obp1 & 0x3];
    d_ob1_palette[1] = d_master_palette[(d_obp1 & (0x3 << 2)) >> 2];
    d_ob1_palette[2] = d_master_palette[(d_obp1 & (0x3 << 4)) >> 4];
    d_ob1_palette[3] = d_master_palette[(d_obp1 & (0x3 << 6)) >> 6];
}

void Graphics::dump_display() {
    Graphics::lcdc_info l = decode_LCDC(d_LCDC);

    if (!l.operation) return;

    use_palettes();

    unsigned char buf[256][256] = {{0}};
    generate_map(l.tile_data_addr, l.bg_tile_map_addr, buf);

    Uint32 sdl_buf[144][160];
    
    for (int i = 0; i <  144; i++) {
        for (int j = 0; j < 160; j++) {
            unsigned char pixel = buf[(i+d_scroll_y)%255][(j+d_scroll_x)%255];
            sdl_buf[i][j] = d_bg_palette[pixel];
        }
    }

    SDL_Surface *pixels = SDL_CreateRGBSurfaceFrom(&sdl_buf, 160, 144, 32, 160 * 32 / 8,
                    0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    if (pixels == nullptr) {
            std::cout << "SDL_CreateRGBSurfaceFrom Error: " 
                        << SDL_GetError() << std::endl;
            return;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(d_sdl_renderer, pixels);
    SDL_FreeSurface(pixels);
    if (tex == nullptr) {
            std::cout << "SDL_CreateTextureFromSurface Error: "
                      << SDL_GetError() << std::endl;
            return;
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

    SDL_RenderClear(d_sdl_renderer);
    SDL_RenderCopy(d_sdl_renderer, tex, &src_rect, &dst_rect);
    SDL_RenderPresent(d_sdl_renderer);

    SDL_DestroyTexture(tex);
}

} // Close Namespace gbuemu
