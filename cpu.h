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

    void increment_pair(unsigned char &LSB, unsigned char &MSB);
    void decrement_pair(unsigned char &LSB, unsigned char &MSB);

    void push_val(unsigned char val);
    unsigned char pop_val();

    void push_addr(unsigned short addr);
    unsigned short pop_addr();

    void RL(unsigned char &reg);
    template<typename T> 
    void LD(T &reg1, T reg2);
    void LD_16(unsigned char &reg1a, unsigned char &reg1b, 
               unsigned char reg2a, unsigned char reg2b);
    void LDHL(unsigned short reg, unsigned char n);

public: 
    Memory memory;
    int fetch_and_execute();
    void print_state();
};


#endif /* CPU_H */
