#ifndef CPU_H
#define CPU_H

#include "Memory.h"

class CPU {
    //General Purpose Registers
    char A, F, B, C, D, E, H, L;
    
    //Stack Pointer & Program Counter -- Should be 16bits
    int SP, PC; 

    struct Flag {
        bool Z, H, N, C; 
    } flag;

public: 
    Memory memory;
    int fetch_and_execute();
};


#endif /* CPU_H */
