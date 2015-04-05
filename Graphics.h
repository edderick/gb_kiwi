#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

namespace gbemu {

class IGraphics {
  public:
    // PUBLIC DATA
    unsigned char d_LCDC;
    unsigned char d_LCDC_status;

    unsigned char d_scroll_y;
    unsigned char d_scroll_x;

    unsigned char d_line_y;
    unsigned char d_line_y_cmp;

    unsigned char d_DMA_addr;

    unsigned char d_bgp;
    unsigned char d_obp0;
    unsigned char d_obp1;

    unsigned char d_window_y;
    unsigned char d_window_x;

  public:
    // PUBLIC ACCESSORS
    virtual void step(int clock_cycle_delta) = 0;
    virtual unsigned char& operator[](unsigned int)  = 0;
    virtual const unsigned char& operator[](unsigned int) const = 0;
};

class Graphics : public IGraphics {
  private:
    // PRIVATE TYPES
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

  private:
    // PRIVATE DATA
    int d_CLK;
    /*
       0x8000 - 0x87FF  Tile set 1 (0 to 127)
       0x8800 - 0x8FFF  Shared Tiles Tile set 1 (128 to 255)
                                     Tile set 2 (-128 to -1)
       0x9000 - 0x97FF  Tile set 2 (0 to 127)
       0x9800 - 0x9BFF  Tile Map 0 
       0x9C00 - 0x9FFF  Tile Map 1
    */

    unsigned char d_VRAM[0xA000 - 0x8000];
    unsigned char d_OAM[0xFEA0 - 0xFE00];

    Uint32 d_master_palette[4];
    Uint32 d_bg_palette[4];
    Uint32 d_ob0_palette[4];
    Uint32 d_ob1_palette[4];

    SDL_Window *d_sdl_window;
    SDL_Renderer *d_sdl_renderer;

  private:
    // PRIVATE ACCESSORS
    const unsigned char* get_tile(unsigned int, unsigned int) const;
    void generate_map(unsigned int,
                      unsigned int,
                      unsigned char[256][256]) const;
    
    void use_palettes();

    lcdc_info decode_LCDC(unsigned char) const;

  private:
    // NOT IMPLEMENTED
    Graphics(const Graphics &);           // = delete
    Graphics operator=(const Graphics &); // = delete

  public:
    // CREATORS
    Graphics();
    ~Graphics();

  public:
    // PUBLIC ACCESSORS
    void step(int clock_cycle_delta); 

    unsigned char& operator[](unsigned int); 
    const unsigned char& operator[](unsigned int) const;

    void dump_state() const;
    void dump_tiles() const;
    void dump_map_indices() const;
    void dump_map(unsigned int, unsigned int) const;
    void dump_display();

    void dump_map_one_tileset_one() const;
    void dump_map_one_tileset_two() const;
    void dump_map_two_tileset_one() const;
    void dump_map_two_tileset_two() const;
};

} // Close Namespace gbemu

#endif
