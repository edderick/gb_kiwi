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

    // LD A,B
    cpu.B = 'b';
    cpu.execute(0x40, arg1, arg2);
    EXPECT_EQ('b', cpu.B);

    // LD A,C
    cpu.C = 'c';
    cpu.execute(0x41, arg1, arg2);
    EXPECT_EQ('c', cpu.B);

    // LD A,D
    cpu.D = 'd';
    cpu.execute(0x42, arg1, arg2);
    EXPECT_EQ('d', cpu.B);

    // LD A,E
    cpu.E = 'e';
    cpu.execute(0x43, arg1, arg2);
    EXPECT_EQ('e', cpu.B);

    // LD A,H
    cpu.H = 'h';
    cpu.execute(0x44, arg1, arg2);
    EXPECT_EQ('h', cpu.B);

    // LD A,L
    cpu.L = 'l';
    cpu.execute(0x45, arg1, arg2);
    EXPECT_EQ('l', cpu.B);

    //LD A,(HL)
    cpu.memory[0xFFFF] = 'M';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x46, arg1, arg2);
    EXPECT_EQ('M', cpu.B);
}

//TODO : rest of page 66
