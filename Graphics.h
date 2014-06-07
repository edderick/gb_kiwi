#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics {
    int CLK;
    /*
       0x8000 - 0x87FF  Tile set 1 (0 to 127)
       0x8800 - 0x8FFF  Shared Tiles Tile set 1 (128 to 255)
                                     Tile set 2 (-128 to -1)
       0x9000 - 0x97FF  Tile set 2 (0 to 127)
       0x9800 - 0x9BFF  Tile Map 0 
       0x9C00 - 0x9FFF  Tile Map 1
    */
    unsigned char VRAM[0xA000 - 0x8000]= {0};
    public: 

    Graphics();

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

    unsigned char window_y;
    unsigned char window_x;

    void step(int clock_cycle_delta); 
    unsigned char& operator[](unsigned int); 
    
    void dump_state();
    void dump_tiles();
    void dump_map_indices();
    void dump_map_one();
    void dump_map_two();
};


#endif
