#include "cpu.h"
#include <iostream>
#include <iomanip>

using namespace std;

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

void CPU::print_state() {
    //XXX:
    if (CLK < 380724) return;

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

    int cycles = 0;
    int len = 0; 

    unsigned char OP_CODE = memory[PC];
   
    switch (OP_CODE) {
        case 0x3C: 
            //Increment A
            cycles = 4;
            len = 1; 
            A++; 
            flag.Z = (A == 0);
            flag.N = false;
            //XXX :Need to set flag.H for half carry 
            break; 
        
        case 0x04: 
            //Increment B
            cycles = 4;
            len = 1; 
            B++; 
            flag.Z = (B == 0);
            flag.N = false;
            //XXX :Need to set flag.H for half carry 
            break; 
        
        case 0x0C: 
            //Increment C
            cycles = 4;
            len = 1; 
            C++; 
            flag.Z = (C == 0);
            flag.N = false;
            //XXX :Need to set flag.H for half carry 
            break; 
        
        case 0x14: 
            //Increment D
            cycles = 4;
            len = 1; 
            D++; 
            flag.Z = (D == 0);
            flag.N = false;
            //XXX :Need to set flag.H for half carry 
            break; 
        
        case 0x1C: 
            //Increment E
            cycles = 4;
            len = 1; 
            E++; 
            flag.Z = (E == 0);
            flag.N = false;
            //XXX :Need to set flag.H for half carry 
            break; 
        
        case 0x24: 
            //Increment H
            cycles = 4;
            len = 1; 
            H++; 
            flag.Z = (H == 0);
            flag.N = false;
            //XXX :Need to set flag.H for half carry 
            break; 
        
        case 0x2C: 
            //Increment L
            cycles = 4;
            len = 1; 
            L++; 
            flag.Z = (L == 0);
            flag.N = false;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x34: 
            //Increment HL
            cycles = 12;
            len = 1; 
            increment_pair(L, H); 
            flag.Z = (H == 0) && (L == 0); 
            flag.N = false;
            //XXX: flag.H set if no borrow from bit 4 
            break; 

        case 0x03:
            //Increment BC
            cycles = 8;
            len = 1;
            increment_pair(C, B); 
            break;

        case 0x13:
            //Increment DE
            cycles = 8;
            len = 1;
            increment_pair(E, D); 
            break;

        case 0x23:
            //Increment HL
            cycles = 8;
            len = 1;
            increment_pair(L, H); 
            break;

        case 0x33:
            //Increment SP
            cycles = 8;
            len = 1;
            SP++; 
            break;

        case 0x3D: 
            //Decrement A
            cycles = 4;
            len = 1; 
            A--; 
            flag.Z = (A == 0);
            flag.N = true;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x05: 
            //Decrement B
            cycles = 4;
            len = 1; 
            B--; 
            flag.Z = (B == 0);
            flag.N = true;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x0D: 
            //Decrement C
            cycles = 4;
            len = 1; 
            C--; 
            flag.Z = (C == 0);
            flag.N = true;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x15: 
            //Decrement D
            cycles = 4;
            len = 1; 
            D--; 
            flag.Z = (D == 0);
            flag.N = true;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x1D: 
            //Decrement E
            cycles = 4;
            len = 1; 
            E--; 
            flag.Z = (E == 0);
            flag.N = true;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x25: 
            //Decrement H
            cycles = 4;
            len = 1; 
            H--; 
            flag.Z = (H == 0);
            flag.N = true;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x2D: 
            //Decrement L
            cycles = 4;
            len = 1; 
            L--; 
            flag.Z = (L == 0);
            flag.N = true;
            //XXX :Need to set flag.H for half carry 
            break; 

        case 0x35: 
            //Decrement HL
            cycles = 12;
            len = 1; 
            decrement_pair(L, H); 
            flag.Z = (H == 0) && (L == 0); 
            flag.N = true;
            //XXX: flag.H set if no borrow from bit 4 
            break; 

        case 0x0B:
            //Decrement BC
            cycles = 8;
            len = 1;
            decrement_pair(C, B); 
            break;

        case 0x1B:
            //Decrement DE
            cycles = 8;
            len = 1;
            decrement_pair(E, D); 
            break;

        case 0x2B:
            //Decrement HL
            cycles = 8;
            len = 1;
            decrement_pair(L, H); 
            break;

        case 0x3B:
            //Decrement SP
            cycles = 8;
            len = 1;
            SP--; 
            break;

        case 0x06:
            //8-bit immediate load into B
            cycles = 8;
            len = 2;
            B = memory[PC + 1];
            break; 

        case 0x0E:
            //8-bit immediate load into C
            cycles = 8;
            len = 2;
            C = memory[PC + 1];
            break; 

        case 0x16:
            //8-bit immediate load into D
            cycles = 8;
            len = 2;
            D = memory[PC + 1];
            break; 

        case 0x1E:
            //8-bit immediate load into E
            cycles = 8;
            len = 2;
            E = memory[PC + 1];
            break; 

        case 0x26:
            //8-bit immediate load into H
            cycles = 8;
            len = 2;
            H = memory[PC + 1];
            break; 

        case 0x2E:
            //8-bit immediate load into L
            cycles = 8;
            len = 2;
            L = memory[PC + 1];
            break; 

        case 0x18:
            //Jump if not zero
            cycles = 8; 
            len = 2;
            PC += (signed char) memory[PC + 1];
            break;

        case 0x20:
            //Jump if not zero
            cycles = 8; 
            len = 2;
            if (!flag.Z) PC += (signed char) memory[PC + 1];
            break;

        case 0x28:
            //Jump if zero
            cycles = 8; 
            len = 2;
            if (flag.Z) PC += (signed char) memory[PC + 1];
            break;

        case 0x01: 
            //16-bit immediate load into BC
            cycles = 12; 
            len = 3;
            B = memory[PC + 2]; 
            C = memory[PC + 1];
            break;

        case 0x11: 
            //16-bit immediate load into DE
            cycles = 12; 
            len = 3;
            D = memory[PC + 2]; 
            E = memory[PC + 1];
            break;
    
        case 0x1A:
            //Put value n into A
            cycles = 8;
            len = 1;

            A = memory[concat_bytes(E, D)];
            break;

        case 0x21: 
            //16-bit immediate load into HL
            cycles = 12; 
            len = 3;
            H = memory[PC + 2]; 
            L = memory[PC + 1];
            break;

        case 0x31: 
            //16-bit immediate load into stack pointer
            cycles = 12; 
            len = 3;
            SP = concat_bytes(memory[PC + 1], memory[PC + 2]);
            break;

        case 0x22: 
            //Put A into mem[HL], Increment HL
            cycles = 8;
            len = 1;
            memory[concat_bytes(L, H)] = A;
            increment_pair(L, H); 
            break;

        case 0x32: 
            //Put A into mem[HL], Decrement HL
            cycles = 8;
            len = 1;
            memory[concat_bytes(L, H)] = A;
            decrement_pair(L, H); 
            break;

        case 0x3E:
            //Immediate load into A
            cycles = 8;
            len = 2;
            A = memory[PC + 1];
            break;

        case 0x47:
            //Load A into B
            cycles = 4;
            len = 1;
            B = A;
            break;

        case 0x4F: 
            // Load A into C
            cycles = 4;
            len = 1;
            C = A;
            break;

        case 0x57: 
            // Load A into D
            cycles = 4;
            len = 1;
            D = A;
            break;

        case 0x5F: 
            // Load A into E
            cycles = 4;
            len = 1;
            E = A;
            break;

        case 0x67: 
            // Load A into H
            cycles = 4;
            len = 1;
            H = A;
            break;

        case 0x6F: 
            // Load A into L
            cycles = 4;
            len = 1;
            L = A;
            break;

        case 0x77:
            // Load A into mem[HL]
            cycles = 8; 
            len = 1;
            memory[concat_bytes(L, H)] = A;
            break;

        case 0x7D:
            //Load L into A
            cycles = 4;
            len = 1; 
            A = L;
            break;

        case 0x78:
            //Load B into A
            cycles = 4;
            len = 1; 
            A = B;
            break;

        case 0x7F:
           // LD A, A
           cycles = 4;
           len = 1; 
           // XXX: A = A;
           break; 

        case 0xAF:
            //XOR A with A store in A
            cycles = 4;
            len = 1;
            A = A ^ A; 

            //Set flags
            flag.Z = (A == 0);
            flag.N = false;
            flag.H = false;
            flag.C = false; 
            break;

        case 0x17:
            cycles = 4;
            len = 1; 
            RL(A);
            break;

        case 0x7B: 
            // LD A, E
            cycles = 4; 
            len = 1; 
            A = E; 
            break;

        case 0x7C: 
            // LD A, H
            cycles = 4; 
            len = 1; 
            A = H; 
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
                        cycles = 8;
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
                        cycles = 8;
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
                                cycles = 16; //XXX: HL takes more cycles..
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
            cycles = 12;
            len = 0;
            {
                unsigned short addr = PC + 3;
                push_addr(addr);
                PC = concat_bytes(memory[PC + 1], memory[PC + 2]);
            }
            break;

        case 0xC9:
            cycles = 8;
            len = 0; 
            PC = pop_addr();
            break;

        case 0xE0: 
            // Load A into mem[0xFF00 + n]
            cycles = 12;
            len = 2; 
            memory[0xFF00 + memory[PC + 1]] = A;
            break;

        case 0xF0: 
            // Load A into mem[0xFF00 + n]
            cycles = 12;
            len = 2; 
            A = memory[0xFF00 + memory[PC + 1]];
            break;

        case 0xE2: 
            // Load A into mem[0xFF00 + C]
            cycles = 8; 
            len = 1;
            memory[0xFF00 + C] = A;
            break;
        
        case 0xF5: 
            //Push AF
            cycles = 16;
            len = 1;
            push_val(A);
            push_val(F);
            break;

        case 0xC5: 
            //Push BC
            cycles = 16;
            len = 1;
            push_val(B);
            push_val(C);
            break;

        case 0xD5: 
            //Push DE
            cycles = 16;
            len = 1;
            push_val(D);
            push_val(E);
            break;

        case 0xE5: 
            //Push E5
            cycles = 16;
            len = 1;
            push_val(H);
            push_val(L);
            break;

        case 0xF1: 
            //Pop AF
            cycles = 12;
            len = 1;
            F = pop_val();
            A = pop_val();
            break;

        case 0xC1: 
            //Push BC
            cycles = 12;
            len = 1;
            C = pop_val();
            B = pop_val();
            break;

        case 0xD1: 
            //Push DE
            cycles = 12;
            len = 1;
            E = pop_val();
            D = pop_val();
            break;

        case 0xE1: 
            //Push HL
            cycles = 12;
            len = 1;
            L = pop_val();
            H = pop_val();
            break;

        case 0xEA: 
            // Put value A into mem[n]
            cycles = 16;
            len = 3;
            memory[concat_bytes(memory[PC + 1], memory[PC + 2])] = A;
            break;

        case 0xBF:
            //Compare A to A
            cycles = 4;
            len = 1; 
            flag.Z = true;
            flag.N = true;
            //TODO: flag.H
            flag.C = false;
            break; 

        case 0xB8:
            //Compare B to A
            cycles = 4;
            len = 1; 
            flag.Z = (A == B);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A < B);
            break; 

        case 0xB9:
            //Compare C to A
            cycles = 4;
            len = 1; 
            flag.Z = (A == C);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A < C);
            break; 

        case 0xBA:
            //Compare D to A
            cycles = 4;
            len = 1; 
            flag.Z = (A == D);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A < D);
            break; 

        case 0xBB:
            //Compare E to A
            cycles = 4;
            len = 1; 
            flag.Z = (A == E);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A < E);
            break; 

        case 0xBC:
            //Compare H to A
            cycles = 4;
            len = 1; 
            flag.Z = (A == H);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A < H);
            break; 

        case 0xBD:
            //Compare L to A
            cycles = 4;
            len = 1; 
            flag.Z = (A == L);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A < L);
            break; 

        case 0xBE: 
            // Compare mem[HL] to A
            cycles = 8; 
            len = 1;
            flag.Z = (A == memory[concat_bytes(L, H)]);
            flag.N = true;
            //XXX: flag.H
            flag.C = (A < memory[concat_bytes(L, H)]);
            break;


        case 0xFE: 
            // Compare n to A
            cycles = 8; 
            len = 2;
            flag.Z = (A == memory[PC + 1]);
            flag.N = true;
            //XXX: flag.H
            flag.C = (A < memory[PC + 1]);
            break;

        case 0x97:
            //Subtract A from A
            cycles = 4;
            len = 1; 
            A -= A;
            flag.Z = (A == 0);
            flag.N = true;

            //TODO: flag.H
            flag.C = (A + A < A);
            break; 

        case 0x90:
            //Subtract B from A
            cycles = 4;
            len = 1; 
            A -= B;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A + B < B);
            break; 

        case 0x91:
            //Subtract C from A
            cycles = 4;
            len = 1; 
            A -= C;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A + C < C);
            break; 

        case 0x92:
            //Subtract D from A
            cycles = 4;
            len = 1; 
            A -= D;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A + D < D);
            break; 

        case 0x93:
            //Subtract E from A
            cycles = 4;
            len = 1; 
            A -= E;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A + E < E);
            break; 

        case 0x94:
            //Subtract H from A
            cycles = 4;

            len = 1; 
            A -= H;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A + H < H);
            break; 

        case 0x95:
            //Subtract L from A
            cycles = 4;
            len = 1; 
            A -= L;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A + L < L);
            break; 

        case 0xD6:
            //Subtract n from A
            cycles = 8;
            len = 2; 
            A -= memory[PC + 1];
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            flag.C = (A + memory[PC + 1] < memory[PC + 1]);
            break; 

        case 0x87:
            //Add A to A
            cycles = 4;
            len = 1; 
            A += A;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0x80:
            //Add B to A
            cycles = 4;
            len = 1; 
            A += B;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0x81:
            //Add C to A
            cycles = 4;
            len = 1; 
            A += C;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0x82:
            //Add D to A
            cycles = 4;
            len = 1; 
            A += D;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0x83:
            //Add E to A
            cycles = 4;
            len = 1; 
            A += E;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0x84:
            //Add H to A
            cycles = 4;
            len = 1; 
            A += H;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0x85:
            //Add L to A
            cycles = 4;
            len = 1; 
            A += L;
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0x86:
            //Add HL to A
            cycles = 4;
            len = 1; 
            A += memory[concat_bytes(L, H)];
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C 
            break; 

        case 0xC6:
            //Add n to A
            cycles = 8;
            len = 2; 
            A += memory[PC + 1];
            flag.Z = (A == 0);
            flag.N = true;
            //TODO: flag.H
            //TODO: flag.C
            break; 
    }

    PC += len;
    CLK += cycles; 

    return 0;
}

int main() {
    CPU cpu; 
    cpu.memory.cartridge.load_rom("../res/Pokemon Red.gb");

    cpu.print_state();

    for (int i = 0; i < 6 + 3 * (0x9FFF - 0x8000) + 26 + 30 + 50 + 3948 + 46 + 6 + 58 + 79 + 120 + 13 + 18500 + 375 + 102; i++) {
        //cpu.memory.graphics.dump_tiles();
        cpu.fetch_and_execute();
        cpu.print_state();
        if ((i % 100) == 0) cpu.memory.graphics.dump_display();
    }

    //cpu.memory.graphics.dump_state();
    //cpu.memory.graphics.dump_tiles();
    //cpu.memory.graphics.dump_map_indices();

    cout << endl; //XXX: Voodoo...
    return 0; 
}
