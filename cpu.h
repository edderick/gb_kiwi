#ifndef CPU_H
#define CPU_H

#include "Memory.h"

class CPU {
    void increment_pair(unsigned char &LSB, unsigned char &MSB);
    void decrement_pair(unsigned char &LSB, unsigned char &MSB);

    void push_val(unsigned char val);
    unsigned char pop_val();

    void push_addr(unsigned short addr);
    unsigned short pop_addr();

    void RL(unsigned char &reg);
    void RLC(unsigned char &reg);
    void RR(unsigned char &reg);
    void RRC(unsigned char &reg);

    void SLA(unsigned char &reg);
    void SRA(unsigned char &reg);
    void SRL(unsigned char &reg);

    template<typename T> 
    void LD(T &reg1, T reg2);
    void LD_16(unsigned char &reg1a, unsigned char &reg1b, 
               unsigned char reg2a, unsigned char reg2b);
    void LDHL(unsigned short reg, unsigned char n);

    template<typename T>
    void ADD(T &reg1, T reg2);
    void ADC(unsigned char &reg1, unsigned char reg2);
    void SUB(unsigned char &reg1, unsigned char reg2);
    void SBC(unsigned char &reg1, unsigned char reg2);

    void CP(unsigned char reg1, unsigned char reg2);

    void AND(unsigned char &reg1, unsigned char reg2);
    void OR(unsigned char &reg1, unsigned char reg2);
    void XOR(unsigned char &reg1, unsigned char reg2);
    
    template<typename T> 
    void INC(T &reg);
    template<typename T> 
    void DEC(T &reg);

    void ADD_16(unsigned char &reg1a, unsigned char &reg1b, 
                unsigned char reg2a, unsigned char reg2b);
    void INC_16(unsigned char &lsb, unsigned char &msb);
    void DEC_16(unsigned char &lsb, unsigned char &msb);

    void SWAP(unsigned char &reg); 

    void BIT(unsigned char reg, unsigned char bit);
    void SET(unsigned char &reg, unsigned char bit);
    void RESET(unsigned char &reg, unsigned char bit);
    
    void JUMP(unsigned short addr); 
    void JUMP_R(unsigned char offset); 
public: 
    CPU(); 

    //General Purpose Registers
    unsigned char A, F, B, C, D, E, H, L;

    //Stack Pointer & Program Counter -- Should be 16bits
    unsigned short SP, PC; 

    // Clock counts cycles
    int CLK; 
   
    struct Flag {
        bool Z, H, N, C; 
    } flag;

    Memory memory;

    int fetch_and_execute();

    unsigned char fetch();

    int execute(unsigned char OP_CODE, 
                unsigned char& ARG1, 
                unsigned char& ARG2);

    void print_state();
};


// ============================================================================
//                         Inline function definitions 
// ============================================================================

inline
CPU::CPU() : PC(0) {
}

inline 
unsigned char CPU::fetch() {
    return memory[PC];
}

inline
int CPU::fetch_and_execute() { 
    return execute(fetch(), memory[PC + 1], memory[PC + 2]);
}

#endif /* CPU_H */
