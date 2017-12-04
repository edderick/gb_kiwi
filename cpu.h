#ifndef CPU_H
#define CPU_H

#include "Memory.h"
#include "Graphics.h"

namespace gbemu {

class Cartridge;

class CPU {
    public:
    // TYPES
    enum ReturnCodes {
        CONTINUE_EXECUTION = 0,
        HALT_EXECUTION     = 1,
        STOP_EXECUTION     = 2,
    };

    private:
    // PRIVATE DATA
    Memory d_memory;

    public:
    // PUBLIC DATA
    // TODO: Can we hide this?

    //General Purpose Registers
    unsigned char A, F, B, C, D, E, H, L;

    //Stack Pointer & Program Counter -- Should be 16bits
    unsigned short SP, PC;

    // Clock counts cycles
    int CLK;

    struct Flag {
        bool Z, H, N, C;
    } flag;

    private:
    // PRIVATE DATA
    unsigned char d_lastOpCode;
    unsigned char d_lastArg1;
    unsigned char d_lastArg2;

    // PRIVATE MANIPULATORS
    void increment_pair(unsigned char &LSB, unsigned char &MSB);
    void decrement_pair(unsigned char &LSB, unsigned char &MSB);

    void push_val(unsigned char val);
    unsigned char pop_val();

    void push_addr(unsigned short addr);
    unsigned short pop_addr();

    bool interruptsEnabled() const;

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

    void DAA();

    void EI();
    void DI();

    private:
    CPU(const CPU&);            // = delete
    CPU operator=(const CPU&);  // = delete

    public:
    // PUBLIC CREATOTS
    CPU(Cartridge *cartridge, IGraphics *graphics);
    
    public:
    // PUBLIC MANIPULATORS
    int fetch_and_execute();

    unsigned char fetch();

    int execute(unsigned char  OP_CODE,
                unsigned char& ARG1, 
                unsigned char& ARG2);

    // Interruptors
    void verticalBlankInterrupt(); 
    void lcdcStatusInterrupt(); 
    void timerOverflowInterrupt(); 
    void serialTransferInterrupt(); 
    void hiToLoInterrupt(); 

    public:
    // PUBLIC ACCESSORS
    void print_state();

    Memory &memory();
    const Memory &memory() const;
};


// ============================================================================
//                         Inline function definitions 
// ============================================================================

inline
CPU::CPU(Cartridge *cartridge, IGraphics *graphics)
: d_memory(cartridge, graphics)
, PC(0)
{
}

inline 
unsigned char CPU::fetch() {
    return d_memory[PC];
}

inline
int CPU::fetch_and_execute() { 
    return execute(fetch(), d_memory[PC + 1], d_memory[PC + 2]);
}

inline
Memory &CPU::memory() {
    return d_memory;
}

inline
const Memory &CPU::memory() const {
    return d_memory;
}

} // Close namespace gbemu

#endif /* CPU_H */
