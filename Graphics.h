#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

class Graphics {

    struct lcdc_info {
        bool operation;
        bool window_display; 
        bool sprite_display;
        bool bg_window_display; 

        unsigned int window_tile_map_addr; 
        unsigned int bg_tile_map_addr;
        unsigned int tile_data_addr; 

        unsigned char sprite_width; 
        unsigned char sprite_height; 
    };

    int CLK;
    /*
       0x8000 - 0x87FF  Tile set 1 (0 to 127)
       0x8800 - 0x8FFF  Shared Tiles Tile set 1 (128 to 255)
                                     Tile set 2 (-128 to -1)
       0x9000 - 0x97FF  Tile set 2 (0 to 127)
       0x9800 - 0x9BFF  Tile Map 0 
       0x9C00 - 0x9FFF  Tile Map 1
    */
    unsigned char VRAM[0xA000 - 0x8000];
    unsigned char OAM[0xFEA0 - 0xFE00];
    unsigned char* get_tile(unsigned int, unsigned int);
    void generate_map(unsigned int, unsigned int, unsigned char[256][256]);
    
    void use_palettes();

    lcdc_info decode_LCDC(unsigned char); 

    SDL_Window *sdl_window; 
    SDL_Renderer *sdl_renderer;

    public: 

    Graphics();
    ~Graphics();

    unsigned char LCDC;
    unsigned char LCDC_status;

    unsigned char scroll_y;
    unsigned char scroll_x;

    unsigned char line_y;
    unsigned char line_y_cmp;

    unsigned char DMA_addr;

    unsigned char bgp;
    unsigned char obp0;
    unsigned char obp1;

    Uint32 master_palette[4]; 
    Uint32 bg_palette[4];
    Uint32 ob0_palette[4];
    Uint32 ob1_palette[4];

    unsigned char window_y;
    unsigned char window_x;

    void step(int clock_cycle_delta); 
    unsigned char& operator[](unsigned int); 

    void dump_state();
    void dump_tiles();
    void dump_map_indices();
    void dump_map(unsigned int, unsigned int);
    void dump_display();

    void dump_map_one_tileset_one();
    void dump_map_one_tileset_two();
    void dump_map_two_tileset_one();
    void dump_map_two_tileset_two();
};


#endif
