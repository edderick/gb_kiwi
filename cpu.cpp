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
    /*0x*/  0,  3,  1,  0,  0,  0,  2,  0,  0,  0,  1,  0,  0,  0,  2,  0,
    /*1x*/  0,  3,  1,  0,  0,  0,  2,  0,  0,  0,  1,  0,  0,  0,  2,  0,
    /*2x*/  0,  3,  1,  0,  0,  0,  2,  0,  0,  0,  1,  0,  0,  0,  2,  0,
    /*3x*/  0,  3,  1,  0,  0,  0,  2,  0,  0,  0,  1,  0,  0,  0,  2,  0,
    /*4x*/  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    /*5x*/  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    /*6x*/  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    /*7x*/  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    /*8x*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*9x*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*Ax*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*Bx*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*Cx*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*Dx*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*Ex*/  2,  0,  1,  0,  0,  0,  0,  0,  0,  0,  3,  0,  0,  0,  0,  0,
    /*Fx*/  2,  0,  1,  0,  0,  0,  0,  0,  2,  1,  3,  0,  0,  0,  0,  0,
}; 

unsigned char EX_OP_len[0x100] = {  
    /*     x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, xA, xB, xC, xD, xE, xF, */
    /*0x*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*1x*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*2x*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*3x*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*4x*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*5x*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*6x*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*7x*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*8x*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*9x*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*Ax*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*Bx*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*Cx*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*Dx*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*Ex*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*Fx*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
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

void CPU::print_state() {
    //XXX:
    if (CLK < 380700) return;

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
    cout << endl;
}

int CPU::fetch_and_execute() {
    // Read in opcode at PC
    // Execute OP 
    // Update PC?

    int len = 0; 

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
        case 0xE0: LD(memory[0xFF00 + memory[PC + 1]], A); break;

        /* 20. LDH A,(n) */
        case 0xF0: LD(A, memory[0xFF00 + memory[PC + 1]]); break;

        
        /*** 16-bit Loads ***/
        /* 1. LD n,nn */
        case 0x01: LD_16(B, C, memory[PC + 2], memory[PC + 1]); break;
        case 0x11: LD_16(D, E, memory[PC + 2], memory[PC + 1]); break;
        case 0x21: LD_16(H, L, memory[PC + 2], memory[PC + 1]); break;
        case 0x31: LD(SP, concat_bytes(memory[PC + 1], memory[PC + 2])); break;

        /* 2. LD SP,HL */
        case 0xF9: LD(SP, concat_bytes(L, H));  break;

        /* 3. LDHL SP,n */
        case 0xF8: LDHL(SP, memory[PC + 1]); break;



        case 0x3C: 
            //Increment A
            len = 1; 
            A++; 
            flag.Z = (A == 0);
            flag.N = false;
            //XXX :Need to set flag.H for half carry 
            break; 
        
        case 0x04: 
            //Increment B
            len = 1; 
            B++; 
            flag.Z = (B == 0);
            flag.N = false;
            //XXX :Need to set flag.H for half carry 
            break; 
        
        case 0x0C: 
            //Increment C
            len = 1; 
            C++; 
            flag.Z = (C == 0);
            flag.N = false;
            //XXX :Need to set flag.H for half carry 
            break; 
        
        case 0x14: 
            //Increment D
            len = 1; 
            D++; 
            flag.Z = (D == 0);
            flag.N = false;
            //XXX :Need to set flag.H for half carry 
            break; 
        
        case 0x1C: 
            //Increment E
            len = 1; 
            E++; 
            flag.Z = (E == 0);
            flag.N = false;
            //XXX :Need to set flag.H for half carry 
            
        
        case 0x24: 
            //Increment H
            len = 1; 
            H++; 
            flag.Z = (H == 0);
            flag.N = false;
            //XXX :Need to set flag.H for half carry 
            break; 
        
        case 0x2C: 
            //Increment L
            L++; 
            flag.Z = (L == 0);
            flag.N = false;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x34: 
            //Increment HL
            len = 1; 
            increment_pair(L, H); 
            flag.Z = (H == 0) && (L == 0); 
            flag.N = false;
            //XXX: flag.H set if no borrow from bit 4 
            break; 

        case 0x03:
            //Increment BC
            len = 1;
            increment_pair(C, B); 
            break;

        case 0x13:
            //Increment DE
            len = 1;
            increment_pair(E, D); 
            break;

        case 0x23:
            //Increment HL
            len = 1;
            increment_pair(L, H); 
            break;

        case 0x33:
            //Increment SP
            len = 1;
            SP++; 
            break;

        case 0x3D: 
            //Decrement A
            len = 1; 
            A--; 
            flag.Z = (A == 0);
            flag.N = true;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x05: 
            //Decrement B
            len = 1; 
            B--; 
            flag.Z = (B == 0);
            flag.N = true;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x0D: 
            //Decrement C
            len = 1; 
            C--; 
            flag.Z = (C == 0);
            flag.N = true;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x15: 
            //Decrement D
            len = 1; 
            D--; 
            flag.Z = (D == 0);
            flag.N = true;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x1D: 
            //Decrement E
            len = 1; 
            E--; 
            flag.Z = (E == 0);
            flag.N = true;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x25: 
            //Decrement H
            len = 1; 
            H--; 
            flag.Z = (H == 0);
            flag.N = true;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x2D: 
            //Decrement L
            len = 1; 
            L--; 
            flag.Z = (L == 0);
            flag.N = true;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x35: 
            //Decrement HL
            len = 1; 
            decrement_pair(L, H); 
            flag.Z = (H == 0) && (L == 0); 
            flag.N = true;
            //XXX: flag.H set if no borrow from bit 4 
            break; 

        case 0x0B:
            //Decrement BC
            len = 1;
            decrement_pair(C, B); 
            break;

        case 0x1B:
            //Decrement DE
            len = 1;
            decrement_pair(E, D); 
            break;

        case 0x2B:
            //Decrement HL
            len = 1;
            decrement_pair(L, H); 
            break;

        case 0x3B:
            //Decrement SP
            len = 1;
            SP--; 
            break;

        case 0x18:
            //Jump if not zero
            len = 2;
            PC += (signed char) memory[PC + 1];
            break;

        case 0x20:
            //Jump if not zero
            len = 2;
            if (!flag.Z) PC += (signed char) memory[PC + 1];
            break;

        case 0x28:
            //Jump if zero
            len = 2;
            if (flag.Z) PC += (signed char) memory[PC + 1];
            break;

        case 0xAF:
            //XOR A with A store in A
            len = 1;
            A = A ^ A; 

            //Set flags
            flag.Z = (A == 0);
            flag.N = false;
            flag.H = false;
            flag.C = false; 
            break;

        case 0x17:
            len = 1; 
            RL(A);
            break;

        case 0xCB: 
            {
                //Extension OP_CODES
                char x = (memory[PC + 1] & 0xC0) >> 6;
                char y = (memory[PC + 1] & 0x38) >> 3;
                char z = (memory[PC + 1] & 0x07);

                switch(x) {
                    case 00: 
                        //TODO: Rotate
                        len = 2;
                        flag.N = false;
                        flag.H = false;
                        switch(memory[PC + 1]) {
                            case 0x17: RL(A); break;
                            case 0x10: RL(B); break;
                            case 0x11: RL(C); break;
                            case 0x12: RL(D); break;
                            case 0x13: RL(E); break;
                            case 0x14: RL(H); break;
                            case 0x15: RL(L); break;
                        }
                        break;
                    case 01:
                        // BIT -- Test Bit 
                        len = 2; 
                        flag.N = false;
                        flag.H = true;
                        switch(z) {
                            case 0: // B
                                flag.Z = ((B & (1 << y)) == 0);
                                break;
                            case 1: // C
                                flag.Z = ((C & (1 << y)) == 0);
                                break;
                            case 2: // D
                                flag.Z = ((D & (1 << y)) == 0);
                                break;
                            case 3: // E
                                flag.Z = ((E & (1 << y)) == 0);
                                break;
                            case 4: // H
                                flag.Z = ((H & (1 << y)) == 0);
                                break;
                            case 5: // L
                                flag.Z = ((L & (1 << y)) == 0);
                                break;
                            case 6: // HL
                                //TODO: Fill this in
                                break;
                            case 7: // A
                                flag.Z = ((A & (1 << y)) == 0);
                                break;
                        }
                        break;
                    case 02:
                        // TODO: RES -- Reset Bit
                        break;
                    case 03:
                        // TODO: SET -- Set Bit
                        break;
                } 
            }
            break;
         
        case 0xCD:
            // Call addr
            len = 0;
            {
                unsigned short addr = PC + 3;
                push_addr(addr);
                PC = concat_bytes(memory[PC + 1], memory[PC + 2]);
            }
            break;

        case 0xC9:
            len = 0; 
            PC = pop_addr();
            break;
        
        case 0xF5: 
            //Push AF
            len = 1;
            push_val(A);
            push_val(F);
            break;

        case 0xC5: 
            //Push BC
            len = 1;
            push_val(B);
            push_val(C);
            break;

        case 0xD5: 
            //Push DE
            len = 1;
            push_val(D);
            push_val(E);
            break;

        case 0xE5: 
            //Push E5
            len = 1;
            push_val(H);
            push_val(L);
            break;

        case 0xF1: 
            //Pop AF
            len = 1;
            F = pop_val();
            A = pop_val();
            break;

        case 0xC1: 
            //Push BC
            len = 1;
            C = pop_val();
            B = pop_val();
            break;

        case 0xD1: 
            //Push DE
            len = 1;
            E = pop_val();
            D = pop_val();
            break;

        case 0xE1: 
            //Push HL
            len = 1;
            L = pop_val();
            H = pop_val();
            break;

        case 0xBF:
            //Compare A to A
            len = 1; 
            flag.Z = true;
            flag.N = true;
            //TODO: flag.H
            flag.C = false;
            break; 

        case 0xB8:
            //Compare B to A
            len = 1; 
            flag.Z = (A == B);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A < B);
            break; 

        case 0xB9:
            //Compare C to A
            len = 1; 
            flag.Z = (A == C);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A < C);
            break; 

        case 0xBA:
            //Compare D to A
            len = 1; 
            flag.Z = (A == D);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A < D);
            break; 

        case 0xBB:
            //Compare E to A
            len = 1; 
            flag.Z = (A == E);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A < E);
            break; 

        case 0xBC:
            //Compare H to A
            len = 1; 
            flag.Z = (A == H);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A < H);
            break; 

        case 0xBD:
            //Compare L to A
            len = 1; 
            flag.Z = (A == L);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A < L);
            break; 

        case 0xBE: 
            // Compare mem[HL] to A
            len = 1;
            flag.Z = (A == memory[concat_bytes(L, H)]);
            flag.N = true;
            //XXX: flag.H
            flag.C = (A < memory[concat_bytes(L, H)]);
            break;


        case 0xFE: 
            // Compare n to A
            len = 2;
            flag.Z = (A == memory[PC + 1]);
            flag.N = true;
            //XXX: flag.H
            flag.C = (A < memory[PC + 1]);
            break;

        case 0x97:
            //Subtract A from A
            len = 1; 
            A -= A;
            flag.Z = (A == 0);
            flag.N = true;

            //TODO: flag.H
            flag.C = (A + A < A);
            break; 

        case 0x90:
            //Subtract B from A
            len = 1; 
            A -= B;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A + B < B);
            break; 

        case 0x91:
            //Subtract C from A
            len = 1; 
            A -= C;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A + C < C);
            break; 

        case 0x92:
            //Subtract D from A
            len = 1; 
            A -= D;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A + D < D);
            break; 

        case 0x93:
            //Subtract E from A
            len = 1; 
            A -= E;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A + E < E);
            break; 

        case 0x94:
            //Subtract H from A
            len = 1; 
            A -= H;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A + H < H);
            break; 

        case 0x95:
            //Subtract L from A
            len = 1; 
            A -= L;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A + L < L);
            break; 

        case 0xD6:
            //Subtract n from A
            len = 2; 
            A -= memory[PC + 1];
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A + memory[PC + 1] < memory[PC + 1]);
            break; 

        case 0x87:
            //Add A to A
            len = 1; 
            A += A;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0x80:
            //Add B to A
            len = 1; 
            A += B;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0x81:
            //Add C to A
            len = 1; 
            A += C;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0x82:
            //Add D to A
            len = 1; 
            A += D;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0x83:
            //Add E to A
            len = 1; 
            A += E;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0x84:
            //Add H to A
            len = 1; 
            A += H;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0x85:
            //Add L to A
            len = 1; 
            A += L;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0x86:
            //Add HL to A
            len = 1; 
            A += memory[concat_bytes(L, H)];
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0xC6:
            //Add n to A
            len = 2; 
            A += memory[PC + 1];
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C
            break; 
    }


    if (OP_CODE != 0xCB) {
        CLK += OP_cycles[OP_CODE]; 
        len += OP_len[OP_CODE];
    } else {
        unsigned char EX_OP_CODE = memory[PC + 1];
        CLK += EX_OP_cycles[EX_OP_CODE]; 
        len += EX_OP_len[EX_OP_CODE];
    }


    PC += len;
    return 0;
}

int main() {
    CPU cpu; 
    cpu.memory.cartridge.load_rom("../res/Pokemon Red.gb");

    cpu.print_state();

    for (int i = 0; i < 6 + 3 * (0x9FFF - 0x8000) + 26 + 30 + 50 + 3948 + 46 + 6 + 58 + 79 + 120 + 13 + 18500 + 375 + 102; i++) {
//    int i = 0;
//    while (true) {
//        i++;
        //cpu.memory.graphics.dump_tiles();
        cpu.fetch_and_execute();
        cpu.print_state();
        if ((i % 100) == 0) cpu.memory.graphics.dump_display();
    }

    //TODO: Check which count is right: 380732, or this
    //cpu.memory.graphics.dump_state();
    //cpu.memory.graphics.dump_tiles();
    //cpu.memory.graphics.dump_map_indices();

    cout << endl; //XXX: Voodoo...
    return 0; 
}
