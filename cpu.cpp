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
void CPU::decrement_HL() {
    unsigned short HL = concat_bytes(L, H);
    HL--; 
    H = (0xFF00 & HL) >> 8;
    L = 0x00FF & HL;

    flag.Z = (HL == 0); 
    flag.N = true;
    flag.H = (L == 0xFF); //XXX: UNTESTED -- set if no borrow from bit 4 
} 

void CPU::print_state() {
    //XXX:
    if (CLK < 196628) return;



    cout << "PC: " << hex << setw(4) << setfill('0') << PC;
    cout << "   CLK: " << dec << CLK;
    cout << "   SP: " << hex << setw(4) << setfill('0') << SP;
    cout << "\n";
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
    cout << "\n" << endl;
}

int CPU::fetch_and_execute() {
    // Read in opcode at PC
    // Execute OP 
    // Update PC?

    int cycles = 0;
    int len = 0; 

    unsigned char OP_CODE = memory[PC];
    
    switch (OP_CODE) {
        case 0x0C: 
            //Increment C
            cycles = 4;
            len = 1; 
            C++; 
            break; 

        case 0x0E:
            //8-bit immediate load into C
            cycles = 8;
            len = 2;
            C = memory[PC + 1];
            break; 

        case 0x20:
            //Jump if not zero
            cycles = 8; 
            len = 2;
            if (!flag.Z) PC += (signed char) memory[PC + 1];
            break;

        case 0x21: 
            //16-bit immediate load into stack pointer
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

        case 0x32: 
            //Put A into mem[HL], Decrement HL
            cycles = 8;
            len = 1;
            memory[concat_bytes(L, H)] = A;
            decrement_HL(); 
            break;

        case 0x3E:
            //Immediate load into A
            cycles = 8;
            len = 2;
            A = memory[PC + 1];
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

        case 0xCB: 
            {
                //Extension OP_CODES
                char x = (memory[PC + 1] & 0xC0) >> 6;
                char y = (memory[PC + 1] & 0x38) >> 3;
                char z = (memory[PC + 1] & 0x07);

                switch(x) {
                    case 00: 
                        //TODO: Rotate
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
            
        case 0xE2: 
            // Load A into mem[0xFF00 + C]
            cycles = 8; 
            len = 1;
            memory[0xFF00 + C] = A;
            break;
    }

    PC += len;
    CLK += cycles; 

    return 0;
}

int main() {

    CPU cpu; 
    cpu.memory.cartridge.load_rom("/users/ejfs1g10/Downloads/Pokemon Red/Pokemon Red.gb");

    cpu.print_state();

    for (int i = 0; i < 6 + 3 * (0x9FFF - 0x8000) + 7; i++) {
        cpu.fetch_and_execute();
        cpu.print_state();
    }

    return 0; 
}
