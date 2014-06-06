#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics {
    int CLK;
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
};


#endif
