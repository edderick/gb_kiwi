#include <gtest/gtest.h>
#include "../cpu.h"

TEST(CPU, cpuCanBeCreated) {
    CPU cpu; 
    EXPECT_EQ(0, cpu.PC); 
}

// Page 65
TEST(CPU, 8BitLoads_LoadNIntoReg) {

    //TODO: Refactor into two tests


    CPU cpu; 

    // 0x86 LD B,n
    unsigned char arg1 = 'a'; 
    unsigned char arg2 = '0'; 
    cpu.execute(0x06, arg1, arg2);
    EXPECT_EQ('a', cpu.B);  // Operation successful
    EXPECT_EQ('a', arg1);   // arguments unchanged 
    EXPECT_EQ('0', arg2);

    // 0x0E LD C,n
    arg1 = 'a'; 
    arg2 = '0'; 
    cpu.execute(0x0E, arg1, arg2);
    EXPECT_EQ('a', cpu.C);
    EXPECT_EQ('a', arg1);
    EXPECT_EQ('0', arg2);

    // 0x16 LD D,n
    arg1 = 'a'; 
    arg2 = '0'; 
    cpu.execute(0x16, arg1, arg2);
    EXPECT_EQ('a', cpu.D);
    EXPECT_EQ('a', arg1);
    EXPECT_EQ('0', arg2);

    // 0x1E LD E,n
    arg1 = 'a'; 
    arg2 = '0'; 
    cpu.execute(0x1E, arg1, arg2);
    EXPECT_EQ('a', cpu.E);
    EXPECT_EQ('a', arg1);
    EXPECT_EQ('0', arg2);

    // 0x26 LD H,n
    arg1 = 'a'; 
    arg2 = '0'; 
    cpu.execute(0x26, arg1, arg2);
    EXPECT_EQ('a', cpu.H);
    EXPECT_EQ('a', arg1);
    EXPECT_EQ('0', arg2);

    // 0x2E LD L,n
    arg1 = 'a'; 
    arg2 = '0'; 
    cpu.execute(0x2E, arg1, arg2);
    EXPECT_EQ('a', cpu.L);
    EXPECT_EQ('a', arg1);
    EXPECT_EQ('0', arg2);
}

// Page 66
TEST(CPU, 8BitLoads_LD_regIntoA) {
    CPU cpu; 

    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    // LD A,A
    cpu.A = 'a';
    cpu.execute(0x7F, arg1, arg2);
    EXPECT_EQ('a', cpu.A);

    // LD A,B
    cpu.B = 'b';
    cpu.execute(0x78, arg1, arg2);
    EXPECT_EQ('b', cpu.A);

    // LD A,C
    cpu.C = 'c';
    cpu.execute(0x79, arg1, arg2);
    EXPECT_EQ('c', cpu.A);

    // LD A,D
    cpu.D = 'd';
    cpu.execute(0x7A, arg1, arg2);
    EXPECT_EQ('d', cpu.A);

    // LD A,E
    cpu.E = 'e';
    cpu.execute(0x7B, arg1, arg2);
    EXPECT_EQ('e', cpu.A);

    // LD A,H
    cpu.H = 'h';
    cpu.execute(0x7C, arg1, arg2);
    EXPECT_EQ('h', cpu.A);

    // LD A,L
    cpu.L = 'l';
    cpu.execute(0x7D, arg1, arg2);
    EXPECT_EQ('l', cpu.A);

    //LD A,(HL)
    cpu.memory[0xFFFF] = 'M';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x7E, arg1, arg2);
    EXPECT_EQ('M', cpu.A);
}

// Page 66
TEST(CPU, 8BitLoads_LD_regIntoB) {
    CPU cpu; 

    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    // LD B,B
    cpu.B = 'b';
    cpu.execute(0x40, arg1, arg2);
    EXPECT_EQ('b', cpu.B);

    // LD B,C
    cpu.C = 'c';
    cpu.execute(0x41, arg1, arg2);
    EXPECT_EQ('c', cpu.B);

    // LD B,D
    cpu.D = 'd';
    cpu.execute(0x42, arg1, arg2);
    EXPECT_EQ('d', cpu.B);

    // LD B,E
    cpu.E = 'e';
    cpu.execute(0x43, arg1, arg2);
    EXPECT_EQ('e', cpu.B);

    // LD B,H
    cpu.H = 'h';
    cpu.execute(0x44, arg1, arg2);
    EXPECT_EQ('h', cpu.B);

    // LD B,L
    cpu.L = 'l';
    cpu.execute(0x45, arg1, arg2);
    EXPECT_EQ('l', cpu.B);

    //LD B,(HL)
    cpu.memory[0xFFFF] = 'M';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x46, arg1, arg2);
    EXPECT_EQ('M', cpu.B);
}

// Page 66
TEST(CPU, 8BitLoads_LD_regIntoC) {
    CPU cpu; 

    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    // LD C,B
    cpu.B = 'b';
    cpu.execute(0x48, arg1, arg2);
    EXPECT_EQ('b', cpu.C);

    // LD C,C
    cpu.C = 'c';
    cpu.execute(0x49, arg1, arg2);
    EXPECT_EQ('c', cpu.C);

    // LD C,D
    cpu.D = 'd';
    cpu.execute(0x4A, arg1, arg2);
    EXPECT_EQ('d', cpu.C);

    // LD C,E
    cpu.E = 'e';
    cpu.execute(0x4B, arg1, arg2);
    EXPECT_EQ('e', cpu.C);

    // LD C,H
    cpu.H = 'h';
    cpu.execute(0x4C, arg1, arg2);
    EXPECT_EQ('h', cpu.C);

    // LD C,L
    cpu.L = 'l';
    cpu.execute(0x4D, arg1, arg2);
    EXPECT_EQ('l', cpu.C);

    //LD C,(HL)
    cpu.memory[0xFFFF] = 'M';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x4E, arg1, arg2);
    EXPECT_EQ('M', cpu.C);
}

// Page 66
TEST(CPU, 8BitLoads_LD_regIntoD) {
    CPU cpu; 

    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    // LD D,B
    cpu.B = 'b';
    cpu.execute(0x50, arg1, arg2);
    EXPECT_EQ('b', cpu.D);

    // LD D,C
    cpu.C = 'c';
    cpu.execute(0x51, arg1, arg2);
    EXPECT_EQ('c', cpu.D);

    // LD D,D
    cpu.D = 'd';
    cpu.execute(0x52, arg1, arg2);
    EXPECT_EQ('d', cpu.D);

    // LD D,E
    cpu.E = 'e';
    cpu.execute(0x53, arg1, arg2);
    EXPECT_EQ('e', cpu.D);

    // LD D,H
    cpu.H = 'h';
    cpu.execute(0x54, arg1, arg2);
    EXPECT_EQ('h', cpu.D);

    // LD D,L
    cpu.L = 'l';
    cpu.execute(0x55, arg1, arg2);
    EXPECT_EQ('l', cpu.D);

    //LD D,(HL)
    cpu.memory[0xFFFF] = 'M';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x56, arg1, arg2);
    EXPECT_EQ('M', cpu.D);
}

// Page 66
TEST(CPU, 8BitLoads_LD_regIntoE) {
    CPU cpu; 

    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    //  LD E,B
    cpu.B = 'b';
    cpu.execute(0x58, arg1, arg2);
    EXPECT_EQ('b', cpu.E);

    //  LD E,C
    cpu.C = 'c';
    cpu.execute(0x59, arg1, arg2);
    EXPECT_EQ('c', cpu.E);

    //  LD E,D
    cpu.D = 'd';
    cpu.execute(0x5A, arg1, arg2);
    EXPECT_EQ('d', cpu.E);

    //  LD E,E
    cpu.E = 'e';
    cpu.execute(0x5B, arg1, arg2);
    EXPECT_EQ('e', cpu.E);

    //  LD E,H
    cpu.H = 'h';
    cpu.execute(0x5C, arg1, arg2);
    EXPECT_EQ('h', cpu.E);

    //  LD E,L
    cpu.L = 'l';
    cpu.execute(0x5D, arg1, arg2);
    EXPECT_EQ('l', cpu.E);

    // LD E,(HL)
    cpu.memory[0xFFFF] = 'M';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x5E, arg1, arg2);
    EXPECT_EQ('M', cpu.E);
}

// Page 66
TEST(CPU, 8BitLoads_LD_regIntoH) {
    CPU cpu; 

    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    //  LD H,B
    cpu.B = 'b';
    cpu.execute(0x60, arg1, arg2);
    EXPECT_EQ('b', cpu.H);

    //  LD H,C
    cpu.C = 'c';
    cpu.execute(0x61, arg1, arg2);
    EXPECT_EQ('c', cpu.H);

    //  LD H,D
    cpu.D = 'd';
    cpu.execute(0x62, arg1, arg2);
    EXPECT_EQ('d', cpu.H);

    //  LD H,E
    cpu.E = 'e';
    cpu.execute(0x63, arg1, arg2);
    EXPECT_EQ('e', cpu.H);

    //  LD H,H
    cpu.H = 'h';
    cpu.execute(0x64, arg1, arg2);
    EXPECT_EQ('h', cpu.H);

    //  LD H,L
    cpu.L = 'l';
    cpu.execute(0x65, arg1, arg2);
    EXPECT_EQ('l', cpu.H);

    // LD H,(HL)
    cpu.memory[0xFFFF] = 'M';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x66, arg1, arg2);
    EXPECT_EQ('M', cpu.H);
}
  
// Page 66
TEST(CPU, 8BitLoads_LD_regIntoL) {
    CPU cpu; 

    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    //  LD L,B
    cpu.B = 'b';
    cpu.execute(0x68, arg1, arg2);
    EXPECT_EQ('b', cpu.L);

    //  LD L,C
    cpu.C = 'c';
    cpu.execute(0x69, arg1, arg2);
    EXPECT_EQ('c', cpu.L);

    //  LD L,D
    cpu.D = 'd';
    cpu.execute(0x6A, arg1, arg2);
    EXPECT_EQ('d', cpu.L);

    //  LD L,E
    cpu.E = 'e';
    cpu.execute(0x6B, arg1, arg2);
    EXPECT_EQ('e', cpu.L);

    //  LD L,H
    cpu.H = 'h';
    cpu.execute(0x6C, arg1, arg2);
    EXPECT_EQ('h', cpu.L);

    //  LD L,L
    cpu.L = 'l';
    cpu.execute(0x6D, arg1, arg2);
    EXPECT_EQ('l', cpu.L);

    // LD L,(HL)
    cpu.memory[0xFFFF] = 'M';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x6E, arg1, arg2);
    EXPECT_EQ('M', cpu.L);
}

TEST(CPU, 8BitLoads_LD_regInto_HL) {
    CPU cpu; 

    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    // LD (HL),B
    cpu.memory[0xFFFF] = '0';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.B = 'b';
    cpu.execute(0x70, arg1, arg2);
    EXPECT_EQ('b', cpu.memory[0xFFFF]);

    // LD (HL),C
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.C = 'c';
    cpu.execute(0x71, arg1, arg2);
    EXPECT_EQ('c', cpu.memory[0xFFFF]);

    // LD (HL),D
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.D = 'd';
    cpu.execute(0x72, arg1, arg2);
    EXPECT_EQ('d', cpu.memory[0xFFFF]);

    // LD (HL),E
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.E = 'e';
    cpu.execute(0x73, arg1, arg2);
    EXPECT_EQ('e', cpu.memory[0xFFFF]);

    // LD (HL),H
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x74, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.memory[0xFFFF]);

    // LD (HL),L
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x75, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.memory[0xFFFF]);

    // LD (HL),n
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    arg1 = 'n'; 
    cpu.execute(0x36, arg1, arg2);
    EXPECT_EQ('n', cpu.memory[0xFFFF]);
}

//TODO : rest of page 66

