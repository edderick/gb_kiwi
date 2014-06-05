#ifndef CPU_H
#define CPU_H

#include "Memory.h"

class CPU {
    //General Purpose Registers
    unsigned char A, F, B, C, D, E, H, L;

    //Stack Pointer & Program Counter -- Should be 16bits
    unsigned short SP, PC; 

    // Clock counts cycles
    int CLK; 
   
    struct Flag {
        bool Z, H, N, C; 
    } flag;

    void decrement_HL();

public: 
    Memory memory;
    int fetch_and_execute();
    void print_state();
};


#endif /* CPU_H */
