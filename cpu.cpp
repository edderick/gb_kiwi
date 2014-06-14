#include "cpu.h"
#include <iostream>
#include <iomanip>

using namespace std;

unsigned char OP_cycles[0x100] = {  
    /*     x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, xA, xB, xC, xD, xE, xF, */
    /*0x*/  4, 12,  8,  8,  4,  4,  8,  4, 20,  8,  8,  8,  4,  4,  8,  4,
    /*1x*/  4, 12,  8,  8,  4,  4,  8,  4,  8,  8,  8,  8,  4,  4,  8,  4,
    /*2x*/  8, 12,  8,  8,  4,  4,  8,  4,  8,  8,  8,  8,  4,  4,  8,  4,
    /*3x*/  8, 12,  8,  8, 12, 12, 12,  4,  8,  8,  8,  8,  4,  4,  8,  4,
    /*4x*/  4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
    /*5x*/  4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
    /*6x*/  4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
    /*7x*/  8,  8,  8,  8,  8,  8,  4,  8,  4,  4,  4,  4,  4,  4,  8,  4,
    /*8x*/  4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
    /*9x*/  4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
    /*Ax*/  4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
    /*Bx*/  4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
    /*Cx*/  8, 12, 12, 12, 12, 16,  8, 32,  8,  8, 12,  0, 12, 12,  8, 32,
    /*Dx*/  8, 12, 12,  0, 12, 16,  8, 32,  8,  8, 12,  0, 12,  0,  0, 32,
    /*Ex*/ 12, 12,  8,  0,  0, 16,  8, 32, 16,  4, 16,  0,  0,  0,  8, 32,
    /*Fx*/ 12, 12,  8,  4,  0, 16,  8, 32, 12,  8, 16,  4,  0,  0,  8, 32,
}; 

unsigned char EX_OP_cycles[0x100] = {  
    /*     x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, xA, xB, xC, xD, xE, xF, */
    /*0x*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    /*1x*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    /*2x*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    /*3x*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    /*4x*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    /*5x*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    /*6x*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    /*7x*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    /*8x*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    /*9x*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    /*Ax*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    /*Bx*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    /*Cx*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    /*Dx*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    /*Ex*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    /*Fx*/  8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
}; 

unsigned char OP_len[0x100] = {  
    /*     x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, xA, xB, xC, xD, xE, xF, */
    /*0x*/  1,  3,  1,  1,  1,  1,  2,  1,  3,  1,  1,  1,  1,  1,  2,  1,
    /*1x*/  0,  3,  1,  1,  1,  1,  2,  1,  2,  1,  1,  1,  1,  1,  2,  1,
    /*2x*/  2,  3,  1,  1,  1,  1,  2,  0,  2,  1,  1,  1,  1,  1,  2,  1,
    /*3x*/  2,  3,  1,  1,  1,  1,  2,  1,  2,  1,  1,  1,  1,  1,  2,  1,
    /*4x*/  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    /*5x*/  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    /*6x*/  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    /*7x*/  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    /*8x*/  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    /*9x*/  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    /*Ax*/  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    /*Bx*/  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    /*Cx*/  0,  1,  3,  0,  3,  1,  2,  0,  0,  0,  3,  0,  3,  0,  2,  0,
    /*Dx*/  0,  1,  3,  0,  3,  1,  2,  0,  0,  0,  3,  0,  3,  0,  0,  0,
    /*Ex*/  2,  1,  1,  0,  0,  1,  2,  0,  2,  1,  3,  0,  0,  0,  2,  0,
    /*Fx*/  2,  1,  1,  1,  0,  1,  2,  0,  2,  1,  3,  1,  0,  0,  2,  0,
}; 

unsigned char EX_OP_len[0x100] = {  
    /*     x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, xA, xB, xC, xD, xE, xF, */
    /*0x*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    /*1x*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    /*2x*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    /*3x*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    /*4x*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    /*5x*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    /*6x*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    /*7x*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    /*8x*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    /*9x*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    /*Ax*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    /*Bx*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    /*Cx*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    /*Dx*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    /*Ex*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    /*Fx*/  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
}; 

unsigned short concat_bytes(unsigned char LSB, unsigned char MSB) {
    // Little endian machime
    unsigned short tmp_MSB = MSB << 8;
    unsigned short tmp_LSB = LSB;
    return tmp_LSB + tmp_MSB;
}

//XXX: NEEDS TESTING...
void CPU::increment_pair(unsigned char &LSB, unsigned char &MSB) {
    unsigned short p = concat_bytes(LSB, MSB);
    p++; 
    MSB = (0xFF00 & p) >> 8;
    LSB = 0x00FF & p;
} 

//XXX: NEEDS TESTING...
void CPU::decrement_pair(unsigned char &LSB, unsigned char &MSB) {
    unsigned short p = concat_bytes(L, H);
    p--; 
    MSB = (0xFF00 & p) >> 8;
    LSB = 0x00FF & p;
} 

void CPU::push_val(unsigned char val) {
    SP--;
    memory[SP] = val;
}

unsigned char CPU::pop_val() {
    SP++;
    return memory[SP - 1];
}

void CPU::push_addr(unsigned short addr) {
    push_val((addr & 0xFF00) >> 8);
    push_val((addr & 0xFF));

}

unsigned short CPU::pop_addr() {
    unsigned char A = pop_val();
    unsigned char B = pop_val();
    
    return concat_bytes(A, B);
}

void CPU::RL(unsigned char &reg) {
    bool carry_out = ((reg >> 7) == 1);
    unsigned char carry_in = flag.C ? 0x1 : 0x0;
    reg = (reg << 1) | carry_in;

    flag.C = carry_out;
    flag.N = false; flag.H = false;
    flag.Z = (reg == 0);
}

void CPU::RLC(unsigned char &reg) {
    bool carry_out = ((reg >> 7) == 1);
    unsigned char carry_in = carry_out ? 0x1 : 0x0;
    reg = (reg << 1) | carry_in;

    flag.C = carry_out;
    flag.N = false; flag.H = false;
    flag.Z = (reg == 0);
}

void CPU::RR(unsigned char &reg) {
    bool carry_out = ((reg & 0x1) == 1);
    unsigned char carry_in = flag.C ? 0x1 : 0x0;
    reg = (reg >> 1) | (carry_in << 7);

    flag.C = carry_out;
    flag.N = false; flag.H = false;
    flag.Z = (reg == 0);
}

void CPU::RRC(unsigned char &reg) {
    bool carry_out = ((reg & 0x1) == 1);
    unsigned char carry_in = carry_out ? 0x1 : 0x0;
    reg = (reg >> 1) | (carry_in << 7);

    flag.C = carry_out;
    flag.N = false; flag.H = false;
    flag.Z = (reg == 0);
}

void CPU::SLA(unsigned char &reg){
    bool carry_out = ((reg >> 7) == 1);
    reg = (reg << 1);

    flag.C = carry_out;
    flag.N = false; flag.H = false;
    flag.Z = (reg == 0);
}

void CPU::SRA(unsigned char &reg){
    bool carry_out = ((reg & 1) == 1);
    reg = ((reg >> 1) | (reg & (1 << 7)));

    flag.C = carry_out;
    flag.N = false; flag.H = false;
    flag.Z = (reg == 0);
}

void CPU::SRL(unsigned char &reg){
    bool carry_out = ((reg & 1) == 1);
    reg = (reg >> 1);

    flag.C = carry_out;
    flag.N = false; flag.H = false;
    flag.Z = (reg == 0);
}

template<typename T>
void CPU::LD(T &reg1, T reg2) {
    reg1 = reg2; 
}

void CPU::LD_16(unsigned char &reg1a, unsigned char &reg1b, 
                unsigned char reg2a, unsigned char reg2b) {
    reg1a = reg2a; 
    reg1b = reg2b; 
}

void CPU::LDHL(unsigned short reg, unsigned char n) {
    unsigned short tmp = reg + n; 
    H = (tmp & 0xFF00) >> 8;
    L = tmp & 0xFF;
    flag.Z = 0; flag.N = 0; 
    //TODO: flag.H and flag.C;
}

template<>
void CPU::ADD(unsigned char &reg1, unsigned char reg2) {
    //TODO: Check this
    flag.H = (((reg1 & (1 << 3)) & (reg2 & (1 << 3))) != 0);
    flag.C = (((reg1 & (1 << 7)) & (reg2 & (1 << 7))) != 0);
    reg1 += reg2;
    flag.Z = (reg1 == 0); flag.N = false;
}

template<>
void CPU::ADD(unsigned short &reg1, unsigned short reg2) {
    //TODO: Check this
    flag.H = (((reg1 & (1 << 11)) & (reg2 & (1 << 11))) != 0);
    flag.C = (((reg1 & (1 << 15)) & (reg2 & (1 << 15))) != 0);
    reg1 += reg2;
    flag.N = false;
}

void CPU::ADD_16(unsigned char &reg1_lsb, unsigned char &reg1_msb, 
                 unsigned char reg2_lsb, unsigned char reg2_msb) {
    //TODO: Check this
    flag.H = (((reg1_msb & (1 << (11-7))) & (reg2_msb & (1 << (11-7)))) != 0);
    flag.C = (((reg1_msb & (1 << (15-7))) & (reg2_msb & (1 << (15-7)))) != 0);
    flag.N = false;
        
    unsigned short tmp = concat_bytes(reg1_lsb, reg1_msb) + concat_bytes(reg2_lsb, reg2_msb); 
        
    reg1_msb = (0xFF00 & tmp) >> 8;
    reg1_lsb = 0x00FF & tmp;
}

void CPU::ADC(unsigned char &reg1, unsigned char reg2) {
    //TODO: Check this
    unsigned char carry = flag.C ? 1 : 0;
    flag.H = (((reg1 & (1 << 3)) & (reg2 & (1 << 3))) != 0);
    flag.C = (((reg1 & (1 << 7)) & (reg2 & (1 << 7))) != 0);
    reg1 = reg1 + reg2  + carry;
    flag.Z = (reg1 == 0); flag.N = true;
}

void CPU::SUB(unsigned char &reg1, unsigned char reg2) {
    //TODO: Check this
    flag.H = !(((reg1 & (1 << 3)) == 0) && ((reg2 & (1 << 3))) != 0);
    flag.C = (reg1 < reg2);
    reg1 -= reg2;
    flag.Z = (reg1 == 0); flag.N = true;
}

void CPU::SBC(unsigned char &reg1, unsigned char reg2) {
    //TODO: Check this
    unsigned char carry = flag.C ? 1 : 0;
    flag.H = !(((reg1 & (1 << 3)) == 0) && ((reg2 & (1 << 3))) != 0);
    flag.C = (reg1 < reg2);
    reg1 = reg1 - reg2  + carry;
    flag.Z = (reg1 == 0); flag.N = true;
}

void CPU::CP(unsigned char reg1, unsigned char reg2) {
    //TODO: Check this
    flag.H = !(((reg1 & (1 << 3)) == 0) && ((reg2 & (1 << 3))) != 0);
    flag.C = (reg1 < reg2);
    flag.Z = (reg1 == reg2); flag.N = true;
}

void CPU::AND(unsigned char &reg1, unsigned char reg2) {
    //TODO: Check this
    reg1 = reg1 & reg2;
    flag.Z = (reg1 == 0); 
    flag.N = false; flag.H = true; flag.C = false;
}

void CPU::OR(unsigned char &reg1, unsigned char reg2) {
    //TODO: Check this
    reg1 = reg1 | reg2;
    flag.Z = (reg1 == 0); 
    flag.N = false; flag.H = false; flag.C = false;
}

void CPU::XOR(unsigned char &reg1, unsigned char reg2) {
    //TODO: Check this
    reg1 = reg1 ^ reg2;
    flag.Z = (reg1 == 0); 
    flag.N = false; flag.H = false; flag.C = false;
}

template<typename T>
void CPU::INC(T &reg) {
    reg++;
    flag.Z = (reg == 0);
    flag.N = false; 
    flag.H = ((0xF & reg) == 0xF);
}

template<typename T>
void CPU::DEC(T &reg) {
    reg--;
    flag.Z = (reg == 0);
    flag.N = true; 
    flag.H = ((0xF & reg) == 0x0);
}

void CPU::INC_16(unsigned char &LSB, unsigned char &MSB) {
        increment_pair(LSB, MSB);
}

void CPU::DEC_16(unsigned char &LSB, unsigned char &MSB) {
        increment_pair(LSB, MSB);
}

void CPU::SWAP(unsigned char &reg) {
    reg = (((reg & 0xF) << 8) | ((reg & 0xF0) >> 8));
    flag.Z = (reg == 0);
    flag.N = false; flag.H = false; flag.C = false;
}

void CPU::BIT(unsigned char reg, unsigned char bit) {
    flag.Z = ((reg & (1 << bit)) == 0);
    flag.N = false;
    flag.H = true;
}

void CPU::SET(unsigned char &reg, unsigned char bit) {
    reg = reg | (1 << bit); 
}

void CPU::RESET(unsigned char &reg, unsigned char bit) {
    reg = reg & (0xFF ^ (1 << bit)); 
}

void CPU::JUMP(unsigned short addr) {
    PC = addr;
}

void CPU::JUMP_R(unsigned char offset) {
    PC += (signed char) offset;
}

void CPU::print_state() {
    //XXX: 2590436
    if (CLK < 835024) return;
    //if (memory[PC] == 0) return;

    //memory.graphics.dump_state();
    //memory.graphics.dump_map_indices();
    //memory.graphics.dump_tiles();

    cout << "A: "  << hex << setw(2) << setfill('0') << (unsigned int) A;
    cout << "  F: " << hex << setw(2) << setfill('0') << (unsigned int) F;
    cout << "  B: " << hex << setw(2) << setfill('0') << (unsigned int) B;
    cout << "  C: " << hex << setw(2) << setfill('0') << (unsigned int) C;
    cout << "  D: " << hex << setw(2) << setfill('0') << (unsigned int) D;
    cout << "  E: " << hex << setw(2) << setfill('0') << (unsigned int) E;
    cout << "  H: " << hex << setw(2) << setfill('0') << (unsigned int) H;
    cout << "  L: " << hex << setw(2) << setfill('0') << (unsigned int) L;
    cout << "\n";
    cout << "Z: "  << hex << setw(1) << setfill('0') << (unsigned int) flag.Z;
    cout << "  H: " << hex << setw(1) << setfill('0') << (unsigned int) flag.H;
    cout << "  N: " << hex << setw(1) << setfill('0') << (unsigned int) flag.N;
    cout << "  C: " << hex << setw(1) << setfill('0') << (unsigned int) flag.C;
    cout << "\n\n";
    cout << "PC: " << hex << setw(4) << setfill('0') << PC;
    cout << "   CLK: " << dec << CLK;
    cout << "   SP: " << hex << setw(4) << setfill('0') << SP;
    cout << "\n";
    cout << "OP_CODE: " << hex << setw(2) << setfill('0') << (int) memory[PC];
    cout << "   ARG1: " << hex << setw(2) << setfill('0') << (int) memory[PC+1];
    cout << "   ARG2: " << hex << setw(2) << setfill('0') << (int) memory[PC+2];
    cout << endl;
}

int CPU::fetch_and_execute() {
    unsigned char OP_CODE = memory[PC];
   
    switch (OP_CODE) {
        /*** 8-bit Loads ***/ 
        /* 1. LD nn,n */
        case 0x06: LD(B, memory[PC + 1]); break; 
        case 0x0E: LD(C, memory[PC + 1]); break; 
        case 0x16: LD(D, memory[PC + 1]); break; 
        case 0x1E: LD(E, memory[PC + 1]); break; 
        case 0x26: LD(H, memory[PC + 1]); break; 
        case 0x2E: LD(L, memory[PC + 1]); break; 

        /* 2. LD r1,r2 */
        case 0x7F: LD(A, A); break; 
        case 0x78: LD(A, B); break; 
        case 0x79: LD(A, C); break; 
        case 0x7A: LD(A, D); break; 
        case 0x7B: LD(A, E); break; 
        case 0x7C: LD(A, H); break; 
        case 0x7D: LD(A, L); break; 
        case 0x7E: LD(A, memory[concat_bytes(L, H)]); break; 

        case 0x40: LD(B, B); break; 
        case 0x41: LD(B, C); break; 
        case 0x42: LD(B, D); break; 
        case 0x43: LD(B, E); break; 
        case 0x44: LD(B, H); break; 
        case 0x45: LD(B, L); break; 
        case 0x46: LD(B, memory[concat_bytes(L, H)]); break; 

        case 0x48: LD(C, B); break; 
        case 0x49: LD(C, C); break; 
        case 0x4A: LD(C, D); break; 
        case 0x4B: LD(C, E); break; 
        case 0x4C: LD(C, H); break; 
        case 0x4D: LD(C, L); break; 
        case 0x4E: LD(C, memory[concat_bytes(L, H)]); break; 

        case 0x50: LD(D, B); break; 
        case 0x51: LD(D, C); break; 
        case 0x52: LD(D, D); break; 
        case 0x53: LD(D, E); break; 
        case 0x54: LD(D, H); break; 
        case 0x55: LD(D, L); break; 
        case 0x56: LD(D, memory[concat_bytes(L, H)]); break; 

        case 0x58: LD(E, B); break; 
        case 0x59: LD(E, C); break; 
        case 0x5A: LD(E, D); break; 
        case 0x5B: LD(E, E); break; 
        case 0x5C: LD(E, H); break; 
        case 0x5D: LD(E, L); break; 
        case 0x5E: LD(E, memory[concat_bytes(L, H)]); break; 

        case 0x60: LD(H, B); break; 
        case 0x61: LD(H, C); break; 
        case 0x62: LD(H, D); break; 
        case 0x63: LD(H, E); break; 
        case 0x64: LD(H, H); break; 
        case 0x65: LD(H, L); break; 
        case 0x66: LD(H, memory[concat_bytes(L, H)]); break; 

        case 0x68: LD(L, B); break; 
        case 0x69: LD(L, C); break; 
        case 0x6A: LD(L, D); break; 
        case 0x6B: LD(L, E); break; 
        case 0x6C: LD(L, H); break; 
        case 0x6D: LD(L, L); break; 
        case 0x6E: LD(L, memory[concat_bytes(L, H)]); break; 

        case 0x70: LD(memory[concat_bytes(L, H)], B); break; 
        case 0x71: LD(memory[concat_bytes(L, H)], C); break; 
        case 0x72: LD(memory[concat_bytes(L, H)], D); break; 
        case 0x73: LD(memory[concat_bytes(L, H)], E); break; 
        case 0x74: LD(memory[concat_bytes(L, H)], H); break; 
        case 0x75: LD(memory[concat_bytes(L, H)], L); break; 

        case 0x36: LD(memory[concat_bytes(L, H)], memory[PC + 1]); break; 
    
        /* 3. LD A,n */
        case 0x0A: LD(A, memory[concat_bytes(C, B)]); break;
        case 0x1A: LD(A, memory[concat_bytes(E, D)]); break;
        case 0xFA: LD(A, memory[concat_bytes(memory[PC + 1], memory[PC + 2])]); break;
        case 0x3E: LD(A, memory[PC + 1]); break;

        /* 4. LD n,A */
        case 0x47: LD(B, A); break;
        case 0x4F: LD(C, A); break;
        case 0x57: LD(D, A); break;
        case 0x5F: LD(E, A); break;
        case 0x67: LD(H, A); break;
        case 0x6F: LD(L, A); break;
        case 0x02: LD(memory[concat_bytes(C, B)], A); break;
        case 0x12: LD(memory[concat_bytes(E, D)], A); break;
        case 0x77: LD(memory[concat_bytes(L, H)], A); break;
        case 0xEA: LD(memory[concat_bytes(memory[PC + 1], memory[PC + 2])], A); break;

        /* 5. LD A,(C) */
        case 0xF2: LD(A, memory[0xFF00 + C]); break; 

        /* 6. LD (C),A */
        case 0xE2: LD(memory[0xFF00 + C], A); break;

        /* 9. LDD A,(HL) */ 
        case 0x3A: LD(A, memory[concat_bytes(L, H)]); decrement_pair(L, H); break;

        /* 12. LDD (HL),A */ 
        case 0x32: LD(memory[concat_bytes(L, H)], A); decrement_pair(L, H); break;

        /* 15. LDI A,(HL) */
        case 0x2A: LD(A, memory[concat_bytes(L, H)]); increment_pair(L, H); break;

        /* 18. LDI (HL),A */ 
        case 0x22: LD(memory[concat_bytes(L, H)], A); increment_pair(L, H); break;

        /* 19. LDH (n),A */
        case 0xE0:  LD(memory[0xFF00 + memory[PC + 1]], A); break;

        /* 20. LDH A,(n) */
        case 0xF0: LD(A, memory[0xFF00 + memory[PC + 1]]); break;

        
        /*** 16-bit Loads ***/
        /* 1. LD n,nn */
        case 0x01: LD_16(B, C, memory[PC + 2], memory[PC + 1]); break;
        case 0x11: LD_16(D, E, memory[PC + 2], memory[PC + 1]); break;
        case 0x21: LD_16(H, L, memory[PC + 2], memory[PC + 1]); break;
        case 0x31: LD(SP, concat_bytes(memory[PC + 1], memory[PC + 2])); break;

        /* 2. LD SP,HL */
        case 0xF9: LD(SP, concat_bytes(L, H)); break;

        /* 3. LDHL SP,n */
        case 0xF8: LDHL(SP, memory[PC + 1]); break;

        /* 5. LD (nn),SP */
        case 0x08: LD_16(memory[concat_bytes(memory[PC + 1], memory[PC + 2]) + 1], 
                         memory[concat_bytes(memory[PC + 1], memory[PC + 2])], 
                         ((SP& 0xFF00) >> 8), (SP & 0xFF)); break;  

        /* 6. PUSH nn */
        case 0xF5: push_val(A); push_val(F); break;
        case 0xC5: push_val(B); push_val(C); break; 
        case 0xD5: push_val(D); push_val(E); break; 
        case 0xE5: push_val(H); push_val(L); break; 
        
        /* 7. POP nn */ 
        case 0xF1: F = pop_val(); A = pop_val(); break; 
        case 0xC1: C = pop_val(); B = pop_val(); break; 
        case 0xD1: E = pop_val(); D = pop_val(); break; 
        case 0xE1: L = pop_val(); H = pop_val(); break; 

        
        /*** 8-bit ALU ***/
        /* 1. ADD A,n */
        case 0x87: ADD(A, A); break; 
        case 0x80: ADD(A, B); break; 
        case 0x81: ADD(A, C); break; 
        case 0x82: ADD(A, D); break; 
        case 0x83: ADD(A, E); break; 
        case 0x84: ADD(A, H); break; 
        case 0x85: ADD(A, L); break; 
        case 0x86: ADD(A, memory[concat_bytes(L, H)]); break; 
        case 0xC6: ADD(A, memory[PC + 1]); break; 
    
        /* 2. ADC A,n */ 
        case 0x8F: ADC(A, A); break; 
        case 0x88: ADC(A, B); break; 
        case 0x89: ADC(A, C); break; 
        case 0x8A: ADC(A, D); break; 
        case 0x8B: ADC(A, E); break; 
        case 0x8C: ADC(A, H); break; 
        case 0x8D: ADC(A, L); break; 
        case 0x8E: ADC(A, memory[concat_bytes(L, H)]); break; 
        case 0xCE: ADC(A, memory[PC + 1]); break; 

        /* 3. SUB A,n */
        case 0x97: SUB(A, A); break; 
        case 0x90: SUB(A, B); break; 
        case 0x91: SUB(A, C); break; 
        case 0x92: SUB(A, D); break; 
        case 0x93: SUB(A, E); break; 
        case 0x94: SUB(A, H); break; 
        case 0x95: SUB(A, L); break; 
        case 0x96: SUB(A, memory[concat_bytes(L, H)]); break; 
        case 0xD6: SUB(A, memory[PC + 1]); break; 
    
        /* 4. SBC A,n */ 
        case 0x9F: SBC(A, A); break; 
        case 0x98: SBC(A, B); break; 
        case 0x99: SBC(A, C); break; 
        case 0x9A: SBC(A, D); break; 
        case 0x9B: SBC(A, E); break; 
        case 0x9C: SBC(A, H); break; 
        case 0x9D: SBC(A, L); break; 
        case 0x9E: SBC(A, memory[concat_bytes(L, H)]); break; 
        case 0xDE: SBC(A, memory[PC + 1]); break; 

        /* 5. AND n */
        case 0xA7: AND(A, A); break; 
        case 0xA0: AND(A, B); break; 
        case 0xA1: AND(A, C); break; 
        case 0xA2: AND(A, D); break; 
        case 0xA3: AND(A, E); break; 
        case 0xA4: AND(A, H); break; 
        case 0xA5: AND(A, L); break; 
        case 0xA6: AND(A, memory[concat_bytes(L, H)]); break; 
        case 0xE6: AND(A, memory[PC + 1]); break; 

        /* 6. OR n */
        case 0xB7: OR(A, A); break; 
        case 0xB0: OR(A, B); break; 
        case 0xB1: OR(A, C); break; 
        case 0xB2: OR(A, D); break; 
        case 0xB3: OR(A, E); break; 
        case 0xB4: OR(A, H); break; 
        case 0xB5: OR(A, L); break; 
        case 0xB6: OR(A, memory[concat_bytes(L, H)]); break; 
        case 0xF6: OR(A, memory[PC + 1]); break; 

        /* 7. XOR n */
        case 0xAF: XOR(A, A); break; 
        case 0xA8: XOR(A, B); break; 
        case 0xA9: XOR(A, C); break; 
        case 0xAA: XOR(A, D); break; 
        case 0xAB: XOR(A, E); break; 
        case 0xAC: XOR(A, H); break; 
        case 0xAD: XOR(A, L); break; 
        case 0xAE: XOR(A, memory[concat_bytes(L, H)]); break; 
        case 0xEE: XOR(A, memory[PC + 1]); break; 

        /* 8. CP n */
        case 0xBF: CP(A, A); break; 
        case 0xB8: CP(A, B); break; 
        case 0xB9: CP(A, C); break; 
        case 0xBA: CP(A, D); break; 
        case 0xBB: CP(A, E); break; 
        case 0xBC: CP(A, H); break; 
        case 0xBD: CP(A, L); break; 
        case 0xBE: CP(A, memory[concat_bytes(L, H)]); break; 
        case 0xFE: CP(A, memory[PC + 1]); break; 

        /* 9. INC n */
        case 0x3C: INC(A); break;
        case 0x04: INC(B); break;
        case 0x0C: INC(C); break;
        case 0x14: INC(D); break;
        case 0x1C: INC(E); break;
        case 0x24: INC(H); break;
        case 0x2C: INC(L); break;
        case 0x34: INC(memory[concat_bytes(L, H)]); break;

        /* 10. DEC n */
        case 0x3D: DEC(A); break;
        case 0x05: DEC(B); break;
        case 0x0D: DEC(C); break;
        case 0x15: DEC(D); break;
        case 0x1D: DEC(E); break;
        case 0x25: DEC(H); break;
        case 0x2D: DEC(L); break;
        case 0x35: DEC(memory[concat_bytes(L, H)]); break;

        /*** 16-bit ALU ***/
        /* 1. ADD HL,n */
        case 0x09: ADD_16(L, H, C, B); break; 
        case 0x19: ADD_16(L, H, E, D); break; 
        case 0x29: ADD_16(L, H, L, H); break; 
        case 0x39: ADD_16(L, H, (SP & 0xFF), ((SP & 0xFF00) >> 8)); break; 

        /* 2. ADD SP,n */
        case 0xE8: ADD(SP, (unsigned short) memory[PC + 1]); break;

        /* 3. INC nn */ 
        case 0x03: INC_16(C, B); break;
        case 0x13: INC_16(E, D); break;
        case 0x23: INC_16(L, H); break;
        case 0x33: INC(SP); break;

        /* 4. DEC nn */ 
        case 0x0B: DEC_16(C, B); break;
        case 0x1B: DEC_16(E, D); break;
        case 0x2B: DEC_16(L, H); break;
        case 0x3B: DEC(SP); break;
        
        /*** Miscellaneous ***/
        /* 2. DAA */ 
        //TODO: DAA

        /* 3. CPL */
        case 0x2F: A = ~A; flag.N = true; flag.H = true; break;

        /* 4. CCF */
        case 0x3F: flag.N = false; flag.H = false; flag.C = !flag.C; break;

        /* 5. SCF */ 
        case 0x37: flag.N = false; flag.H = false; flag.C = true; break;

        /* 6. NOP */
        case 0x00: break;        

        /* 7. HALT */ 
        //TODO: case 0x76: 
        
        /* 8. STOP */
        //TODO: case 0x10:

        /* 9. DI */
        //TODO: Implement this 
        case 0xF3: cout << "WARNING: Attempting to disable interrupts!" << endl; break;

        /* 10. EI */
        //TODO: Implement this
        case 0xFB: cout << "WARNING: Attempting to enable interrupts!" << endl; break;

        /*** Rotates & Shifts ***/
        /* 1. RLCA */
        case 0x07: RLC(A); break; 
                   
        /* 2. RLA */
        case 0x17: RL(A); break;
        
        /* 3. RRCA */
        case 0x0F: RRC(A); break; 
                   
        /* 4. RRA */
        case 0x1F: RR(A); break;
        



        case 0xCB: 
            {
                //Extension OP_CODES
                char x = (memory[PC + 1] & 0xC0) >> 6;
                char y = (memory[PC + 1] & 0x38) >> 3;
                char z = (memory[PC + 1] & 0x07);

                switch(x) {
                    case 00: 
                        //TODO: Rotate
                        switch(memory[PC + 1]) {
                            /* 5. RLC n */
                            case 0x07: RLC(A); break;
                            case 0x00: RLC(B); break;
                            case 0x01: RLC(C); break;
                            case 0x02: RLC(D); break;
                            case 0x03: RLC(E); break;
                            case 0x04: RLC(H); break;
                            case 0x05: RLC(L); break;
                            case 0x06: RLC(memory[concat_bytes(L,H)]); break;
                            
                            /* 6. RL n */
                            case 0x17: RL(A); break;
                            case 0x10: RL(B); break;
                            case 0x11: RL(C); break;
                            case 0x12: RL(D); break;
                            case 0x13: RL(E); break;
                            case 0x14: RL(H); break;
                            case 0x15: RL(L); break;
                            case 0x16: RL(memory[concat_bytes(L,H)]); break;
                            
                            /* 7. RRC n */
                            case 0x0F: RRC(A); break;
                            case 0x08: RRC(B); break;
                            case 0x09: RRC(C); break;
                            case 0x0A: RRC(D); break;
                            case 0x0B: RRC(E); break;
                            case 0x0C: RRC(H); break;
                            case 0x0D: RRC(L); break;
                            case 0x0E: RRC(memory[concat_bytes(L,H)]); break;
                            
                            /* 8. RR n */
                            case 0x1F: RR(A); break;
                            case 0x18: RR(B); break;
                            case 0x19: RR(C); break;
                            case 0x1A: RR(D); break;
                            case 0x1B: RR(E); break;
                            case 0x1C: RR(H); break;
                            case 0x1D: RR(L); break;
                            case 0x1E: RR(memory[concat_bytes(L,H)]); break;

                            /* 9. SLA n */
                            case 0x27: SLA(A); break;
                            case 0x20: SLA(B); break;
                            case 0x21: SLA(C); break;
                            case 0x22: SLA(D); break;
                            case 0x23: SLA(E); break;
                            case 0x24: SLA(H); break;
                            case 0x25: SLA(L); break;
                            case 0x26: SLA(memory[concat_bytes(L,H)]); break;

                            /* 10. SRA n */
                            case 0x2F: SRA(A); break;
                            case 0x28: SRA(B); break;
                            case 0x29: SRA(C); break;
                            case 0x2A: SRA(D); break;
                            case 0x2B: SRA(E); break;
                            case 0x2C: SRA(H); break;
                            case 0x2D: SRA(L); break;
                            case 0x2E: SRA(memory[concat_bytes(L,H)]); break;

                            /* 11. SRL n */
                            case 0x3F: SRL(A); break;
                            case 0x38: SRL(B); break;
                            case 0x39: SRL(C); break;
                            case 0x3A: SRL(D); break;
                            case 0x3B: SRL(E); break;
                            case 0x3C: SRL(H); break;
                            case 0x3D: SRL(L); break;
                            case 0x3E: SRL(memory[concat_bytes(L,H)]); break;

                            /* 1. SWAP n */
                            case 0x37: SWAP(A); break;
                            case 0x30: SWAP(B); break;
                            case 0x31: SWAP(C); break;
                            case 0x32: SWAP(D); break;
                            case 0x33: SWAP(E); break;
                            case 0x34: SWAP(H); break;
                            case 0x35: SWAP(L); break;
                            case 0x36: SWAP(memory[concat_bytes(L, H)]); break;
                        }
                        break;
                    case 01:
                        // BIT -- Test Bit 
                        switch(z) {
                            case 0: BIT(B, y); break;
                            case 1: BIT(C, y); break;
                            case 2: BIT(D, y); break;
                            case 3: BIT(E, y); break;
                            case 4: BIT(H, y); break;
                            case 5: BIT(L, y); break;
                            case 6: BIT(memory[concat_bytes(L, H)], y); break; 
                            case 7: BIT(A, y); break;
                        }
                        break;
                    case 02:
                        // RES -- Reset Bit
                        switch(z) {
                            case 0: RESET(B, y); break;
                            case 1: RESET(C, y); break;
                            case 2: RESET(D, y); break;
                            case 3: RESET(E, y); break;
                            case 4: RESET(H, y); break;
                            case 5: RESET(L, y); break;
                            case 6: RESET(memory[concat_bytes(L, H)], y); break; 
                            case 7: RESET(A, y); break;
                        }
                        break;
                    case 03:
                        // SET -- Set Bit
                        switch(z) {
                            case 0: SET(B, y); break;
                            case 1: SET(C, y); break;
                            case 2: SET(D, y); break;
                            case 3: SET(E, y); break;
                            case 4: SET(H, y); break;
                            case 5: SET(L, y); break;
                            case 6: SET(memory[concat_bytes(L, H)], y); break; 
                            case 7: SET(A, y); break;
                        }
                        break;
                } 
            }
            break;
        
        /*** Jumps ***/ 
        /* 1. JP nn */
        case 0xC3: JUMP(concat_bytes(memory[PC+1], memory[PC+2])); break;

        /* 2. JP cc,nn */
        case 0xC2: if (!flag.Z) {JUMP(concat_bytes(memory[PC+1], memory[PC+2])); PC -= 3;} break;
        case 0xCA: if (flag.Z) {JUMP(concat_bytes(memory[PC+1], memory[PC+2])); PC -= 3;} break;
        case 0xD2: if (!flag.C) {JUMP(concat_bytes(memory[PC+1], memory[PC+2])); PC -= 3;} break;
        case 0xDA: if (flag.C) {JUMP(concat_bytes(memory[PC+1], memory[PC+2])); PC -= 3;} break;

        /* 3. JP (HL) */ 
        case 0xE9: JUMP(concat_bytes(L, H)); break;

        /* 4. JR n */ 
        case 0x18: JUMP_R(memory[PC + 1]); break;

        /* 5. JR cc,n */ 
        case 0x20: if (!flag.Z) JUMP_R(memory[PC+1]); break;
        case 0x28: if (flag.Z) JUMP_R(memory[PC+1]); break;
        case 0x30: if (!flag.C) JUMP_R(memory[PC+1]); break;
        case 0x38: if (flag.C) JUMP_R(memory[PC+1]); break;

        /*** Calls ***/ 
        /* 1. CALL nn */
        case 0xCD: push_addr(PC + 3); JUMP(concat_bytes(memory[PC + 1], memory[PC + 2])); break;

        /* 2. CALL cc,nn */ 
        case 0xC4: if (!flag.Z) {
                       push_addr(PC + 3); 
                       JUMP(concat_bytes(memory[PC + 1], memory[PC + 2])); 
                       PC -= 3;
                   } break;
        case 0xCC: if (flag.Z) {
                       push_addr(PC + 3); 
                       JUMP(concat_bytes(memory[PC + 1], memory[PC + 2])); 
                       PC -= 3;
                   } break;
        case 0xD4: if (!flag.C) {
                       push_addr(PC + 3); 
                       JUMP(concat_bytes(memory[PC + 1], memory[PC + 2])); 
                       PC -= 3;
                   } break;
        case 0xDC: if (flag.C) {
                       push_addr(PC + 3); 
                       JUMP(concat_bytes(memory[PC + 1], memory[PC + 2])); 
                       PC -= 3;
                   } break;
        
        /*** Restarts ***/ 
        /* 1. RST n*/
        case 0xC7: push_addr(PC + 1); JUMP(0x00); break;
        case 0xCF: push_addr(PC + 1); JUMP(0x08); break;
        case 0xD7: push_addr(PC + 1); JUMP(0x10); break;
        case 0xDF: push_addr(PC + 1); JUMP(0x18); break;
        case 0xE7: push_addr(PC + 1); JUMP(0x20); break;
        case 0xEF: push_addr(PC + 1); JUMP(0x28); break;
        case 0xF7: push_addr(PC + 1); JUMP(0x30); break;
        case 0xFF: push_addr(PC + 1); JUMP(0x38); break;

        /*** Returns ***/
        /* 1. RET */ 
        case 0xC9: PC = pop_addr(); break;

        /* 2. RET cc */
        case 0xC0: if (!flag.Z) PC = pop_addr(); else PC++; break;
        case 0xC8: if (flag.Z) PC = pop_addr(); else PC++; break;
        case 0xD0: if (!flag.C) PC = pop_addr(); else PC++; break;
        case 0xD8: if (flag.C) PC = pop_addr(); else PC++; break;

        /* 3. RETI */ 
        //TODO: case 0xD9: 
    }


    if (OP_CODE != 0xCB) {
        CLK += OP_cycles[OP_CODE]; 
        PC += OP_len[OP_CODE];
    } else {
        unsigned char EX_OP_CODE = memory[PC + 1];
        CLK += EX_OP_cycles[EX_OP_CODE]; 
        PC += EX_OP_len[EX_OP_CODE];
    }

    return 0;
}

int main() {
    CPU cpu; 
    cpu.memory.cartridge.load_rom("../res/ttt.gb");

    cpu.print_state();

//    for (int i = 0; i < 6 + 3 * (0x9FFF - 0x8000) + 26 + 30 + 50 + 3948 + 46 + 6 + 58 + 79 + 120 + 13 + 18500 + 375 + 102; i++) {
    int i = 0;
    while (true) {
        i++;
        //cpu.memory.graphics.dump_tiles();
        cpu.fetch_and_execute();
        cpu.print_state();
        cpu.memory.graphics.step(1);
        if ((i % 300) == 0) cpu.memory.graphics.dump_display();
    }

    //TODO: Check which count is right: 380732, or this
    //cpu.memory.graphics.dump_state();
    //cpu.memory.graphics.dump_tiles();
    //cpu.memory.graphics.dump_map_indices();

    cout << endl; //XXX: Voodoo...
    return 0; 
}
