#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../cpu.h"
#include "mock_graphics.h"

using namespace gbemu;

class TestCpu : public ::testing::Test {
    protected:
        Cartridge cartridge;
        MockGraphics mockGraphics;
        CPU cpu;

        TestCpu()
        : cpu(&cartridge, &mockGraphics)
        {
        }
};

//TODO: Check program counter
//TODO: For SBC and ADC, we should probably check 7 Carry/Borrow
//TODO: For SBC and ADC, we should probably check Both Carry/Borrow
//TODO: For SBD and ADC. we might want to check Carry to Zero

TEST_F(TestCpu, cpuCanBeCreated) {
    EXPECT_EQ(0, cpu.PC); 
}

// Page 65
TEST_F(TestCpu, 8BitLoads_LoadNIntoReg) {
    //TODO: Refactor into two tests
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
TEST_F(TestCpu, 8BitLoads_LD_regIntoA) {

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
    cpu.memory()[0xFFFF] = 'M';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x7E, arg1, arg2);
    EXPECT_EQ('M', cpu.A);
}

// Page 66
TEST_F(TestCpu, 8BitLoads_LD_regIntoB) {
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
    cpu.memory()[0xFFFF] = 'M';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x46, arg1, arg2);
    EXPECT_EQ('M', cpu.B);
}

// Page 66
TEST_F(TestCpu, 8BitLoads_LD_regIntoC) {
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
    cpu.memory()[0xFFFF] = 'M';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x4E, arg1, arg2);
    EXPECT_EQ('M', cpu.C);
}

// Page 67
TEST_F(TestCpu, 8BitLoads_LD_regIntoD) {
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
    cpu.memory()[0xFFFF] = 'M';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x56, arg1, arg2);
    EXPECT_EQ('M', cpu.D);
}

// Page 67
TEST_F(TestCpu, 8BitLoads_LD_regIntoE) {
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
    cpu.memory()[0xFFFF] = 'M';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x5E, arg1, arg2);
    EXPECT_EQ('M', cpu.E);
}

// Page 67
TEST_F(TestCpu, 8BitLoads_LD_regIntoH) {
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
    cpu.memory()[0xFFFF] = 'M';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x66, arg1, arg2);
    EXPECT_EQ('M', cpu.H);
}
  
// Page 67
TEST_F(TestCpu, 8BitLoads_LD_regIntoL) {
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
    cpu.memory()[0xFFFF] = 'M';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x6E, arg1, arg2);
    EXPECT_EQ('M', cpu.L);
}

// Page 67
TEST_F(TestCpu, 8BitLoads_LD_regInto_HL) {
    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    // LD (HL),B
    cpu.memory()[0xFFFF] = '0';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.B = 'b';
    cpu.execute(0x70, arg1, arg2);
    EXPECT_EQ('b', cpu.memory()[0xFFFF]);

    // LD (HL),C
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.C = 'c';
    cpu.execute(0x71, arg1, arg2);
    EXPECT_EQ('c', cpu.memory()[0xFFFF]);

    // LD (HL),D
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.D = 'd';
    cpu.execute(0x72, arg1, arg2);
    EXPECT_EQ('d', cpu.memory()[0xFFFF]);

    // LD (HL),E
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.E = 'e';
    cpu.execute(0x73, arg1, arg2);
    EXPECT_EQ('e', cpu.memory()[0xFFFF]);

    // LD (HL),H
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x74, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.memory()[0xFFFF]);

    // LD (HL),L
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x75, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.memory()[0xFFFF]);

    // LD (HL),n
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    arg1 = 'n'; 
    cpu.execute(0x36, arg1, arg2);
    EXPECT_EQ('n', cpu.memory()[0xFFFF]);
}

//Page 68
TEST_F(TestCpu, 8BitLoads_LD_IntoA) {
    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    //  LD A,A
    cpu.A = 'a';
    cpu.execute(0x7F, arg1, arg2);
    EXPECT_EQ('a', cpu.A);

    //  LD A,B
    cpu.B = 'b';
    cpu.execute(0x78, arg1, arg2);
    EXPECT_EQ('b', cpu.A);

    //  LD A,C
    cpu.C = 'c';
    cpu.execute(0x79, arg1, arg2);
    EXPECT_EQ('c', cpu.A);

    //  LD A,D
    cpu.D = 'd';
    cpu.execute(0x7A, arg1, arg2);
    EXPECT_EQ('d', cpu.A);
    
    //  LD A,E
    cpu.E = 'e';
    cpu.execute(0x7B, arg1, arg2);
    EXPECT_EQ('e', cpu.A);

    //  LD A,H
    cpu.H = 'h';
    cpu.execute(0x7C, arg1, arg2);
    EXPECT_EQ('h', cpu.A);

    //  LD A,L
    cpu.L = 'l';
    cpu.execute(0x7D, arg1, arg2);
    EXPECT_EQ('l', cpu.A);

    // LD A,(BC)
    cpu.memory()[0xFF01] = 'B';
    cpu.B = 0xFF;
    cpu.C = 0x01;
    cpu.execute(0x0A, arg1, arg2);
    EXPECT_EQ('B', cpu.A);

    // LD A,(DE)
    cpu.memory()[0xFF02] = 'D';
    cpu.D = 0xFF;
    cpu.E = 0x02;
    cpu.execute(0x1A, arg1, arg2);
    EXPECT_EQ('D', cpu.A);

    // LD A,(HL)
    cpu.memory()[0xFF03] = 'H';
    cpu.H = 0xFF;
    cpu.L = 0x03;
    cpu.execute(0x7E, arg1, arg2);
    EXPECT_EQ('H', cpu.A);

    // LD A,(nn)
    cpu.memory()[0xFF04] = 'N';
    arg1 = 0x04; 
    arg2 = 0xFF; 
    cpu.execute(0xFA, arg1, arg2);
    EXPECT_EQ('N', cpu.A);

   // LD A,n
    arg1 = 'n'; 
    cpu.execute(0x3E, arg1, arg2);
    EXPECT_EQ('n', cpu.A);
}

// Page 69
TEST_F(TestCpu, 8BitLoads_LD_AIntoReg) {
    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    //  LD A,A
    cpu.A = 'a';
    cpu.execute(0x7F, arg1, arg2);
    EXPECT_EQ('a', cpu.A);
    
    //  LD B,A
    cpu.A = 'a';
    cpu.B = 'b';
    cpu.execute(0x47, arg1, arg2);
    EXPECT_EQ('a', cpu.B);

    //  LD C,A
    cpu.A = 'a';
    cpu.C = 'c';
    cpu.execute(0x4F, arg1, arg2);
    EXPECT_EQ('a', cpu.C);

    //  LD D,A
    cpu.A = 'a';
    cpu.D = 'd';
    cpu.execute(0x57, arg1, arg2);
    EXPECT_EQ('a', cpu.D);

    //  LD E,A
    cpu.A = 'a';
    cpu.E = 'e';
    cpu.execute(0x5F, arg1, arg2);
    EXPECT_EQ('a', cpu.E);

    //  LD H,A
    cpu.A = 'a';
    cpu.H = 'h';
    cpu.execute(0x67, arg1, arg2);
    EXPECT_EQ('a', cpu.H);

    //  LD L,A
    cpu.A = 'a';
    cpu.L = 'l';
    cpu.execute(0x6F, arg1, arg2);
    EXPECT_EQ('a', cpu.L);

    // LD (BC),A
    cpu.A = 'a';
    cpu.B = 0xFF;
    cpu.C = 0x11;
    cpu.execute(0x02, arg1, arg2);
    EXPECT_EQ('a', cpu.memory()[0xFF11]);

    // LD (DE),A
    cpu.A = 'a';
    cpu.D = 0xFF;
    cpu.E = 0x12;
    cpu.execute(0x12, arg1, arg2);
    EXPECT_EQ('a', cpu.memory()[0xFF12]);

    // LD (HL),A
    cpu.A = 'a';
    cpu.H = 0xFF;
    cpu.L = 0x13;
    cpu.execute(0x77, arg1, arg2);
    EXPECT_EQ('a', cpu.memory()[0xFF13]);

    // LD (nn),A
    cpu.A = 'a';
    arg1 = 0x14;
    arg2 = 0xFF;
    cpu.execute(0xEA, arg1, arg2);
    EXPECT_EQ('a', cpu.memory()[0xFF14]);
}

// Page 70
TEST_F(TestCpu, 8BitLoads_LD_FFCIntoA) {
    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    // LD A,(0xFF00+C)
    cpu.memory()[0xFFFA] = 'c';
    cpu.A = 'a';
    cpu.C = 0xFA;
    cpu.execute(0xF2, arg1, arg2);
    EXPECT_EQ('c', cpu.A);
}

// Page 70
TEST_F(TestCpu, 8BitLoads_LD_AIntoFFC) {
    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    // LD (0xFF00+C),A
    cpu.A = 'a';
    cpu.C = 0xFB;
    cpu.execute(0xE2, arg1, arg2);
    EXPECT_EQ('a', cpu.memory()[0xFFFB]);
}

// Page 71
TEST_F(TestCpu, 8BitLoads_LDD_AIntoHL) {
    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    // LD A,(HL--) Normal case 
    cpu.memory()[0xFFFF] = 'H';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x3A, arg1, arg2);
    EXPECT_EQ('H', cpu.A);
    EXPECT_EQ(0xFF, cpu.H); // Decrementing has worked
    EXPECT_EQ(0xFE, cpu.L); // Decrementing has worked

    // LD A,(HL--) Byte boundary
    cpu.memory()[0xFF00] = 'H';
    cpu.H = 0xFF;
    cpu.L = 0x00;
    cpu.execute(0x3A, arg1, arg2);
    EXPECT_EQ('H', cpu.A);
    EXPECT_EQ(0xFE, cpu.H); // Decrementing has worked
    EXPECT_EQ(0xFF, cpu.L); // Decrementing has worked

    // LD A,(HL--) Low case
    cpu.memory()[0x0000] = 'H';
    cpu.H = 0x00;
    cpu.L = 0x00;
    cpu.execute(0x3A, arg1, arg2);
    EXPECT_EQ('H', cpu.A);
    EXPECT_EQ(0xFF, cpu.H); // Decrementing has worked
    EXPECT_EQ(0xFF, cpu.L); // Decrementing has worked
}

// Page 72
TEST_F(TestCpu, 8BitLoads_LDD_HLIntoA) {
    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    // LD A,(HL--) Normal case 
    cpu.A = 'A';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x32, arg1, arg2);
    EXPECT_EQ('A', cpu.memory()[0xFFFF]);
    EXPECT_EQ(0xFF, cpu.H); // Decrementing has worked
    EXPECT_EQ(0xFE, cpu.L); // Decrementing has worked

    // LD A,(HL--) Byte boundary
    cpu.A = 'A';
    cpu.H = 0xFF;
    cpu.L = 0x00;
    cpu.execute(0x32, arg1, arg2);
    EXPECT_EQ('A', cpu.memory()[0xFF00]);
    EXPECT_EQ(0xFE, cpu.H); // Decrementing has worked
    EXPECT_EQ(0xFF, cpu.L); // Decrementing has worked

    // LD A,(HL--) Low case
    cpu.A = 'A';
    cpu.H = 0x00;
    cpu.L = 0x00;
    cpu.execute(0x32, arg1, arg2);
    EXPECT_EQ('A', cpu.memory()[0x0000]);
    EXPECT_EQ(0xFF, cpu.H); // Decrementing has worked
    EXPECT_EQ(0xFF, cpu.L); // Decrementing has worked
}


// Page 73
TEST_F(TestCpu, 8BitLoads_LDI_AIntoHL) {
    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    // LD A,(HL++) Normal case 
    cpu.memory()[0xFFF0] = 'H';
    cpu.H = 0xFF;
    cpu.L = 0xF0;
    cpu.execute(0x2A, arg1, arg2);
    EXPECT_EQ('H', cpu.A);
    EXPECT_EQ(0xFF, cpu.H); // Decrementing has worked
    EXPECT_EQ(0xF1, cpu.L); // Decrementing has worked

    // LD A,(HL++) Byte boundary
    cpu.memory()[0xF0FF] = 'H';
    cpu.H = 0xF0;
    cpu.L = 0xFF;
    cpu.execute(0x2A, arg1, arg2);
    EXPECT_EQ('H', cpu.A);
    EXPECT_EQ(0xF1, cpu.H); // Decrementing has worked
    EXPECT_EQ(0x00, cpu.L); // Decrementing has worked

    // LD A,(HL++) High case
    cpu.memory()[0xFFFF] = 'H';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x2A, arg1, arg2);
    EXPECT_EQ('H', cpu.A);
    EXPECT_EQ(0x00, cpu.H); // Decrementing has worked
    EXPECT_EQ(0x00, cpu.L); // Decrementing has worked
}

// Page 74
TEST_F(TestCpu, 8BitLoads_LDI_HLIntoA) {
    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    // LD A,(HL++) Normal case 
    cpu.A = 'A';
    cpu.H = 0x00;
    cpu.L = 0x00;
    cpu.execute(0x22, arg1, arg2);
    EXPECT_EQ('A', cpu.memory()[0x0000]);
    EXPECT_EQ(0x00, cpu.H); // Decrementing has worked
    EXPECT_EQ(0x01, cpu.L); // Decrementing has worked

    // LD A,(HL++) Byte boundary
    cpu.A = 'A';
    cpu.H = 0xFE;
    cpu.L = 0xFF;
    cpu.execute(0x22, arg1, arg2);
    EXPECT_EQ('A', cpu.memory()[0xFEFF]);
    EXPECT_EQ(0xFF, cpu.H); // Decrementing has worked
    EXPECT_EQ(0x00, cpu.L); // Decrementing has worked

    // LD A,(HL++) High case
    cpu.A = 'A';
    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x22, arg1, arg2);
    EXPECT_EQ('A', cpu.memory()[0x0000]);
    EXPECT_EQ(0x00, cpu.H); // Decrementing has worked
    EXPECT_EQ(0x00, cpu.L); // Decrementing has worked
}

// Page 75
TEST_F(TestCpu, 8BitLoads_LD_FFnnIntoA) {
    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    // LD A,(0xFF00+C)
    cpu.memory()[0xFFFA] = 'c';
    cpu.A = 'a';
    arg1 = 0xFA;
    cpu.execute(0xF0, arg1, arg2);
    EXPECT_EQ('c', cpu.A);
}

// Page 75
TEST_F(TestCpu, 8BitLoads_LD_AIntoFFnn) {
    unsigned char arg1 = '0'; 
    unsigned char arg2 = '0'; 

    // LD (0xFF00+C),A
    cpu.A = 'a';
    arg1 = 0xFB;
    cpu.execute(0xE0, arg1, arg2);
    EXPECT_EQ('a', cpu.memory()[0xFFFB]);
}

// Page 76 
TEST_F(TestCpu, 16BitLoads_LD_nnInton) {
    unsigned char arg1 = '1';
    unsigned char arg2 = '2';

    //LD BC,nn 
    arg1 = '1';
    arg2 = '2';
    cpu.B = 'B';
    cpu.C = 'C';
    cpu.execute(0x01, arg1, arg2);
    EXPECT_EQ('2', cpu.B);
    EXPECT_EQ('1', cpu.C);

    //LD DE,nn 
    arg1 = '1';
    arg2 = '2';
    cpu.D = 'D';
    cpu.E = 'E';
    cpu.execute(0x11, arg1, arg2);
    EXPECT_EQ('2', cpu.D);
    EXPECT_EQ('1', cpu.E);

    //LD HL,nn 
    arg1 = '1';
    arg2 = '2';
    cpu.H = 'H';
    cpu.L = 'L';
    cpu.execute(0x21, arg1, arg2);
    EXPECT_EQ('2', cpu.H);
    EXPECT_EQ('1', cpu.L);

    //LD SP,nn 
    arg1 = 0x11;
    arg2 = 0x22;
    cpu.SP = 0xFF;
    cpu.execute(0x31, arg1, arg2);
    EXPECT_EQ(0x2211, cpu.SP);
}

//Page 76
TEST_F(TestCpu, 16BitLoads_LD_HLintoSP) {
    unsigned char arg1 = '0';
    unsigned char arg2 = '0';

    cpu.H = 0x66;
    cpu.L = 0x55;
    cpu.SP = 0x00; 
    cpu.execute(0xF9, arg1, arg2);
    EXPECT_EQ(0x6655, cpu.SP);
}

//Page 77
TEST_F(TestCpu, 16BitLoads_LDHL_SPn) {
    unsigned char arg1;
    unsigned char arg2;

    arg1 = 0x01; 
    arg2 = 0x00;
    cpu.SP = 0x1111; 
    cpu.execute(0xF8, arg1, arg2); 
    EXPECT_EQ(0x11, cpu.H);
    EXPECT_EQ(0x12, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);


    arg1 = 0x04; 
    arg2 = 0x00;
    cpu.SP = 0x11FF; 
    cpu.execute(0xF8, arg1, arg2); 
    EXPECT_EQ(0x12, cpu.H);
    EXPECT_EQ(0x03, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);


    arg1 = 0xFF; 
    arg2 = 0x00;
    cpu.SP = 0xFFFF; 
    cpu.execute(0xF8, arg1, arg2); 
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0xFE, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

//Page 78
TEST_F(TestCpu, 16BitLoads_LD_nnSP) {
    unsigned char arg1 = 0x00;
    unsigned char arg2 = 0xfc;
    cpu.SP = 0x1234; 
    cpu.execute(0x08, arg1, arg2); 
    EXPECT_EQ(0x34, cpu.memory()[0xFC00]);
    EXPECT_EQ(0x12, cpu.memory()[0xFC01]);
}

//Page 78 
TEST_F(TestCpu, PUSH_nn) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.SP = 0xFF88;
    cpu.A = 0x11;
    cpu.F = 0x22; 
    cpu.execute(0xF5, arg1, arg2); 
    EXPECT_EQ(0x11, cpu.memory()[0xFF87]);
    EXPECT_EQ(0x22, cpu.memory()[0xFF86]);
    EXPECT_EQ(0xFF86, cpu.SP);

    cpu.SP = 0xFF92;
    cpu.B = 0x33;
    cpu.C = 0x44; 
    cpu.execute(0xC5, arg1, arg2); 
    EXPECT_EQ(0x33, cpu.memory()[0xFF91]);
    EXPECT_EQ(0x44, cpu.memory()[0xFF90]);
    EXPECT_EQ(0xFF90, cpu.SP);

    cpu.SP = 0xFF96;
    cpu.D = 0x55;
    cpu.E = 0x66; 
    cpu.execute(0xD5, arg1, arg2); 
    EXPECT_EQ(0x55, cpu.memory()[0xFF95]);
    EXPECT_EQ(0x66, cpu.memory()[0xFF94]);
    EXPECT_EQ(0xFF94, cpu.SP);

    cpu.SP = 0xFF98;
    cpu.H = 0x77;
    cpu.L = 0x88; 
    cpu.execute(0xE5, arg1, arg2); 
    EXPECT_EQ(0x77, cpu.memory()[0xFF97]);
    EXPECT_EQ(0x88, cpu.memory()[0xFF96]);
    EXPECT_EQ(0xFF96, cpu.SP);
}

//Page 79
TEST_F(TestCpu, POP_nn) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.SP = 0xFF86;
    cpu.memory()[0xFF86] = 0x11;
    cpu.memory()[0xFF87] = 0x22;
    cpu.execute(0xF1, arg1, arg2); 
    EXPECT_EQ(0x11, cpu.F); 
    EXPECT_EQ(0x22, cpu.A);
    EXPECT_EQ(0xFF88, cpu.SP);

    cpu.SP = 0xFF84;
    cpu.memory()[0xFF84] = 0x33;
    cpu.memory()[0xFF85] = 0x44;
    cpu.execute(0xC1, arg1, arg2); 
    EXPECT_EQ(0x33, cpu.C); 
    EXPECT_EQ(0x44, cpu.B);
    EXPECT_EQ(0xFF86, cpu.SP);

    cpu.SP = 0xFF82;
    cpu.memory()[0xFF82] = 0x55;
    cpu.memory()[0xFF83] = 0x66;
    cpu.execute(0xD1, arg1, arg2); 
    EXPECT_EQ(0x55, cpu.E); 
    EXPECT_EQ(0x66, cpu.D);
    EXPECT_EQ(0xFF84, cpu.SP);

    cpu.SP = 0xFF80;
    cpu.memory()[0xFF80] = 0x77;
    cpu.memory()[0xFF81] = 0x88;
    cpu.execute(0xE1, arg1, arg2); 
    EXPECT_EQ(0x77, cpu.L); 
    EXPECT_EQ(0x88, cpu.H);
    EXPECT_EQ(0xFF82, cpu.SP);
}

// Page 80
TEST_F(TestCpu, ADD_An_NoCarry) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x01;
    cpu.execute(0x87, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.B = 0x02;
    cpu.execute(0x80, arg1, arg2);
    EXPECT_EQ(0x03, cpu.A);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.C = 0x03;
    cpu.execute(0x81, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);
    EXPECT_EQ(0x03, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.D = 0x04;
    cpu.execute(0x82, arg1, arg2);
    EXPECT_EQ(0x05, cpu.A);
    EXPECT_EQ(0x04, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.E = 0x05;
    cpu.execute(0x83, arg1, arg2);
    EXPECT_EQ(0x06, cpu.A);
    EXPECT_EQ(0x05, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x02;
    cpu.H = 0x02;
    cpu.execute(0x84, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);
    EXPECT_EQ(0x02, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x03;
    cpu.L = 0x02;
    cpu.execute(0x85, arg1, arg2);
    EXPECT_EQ(0x05, cpu.A);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x02;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x05;
    cpu.execute(0x86, arg1, arg2);
    EXPECT_EQ(0x07, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x05, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x04;
    arg1 = 0x04;
    cpu.execute(0xC6, arg1, arg2);
    EXPECT_EQ(0x08, cpu.A);
    EXPECT_EQ(0x04, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 80
TEST_F(TestCpu, ADD_An_Zero) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x00;
    cpu.execute(0x87, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.B = 0x00;
    cpu.execute(0x80, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.C = 0x00;
    cpu.execute(0x81, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.D = 0x00;
    cpu.execute(0x82, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.E = 0x00;
    cpu.execute(0x83, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.H = 0x00;
    cpu.execute(0x84, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.L = 0x00;
    cpu.execute(0x85, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.H = 0x00;
    cpu.L = 0x02;
    cpu.memory()[0x0002] = 0x00;
    cpu.execute(0x86, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(0x00, cpu.memory()[0x0002]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    arg1 = 0x00;
    cpu.execute(0xC6, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, arg1);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    // Carry to Zero
    cpu.A = 0x10;
    arg1 = 0xF0;
    cpu.execute(0xC6, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0xF0, arg1);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 80
TEST_F(TestCpu, ADD_An_3Carry) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x0A;
    cpu.execute(0x87, arg1, arg2);
    EXPECT_EQ(0x0A + 0xA, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x0A;
    cpu.B = 0x0B;
    cpu.execute(0x80, arg1, arg2);
    EXPECT_EQ(0x0A + 0x0B, cpu.A);
    EXPECT_EQ(0x0B, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.C = 0x0F;
    cpu.execute(0x81, arg1, arg2);
    EXPECT_EQ(0x01 + 0x0F, cpu.A);
    EXPECT_EQ(0x0F, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x0F;
    cpu.D = 0x01;
    cpu.execute(0x82, arg1, arg2);
    EXPECT_EQ(0x0F + 0x01, cpu.A);
    EXPECT_EQ(0x01, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x03;
    cpu.E = 0x0E;
    cpu.execute(0x83, arg1, arg2);
    EXPECT_EQ(0x03 + 0x0E, cpu.A);
    EXPECT_EQ(0x0E, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x07;
    cpu.H = 0x0C;
    cpu.execute(0x84, arg1, arg2);
    EXPECT_EQ(0x07 + 0x0C, cpu.A);
    EXPECT_EQ(0x0C, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x0F;
    cpu.L = 0x0A;
    cpu.execute(0x85, arg1, arg2);
    EXPECT_EQ(0x0F + 0x0A, cpu.A);
    EXPECT_EQ(0x0A, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x0A;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x0A;
    cpu.execute(0x86, arg1, arg2);
    EXPECT_EQ(0x0A + 0x0A, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x0A, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x0B;
    arg1 = 0x0B;
    cpu.execute(0xC6, arg1, arg2);
    EXPECT_EQ(0x0B + 0x0B, cpu.A);
    EXPECT_EQ(0x0B, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 80
TEST_F(TestCpu, ADD_An_7Carry) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0xA0;
    cpu.execute(0x87, arg1, arg2);
    EXPECT_EQ(0x40, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0xA0;
    cpu.B = 0xB0;
    cpu.execute(0x80, arg1, arg2);
    EXPECT_EQ(0x50, cpu.A);
    EXPECT_EQ(0xB0, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x20;
    cpu.C = 0xF0;
    cpu.execute(0x81, arg1, arg2);
    EXPECT_EQ(0x10, cpu.A);
    EXPECT_EQ(0xF0, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0xF0;
    cpu.D = 0x20;
    cpu.execute(0x82, arg1, arg2);
    EXPECT_EQ(0x10, cpu.A);
    EXPECT_EQ(0x20, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x30;
    cpu.E = 0xE0;
    cpu.execute(0x83, arg1, arg2);
    EXPECT_EQ(0x10, cpu.A);
    EXPECT_EQ(0xE0, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x70;
    cpu.H = 0xC0;
    cpu.execute(0x84, arg1, arg2);
    EXPECT_EQ(0x30, cpu.A);
    EXPECT_EQ(0xC0, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0xF0;
    cpu.L = 0xA0;
    cpu.execute(0x85, arg1, arg2);
    EXPECT_EQ(0x90, cpu.A);
    EXPECT_EQ(0xA0, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0xA0;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0xA0;
    cpu.execute(0x86, arg1, arg2);
    EXPECT_EQ(0x40, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0xA0, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0xB0;
    arg1 = 0xB0;
    cpu.execute(0xC6, arg1, arg2);
    EXPECT_EQ(0x60, cpu.A);
    EXPECT_EQ(0xB0, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 80
TEST_F(TestCpu, ADD_An_BothCarry) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0xAA;
    cpu.execute(0x87, arg1, arg2);
    EXPECT_EQ(0x54, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0xAA;
    cpu.B = 0xBB;
    cpu.execute(0x80, arg1, arg2);
    EXPECT_EQ(0x65, cpu.A);
    EXPECT_EQ(0xBB, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x02;
    cpu.C = 0xFF;
    cpu.execute(0x81, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(0xFF, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0xFF;
    cpu.D = 0x22;
    cpu.execute(0x82, arg1, arg2);
    EXPECT_EQ(0x21, cpu.A);
    EXPECT_EQ(0x22, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x33;
    cpu.E = 0xEE;
    cpu.execute(0x83, arg1, arg2);
    EXPECT_EQ(0x21, cpu.A);
    EXPECT_EQ(0xEE, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x77;
    cpu.H = 0xCC;
    cpu.execute(0x84, arg1, arg2);
    EXPECT_EQ(0x43, cpu.A);
    EXPECT_EQ(0xCC, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0xFF;
    cpu.L = 0xAA;
    cpu.execute(0x85, arg1, arg2);
    EXPECT_EQ(0xA9, cpu.A);
    EXPECT_EQ(0xAA, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0xAA;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0xAA;
    cpu.execute(0x86, arg1, arg2);
    EXPECT_EQ(0x54, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0xAA, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0xBB;
    arg1 = 0xBB;
    cpu.execute(0xC6, arg1, arg2);
    EXPECT_EQ(0x76, cpu.A);
    EXPECT_EQ(0xBB, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 81
TEST_F(TestCpu, ADC_An_NoCarryIn_NoCarryOut) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x01;
    cpu.flag.C = false;
    cpu.execute(0x8F, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.B = 0x02;
    cpu.flag.C = false;
    cpu.execute(0x88, arg1, arg2);
    EXPECT_EQ(0x03, cpu.A);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.C = 0x03;
    cpu.flag.C = false;
    cpu.execute(0x89, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);
    EXPECT_EQ(0x03, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.D = 0x04;
    cpu.flag.C = false;
    cpu.execute(0x8A, arg1, arg2);
    EXPECT_EQ(0x05, cpu.A);
    EXPECT_EQ(0x04, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.E = 0x05;
    cpu.flag.C = false;
    cpu.execute(0x8B, arg1, arg2);
    EXPECT_EQ(0x06, cpu.A);
    EXPECT_EQ(0x05, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x02;
    cpu.H = 0x02;
    cpu.flag.C = false;
    cpu.execute(0x8C, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);
    EXPECT_EQ(0x02, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x03;
    cpu.L = 0x02;
    cpu.flag.C = false;
    cpu.execute(0x8D, arg1, arg2);
    EXPECT_EQ(0x05, cpu.A);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x02;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.flag.C = false;
    cpu.memory()[0x0001] = 0x05;
    cpu.execute(0x8E, arg1, arg2);
    EXPECT_EQ(0x07, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x05, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x04;
    arg1 = 0x04;
    cpu.flag.C = false;
    cpu.execute(0xCE, arg1, arg2);
    EXPECT_EQ(0x08, cpu.A);
    EXPECT_EQ(0x04, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 81
TEST_F(TestCpu, ADC_An_CarryIn_NoCarryOut) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x01;
    cpu.flag.C = true;
    cpu.execute(0x8F, arg1, arg2);
    EXPECT_EQ(0x03, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.B = 0x02;
    cpu.flag.C = true;
    cpu.execute(0x88, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.C = 0x03;
    cpu.flag.C = true;
    cpu.execute(0x89, arg1, arg2);
    EXPECT_EQ(0x05, cpu.A);
    EXPECT_EQ(0x03, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.D = 0x04;
    cpu.flag.C = true;
    cpu.execute(0x8A, arg1, arg2);
    EXPECT_EQ(0x06, cpu.A);
    EXPECT_EQ(0x04, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.E = 0x05;
    cpu.flag.C = true;
    cpu.execute(0x8B, arg1, arg2);
    EXPECT_EQ(0x07, cpu.A);
    EXPECT_EQ(0x05, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x02;
    cpu.H = 0x02;
    cpu.flag.C = true;
    cpu.execute(0x8C, arg1, arg2);
    EXPECT_EQ(0x05, cpu.A);
    EXPECT_EQ(0x02, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x03;
    cpu.L = 0x02;
    cpu.flag.C = true;
    cpu.execute(0x8D, arg1, arg2);
    EXPECT_EQ(0x06, cpu.A);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x02;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.flag.C = true;
    cpu.memory()[0x0001] = 0x05;
    cpu.execute(0x8E, arg1, arg2);
    EXPECT_EQ(0x08, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x05, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x04;
    arg1 = 0x04;
    cpu.flag.C = true;
    cpu.execute(0xCE, arg1, arg2);
    EXPECT_EQ(0x09, cpu.A);
    EXPECT_EQ(0x04, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 81
TEST_F(TestCpu, ADC_An_CarryIn_3Carry) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x0A;
    cpu.flag.C = true;
    cpu.execute(0x8F, arg1, arg2);
    EXPECT_EQ(0x0A + 0x0A + 0x01, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x0A;
    cpu.B = 0x0B;
    cpu.flag.C = true;
    cpu.execute(0x88, arg1, arg2);
    EXPECT_EQ(0x0A + 0x0B + 0x01, cpu.A);
    EXPECT_EQ(0x0B, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.C = 0x0F;
    cpu.flag.C = true;
    cpu.execute(0x89, arg1, arg2);
    EXPECT_EQ(0x01 + 0x0F + 0x01, cpu.A);
    EXPECT_EQ(0x0F, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x0F;
    cpu.D = 0x01;
    cpu.flag.C = true;
    cpu.execute(0x8A, arg1, arg2);
    EXPECT_EQ(0x0F + 0x01 + 0x01, cpu.A);
    EXPECT_EQ(0x01, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x03;
    cpu.E = 0x0E;
    cpu.flag.C = true;
    cpu.execute(0x8B, arg1, arg2);
    EXPECT_EQ(0x03 + 0x0E + 0x01, cpu.A);
    EXPECT_EQ(0x0E, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x07;
    cpu.H = 0x0C;
    cpu.flag.C = true;
    cpu.execute(0x8C, arg1, arg2);
    EXPECT_EQ(0x07 + 0x0C + 0x01, cpu.A);
    EXPECT_EQ(0x0C, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x0F;
    cpu.L = 0x0A;
    cpu.flag.C = true;
    cpu.execute(0x8D, arg1, arg2);
    EXPECT_EQ(0x0F + 0x0A + 0x01, cpu.A);
    EXPECT_EQ(0x0A, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x0A;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x0A;
    cpu.flag.C = true;
    cpu.execute(0x8E, arg1, arg2);
    EXPECT_EQ(0x0A + 0x0A + 0x01, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x0A, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x0B;
    arg1 = 0x0B;
    cpu.flag.C = true;
    cpu.execute(0xCE, arg1, arg2);
    EXPECT_EQ(0x0B + 0x0B + 0x01, cpu.A);
    EXPECT_EQ(0x0B, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 82
TEST_F(TestCpu, SUB_An_NoBorrow) {
    unsigned char arg1;
    unsigned char arg2;

    // A - A is always Zero
    cpu.A = 0x01;
    cpu.execute(0x97, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x03;
    cpu.B = 0x02;
    cpu.execute(0x90, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x04;
    cpu.C = 0x03;
    cpu.execute(0x91, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(0x03, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x0F;
    cpu.D = 0x04;
    cpu.execute(0x92, arg1, arg2);
    EXPECT_EQ(0x0B, cpu.A);
    EXPECT_EQ(0x04, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x07;
    cpu.E = 0x05;
    cpu.execute(0x93, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);
    EXPECT_EQ(0x05, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x08;
    cpu.H = 0x02;
    cpu.execute(0x94, arg1, arg2);
    EXPECT_EQ(0x06, cpu.A);
    EXPECT_EQ(0x02, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x13;
    cpu.L = 0x02;
    cpu.execute(0x95, arg1, arg2);
    EXPECT_EQ(0x11, cpu.A);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x09;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x05;
    cpu.execute(0x96, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x05, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x04;
    arg1 = 0x03;
    cpu.execute(0xD6, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(0x03, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 82
TEST_F(TestCpu, SUB_An_Zero) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x01;
    cpu.execute(0x97, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x00;
    cpu.B = 0x00;
    cpu.execute(0x90, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x91;
    cpu.C = 0x91;
    cpu.execute(0x91, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x91, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x06;
    cpu.D = 0x06;
    cpu.execute(0x92, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x06, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x00;
    cpu.E = 0x00;
    cpu.execute(0x93, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x03;
    cpu.H = 0x03;
    cpu.execute(0x94, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x03, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x02;
    cpu.L = 0x02;
    cpu.execute(0x95, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x00;
    cpu.H = 0x00;
    cpu.L = 0x02;
    cpu.memory()[0x0002] = 0x00;
    cpu.execute(0x96, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(0x00, cpu.memory()[0x0002]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x00;
    arg1 = 0x00;
    cpu.execute(0xD6, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, arg1);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 82
TEST_F(TestCpu, SUB_An_3Borrow) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x11;
    cpu.B = 0x03;
    cpu.execute(0x90, arg1, arg2);
    EXPECT_EQ(0x11 - 0x03, cpu.A);
    EXPECT_EQ(0x03, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x22;
    cpu.C = 0x0F;
    cpu.execute(0x91, arg1, arg2);
    EXPECT_EQ(0x22 - 0x0F, cpu.A);
    EXPECT_EQ(0x0F, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x34;
    cpu.D = 0x05;
    cpu.execute(0x92, arg1, arg2);
    EXPECT_EQ(0x34 - 0x05, cpu.A);
    EXPECT_EQ(0x05, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x56;
    cpu.E = 0x1E;
    cpu.execute(0x93, arg1, arg2);
    EXPECT_EQ(0x56 - 0x1E, cpu.A);
    EXPECT_EQ(0x1E, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x17;
    cpu.H = 0x0C;
    cpu.execute(0x94, arg1, arg2);
    EXPECT_EQ(0x17 - 0x0C, cpu.A);
    EXPECT_EQ(0x0C, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x23;
    cpu.L = 0x0A;
    cpu.execute(0x95, arg1, arg2);
    EXPECT_EQ(0x23 - 0x0A, cpu.A);
    EXPECT_EQ(0x0A, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x1A;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x0B;
    cpu.execute(0x96, arg1, arg2);
    EXPECT_EQ(0x1A - 0x0B, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x0B, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x1B;
    arg1 = 0x0C;
    cpu.execute(0xD6, arg1, arg2);
    EXPECT_EQ(0x1B - 0x0C, cpu.A);
    EXPECT_EQ(0x0C, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 82
TEST_F(TestCpu, SUB_An_7Borrow) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0xA0;
    cpu.B = 0xB0;
    cpu.execute(0x90, arg1, arg2);
    EXPECT_EQ((unsigned char) (0xA0 - 0xB0), cpu.A);
    EXPECT_EQ(0xB0, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x20;
    cpu.C = 0xF0;
    cpu.execute(0x91, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x20 - 0xF0), cpu.A);
    EXPECT_EQ(0xF0, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x40;
    cpu.D = 0x60;
    cpu.execute(0x92, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x40 - 0x60), cpu.A);
    EXPECT_EQ(0x60, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xE0;
    cpu.E = 0xF0;
    cpu.execute(0x93, arg1, arg2);
    EXPECT_EQ((unsigned char) (0xE0 - 0xF0), cpu.A);
    EXPECT_EQ(0xF0, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x76;
    cpu.H = 0x85;
    cpu.execute(0x94, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x76 - 0x85), cpu.A);
    EXPECT_EQ(0x85, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x98;
    cpu.L = 0xA3;
    cpu.execute(0x95, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x98 - 0xA3), cpu.A);
    EXPECT_EQ(0xA3, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xA0;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0xB0;
    cpu.execute(0x96, arg1, arg2);
    EXPECT_EQ((unsigned char) (0xA0 - 0xB0), cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0xB0, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xB3;
    arg1 = 0xC1;
    cpu.execute(0xD6, arg1, arg2);
    EXPECT_EQ((unsigned char) (0xB3 - 0xC1), cpu.A);
    EXPECT_EQ(0xC1, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 82
TEST_F(TestCpu, SUB_An_BothBorrow) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0xAA;
    cpu.B = 0xBB;
    cpu.execute(0x90, arg1, arg2);
    EXPECT_EQ((unsigned char) (0xAA - 0xBB), cpu.A);
    EXPECT_EQ(0xBB, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x22;
    cpu.C = 0xFF;
    cpu.execute(0x91, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x22 - 0xFF), cpu.A);
    EXPECT_EQ(0xFF, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x33;
    cpu.D = 0xEE;
    cpu.execute(0x92, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x33 - 0xEE), cpu.A);
    EXPECT_EQ(0xEE, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x44;
    cpu.E = 0xEE;
    cpu.execute(0x93, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x44 - 0xEE), cpu.A);
    EXPECT_EQ(0xEE, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x77;
    cpu.H = 0xCC;
    cpu.execute(0x94, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x77 - 0xCC), cpu.A);
    EXPECT_EQ(0xCC, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x99;
    cpu.L = 0xAA;
    cpu.execute(0x95, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x99 - 0xAA), cpu.A);
    EXPECT_EQ(0xAA, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x23;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0xAB;
    cpu.execute(0x96, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x23 - 0xAB), cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0xAB, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xA7;
    arg1 = 0xB9;
    cpu.execute(0xD6, arg1, arg2);
    EXPECT_EQ((unsigned char) (0xA7 - 0xB9), cpu.A);
    EXPECT_EQ(0xB9, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 83
TEST_F(TestCpu, SBC_An_NoCarryIn_NoCarryOut) {
    unsigned char arg1;
    unsigned char arg2;
    
    // A - A Can only ever be zero...
    cpu.A = 0x01;
    cpu.flag.C = false;
    cpu.execute(0x9F, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x03;
    cpu.B = 0x02;
    cpu.flag.C = false;
    cpu.execute(0x98, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x44;
    cpu.C = 0x33;
    cpu.flag.C = false;
    cpu.execute(0x99, arg1, arg2);
    EXPECT_EQ(0x11, cpu.A);
    EXPECT_EQ(0x33, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x09;
    cpu.D = 0x04;
    cpu.flag.C = false;
    cpu.execute(0x9A, arg1, arg2);
    EXPECT_EQ(0x05, cpu.A);
    EXPECT_EQ(0x04, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x17;
    cpu.E = 0x05;
    cpu.flag.C = false;
    cpu.execute(0x9B, arg1, arg2);
    EXPECT_EQ(0x12, cpu.A);
    EXPECT_EQ(0x05, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x03;
    cpu.H = 0x02;
    cpu.flag.C = false;
    cpu.execute(0x9C, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(0x02, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x05;
    cpu.L = 0x02;
    cpu.flag.C = false;
    cpu.execute(0x9D, arg1, arg2);
    EXPECT_EQ(0x03, cpu.A);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x37;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.flag.C = false;
    cpu.memory()[0x0001] = 0x05;
    cpu.execute(0x9E, arg1, arg2);
    EXPECT_EQ(0x32, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x05, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 83
TEST_F(TestCpu, SBC_An_CarryIn_NoBorrow) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x01;
    cpu.flag.C = true;
    cpu.execute(0x9F, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x02;
    cpu.B = 0x02;
    cpu.flag.C = true;
    cpu.execute(0x98, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x05;
    cpu.C = 0x03;
    cpu.flag.C = true;
    cpu.execute(0x99, arg1, arg2);
    EXPECT_EQ(0x03, cpu.A);
    EXPECT_EQ(0x03, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x19;
    cpu.D = 0x04;
    cpu.flag.C = true;
    cpu.execute(0x9A, arg1, arg2);
    EXPECT_EQ(0x16, cpu.A);
    EXPECT_EQ(0x04, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x08;
    cpu.E = 0x05;
    cpu.flag.C = true;
    cpu.execute(0x9B, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);
    EXPECT_EQ(0x05, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x02;
    cpu.H = 0x02;
    cpu.flag.C = true;
    cpu.execute(0x9C, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(0x02, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x03;
    cpu.L = 0x02;
    cpu.flag.C = true;
    cpu.execute(0x9D, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x06;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.flag.C = true;
    cpu.memory()[0x0001] = 0x05;
    cpu.execute(0x9E, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x05, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 83
TEST_F(TestCpu, SBC_An_CarryIn_3Borrow) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x1A;
    cpu.B = 0x0C;
    cpu.flag.C = true;
    cpu.execute(0x98, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x1A - 0x0C + 0x01), cpu.A);
    EXPECT_EQ(0x0C, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x11;
    cpu.C = 0x0F;
    cpu.flag.C = true;
    cpu.execute(0x99, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x11 - 0x0F + 0x01), cpu.A);
    EXPECT_EQ(0x0F, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x1C;
    cpu.D = 0x0F;
    cpu.flag.C = true;
    cpu.execute(0x9A, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x1C - 0x0F + 0x01), cpu.A);
    EXPECT_EQ(0x0F, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x16;
    cpu.E = 0x0B;
    cpu.flag.C = true;
    cpu.execute(0x9B, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x16 - 0x0B + 0x01), cpu.A);
    EXPECT_EQ(0x0B, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x17;
    cpu.H = 0x0C;
    cpu.flag.C = true;
    cpu.execute(0x9C, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x17 - 0x0C + 0x01), cpu.A);
    EXPECT_EQ(0x0C, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x1A;
    cpu.L = 0x0F;
    cpu.flag.C = true;
    cpu.execute(0x9D, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x1A - 0x0F + 0x01), cpu.A);
    EXPECT_EQ(0x0F, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x19;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x0B;
    cpu.flag.C = true;
    cpu.execute(0x9E, arg1, arg2);
    EXPECT_EQ((unsigned char) (0x19 - 0x0B + 0x01), cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x0B, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 84
TEST_F(TestCpu, AND_An_NonZero) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x01;
    cpu.execute(0xA7, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x0F;
    cpu.B = 0x02;
    cpu.execute(0xA0, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x07;
    cpu.C = 0x03;
    cpu.execute(0xA1, arg1, arg2);
    EXPECT_EQ(0x03, cpu.A);
    EXPECT_EQ(0x03, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xFF;
    cpu.D = 0x44;
    cpu.execute(0xA2, arg1, arg2);
    EXPECT_EQ(0x44, cpu.A);
    EXPECT_EQ(0x44, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xFF;
    cpu.E = 0x57;
    cpu.execute(0xA3, arg1, arg2);
    EXPECT_EQ(0x57, cpu.A);
    EXPECT_EQ(0x57, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x08;
    cpu.H = 0xFF;
    cpu.execute(0xA4, arg1, arg2);
    EXPECT_EQ(0x08, cpu.A);
    EXPECT_EQ(0xFF, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x13;
    cpu.L = 0xFF;
    cpu.execute(0xA5, arg1, arg2);
    EXPECT_EQ(0x13, cpu.A);
    EXPECT_EQ(0xFF, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xF0;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x85;
    cpu.execute(0xA6, arg1, arg2);
    EXPECT_EQ(0x80, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x85, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x67;
    arg1 = 0xA3;
    cpu.execute(0xE6, arg1, arg2);
    EXPECT_EQ(0x67 & 0xA3, cpu.A);
    EXPECT_EQ(0xA3, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 84
TEST_F(TestCpu, AND_An_Zero) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x00;
    cpu.execute(0xA7, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.B = 0x77;
    cpu.execute(0xA0, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x77, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xF0;
    cpu.C = 0x0F;
    cpu.execute(0xA1, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x0F, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x0F;
    cpu.D = 0xF0;
    cpu.execute(0xA2, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0xF0, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x04;
    cpu.E = 0x08;
    cpu.execute(0xA3, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x08, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.H = 0x0A;
    cpu.execute(0xA4, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x0A, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x20;
    cpu.L = 0x02;
    cpu.execute(0xA5, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.H = 0x00;
    cpu.L = 0x02;
    cpu.memory()[0x0002] = 0x00;
    cpu.execute(0xA6, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(0x00, cpu.memory()[0x0002]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    arg1 = 0x00;
    cpu.execute(0xE6, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, arg1);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 85
TEST_F(TestCpu, OR_An_NonZero) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x01;
    cpu.execute(0xB7, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x0F;
    cpu.B = 0x02;
    cpu.execute(0xB0, arg1, arg2);
    EXPECT_EQ(0x0F, cpu.A);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x07;
    cpu.C = 0x0F;
    cpu.execute(0xB1, arg1, arg2);
    EXPECT_EQ(0x0F, cpu.A);
    EXPECT_EQ(0x0F, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xFF;
    cpu.D = 0x44;
    cpu.execute(0xB2, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(0x44, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xFF;
    cpu.E = 0x57;
    cpu.execute(0xB3, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(0x57, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x08;
    cpu.H = 0x00;
    cpu.execute(0xB4, arg1, arg2);
    EXPECT_EQ(0x08, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x13;
    cpu.L = 0xFF;
    cpu.execute(0xB5, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(0xFF, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xF0;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x85;
    cpu.execute(0xB6, arg1, arg2);
    EXPECT_EQ(0xF5, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x85, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x67;
    arg1 = 0xA3;
    cpu.execute(0xF6, arg1, arg2);
    EXPECT_EQ(0x67 | 0xA3, cpu.A);
    EXPECT_EQ(0xA3, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 85
TEST_F(TestCpu, OR_An_Zero) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x00;
    cpu.execute(0xB7, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.B = 0x00;
    cpu.execute(0xB0, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.C = 0x00;
    cpu.execute(0xB1, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.D = 0x00;
    cpu.execute(0xB2, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.E = 0x00;
    cpu.execute(0xB3, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.H = 0x00;
    cpu.execute(0xB4, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.L = 0x00;
    cpu.execute(0xB5, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.H = 0x00;
    cpu.L = 0x02;
    cpu.memory()[0x0002] = 0x00;
    cpu.execute(0xB6, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(0x00, cpu.memory()[0x0002]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    arg1 = 0x00;
    cpu.execute(0xF6, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, arg1);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 86
TEST_F(TestCpu, XOR_An_NonZero) {
    unsigned char arg1;
    unsigned char arg2;

    // Can't test A because A XOR A = 0

    cpu.A = 0xF0;
    cpu.B = 0x02;
    cpu.execute(0xA8, arg1, arg2);
    EXPECT_EQ(0xF2, cpu.A);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x07;
    cpu.C = 0x0F;
    cpu.execute(0xA9, arg1, arg2);
    EXPECT_EQ(0x0F ^ 0x07, cpu.A);
    EXPECT_EQ(0x0F, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.D = 0x44;
    cpu.execute(0xAA, arg1, arg2);
    EXPECT_EQ(0x44, cpu.A);
    EXPECT_EQ(0x44, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xF0;
    cpu.E = 0x07;
    cpu.execute(0xAB, arg1, arg2);
    EXPECT_EQ(0xF7, cpu.A);
    EXPECT_EQ(0x07, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x08;
    cpu.H = 0x00;
    cpu.execute(0xAC, arg1, arg2);
    EXPECT_EQ(0x08, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x13;
    cpu.L = 0xFF;
    cpu.execute(0xAD, arg1, arg2);
    EXPECT_EQ(0xFF ^ 0x13, cpu.A);
    EXPECT_EQ(0xFF, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xF0;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x05;
    cpu.execute(0xAE, arg1, arg2);
    EXPECT_EQ(0xF5, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x05, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x67;
    arg1 = 0xA3;
    cpu.execute(0xEE, arg1, arg2);
    EXPECT_EQ(0x67 ^ 0xA3, cpu.A);
    EXPECT_EQ(0xA3, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 86
TEST_F(TestCpu, XOR_An_Zero) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x65;
    cpu.execute(0xAF, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.B = 0x00;
    cpu.execute(0xA8, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x77;
    cpu.C = 0x77;
    cpu.execute(0xA9, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x77, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xF4;
    cpu.D = 0xF4;
    cpu.execute(0xAA, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0xF4, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x01;
    cpu.E = 0x01;
    cpu.execute(0xAB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x01, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x20;
    cpu.H = 0x20;
    cpu.execute(0xAC, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x20, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.L = 0x00;
    cpu.execute(0xAD, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x00;
    cpu.H = 0x00;
    cpu.L = 0x02;
    cpu.memory()[0x0002] = 0x00;
    cpu.execute(0xAE, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(0x00, cpu.memory()[0x0002]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x33;
    arg1 = 0x33;
    cpu.execute(0xEE, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x33, arg1);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 87
TEST_F(TestCpu, CP_An_NoBorrow) {
    unsigned char arg1;
    unsigned char arg2;

    // A - A is always Zero
    cpu.A = 0x01;
    cpu.execute(0xBF, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x03;
    cpu.B = 0x02;
    cpu.execute(0xB8, arg1, arg2);
    EXPECT_EQ(0x03, cpu.A);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x04;
    cpu.C = 0x03;
    cpu.execute(0xB9, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);
    EXPECT_EQ(0x03, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x0F;
    cpu.D = 0x04;
    cpu.execute(0xBA, arg1, arg2);
    EXPECT_EQ(0x0F, cpu.A);
    EXPECT_EQ(0x04, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x07;
    cpu.E = 0x05;
    cpu.execute(0xBB, arg1, arg2);
    EXPECT_EQ(0x07, cpu.A);
    EXPECT_EQ(0x05, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x08;
    cpu.H = 0x02;
    cpu.execute(0xBC, arg1, arg2);
    EXPECT_EQ(0x08, cpu.A);
    EXPECT_EQ(0x02, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x13;
    cpu.L = 0x02;
    cpu.execute(0xBD, arg1, arg2);
    EXPECT_EQ(0x13, cpu.A);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x09;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x05;
    cpu.execute(0xBE, arg1, arg2);
    EXPECT_EQ(0x09, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x05, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x04;
    arg1 = 0x03;
    cpu.execute(0xFE, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);
    EXPECT_EQ(0x03, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 87
TEST_F(TestCpu, CP_An_Zero) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x01;
    cpu.execute(0xBF, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x00;
    cpu.B = 0x00;
    cpu.execute(0xB8, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x91;
    cpu.C = 0x91;
    cpu.execute(0xB9, arg1, arg2);
    EXPECT_EQ(0x91, cpu.A);
    EXPECT_EQ(0x91, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x06;
    cpu.D = 0x06;
    cpu.execute(0xBA, arg1, arg2);
    EXPECT_EQ(0x06, cpu.A);
    EXPECT_EQ(0x06, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x00;
    cpu.E = 0x00;
    cpu.execute(0xBB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x03;
    cpu.H = 0x03;
    cpu.execute(0xBC, arg1, arg2);
    EXPECT_EQ(0x03, cpu.A);
    EXPECT_EQ(0x03, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x02;
    cpu.L = 0x02;
    cpu.execute(0xBD, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x00;
    cpu.H = 0x00;
    cpu.L = 0x02;
    cpu.memory()[0x0002] = 0x00;
    cpu.execute(0xBE, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(0x00, cpu.memory()[0x0002]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x00;
    arg1 = 0x00;
    cpu.execute(0xFE, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(0x00, arg1);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 87
TEST_F(TestCpu, CP_An_3Borrow) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0x11;
    cpu.B = 0x03;
    cpu.execute(0xB8, arg1, arg2);
    EXPECT_EQ(0x11, cpu.A);
    EXPECT_EQ(0x03, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x22;
    cpu.C = 0x0F;
    cpu.execute(0xB9, arg1, arg2);
    EXPECT_EQ(0x22, cpu.A);
    EXPECT_EQ(0x0F, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x34;
    cpu.D = 0x05;
    cpu.execute(0xBA, arg1, arg2);
    EXPECT_EQ(0x34, cpu.A);
    EXPECT_EQ(0x05, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x56;
    cpu.E = 0x1E;
    cpu.execute(0xBB, arg1, arg2);
    EXPECT_EQ(0x56, cpu.A);
    EXPECT_EQ(0x1E, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x17;
    cpu.H = 0x0C;
    cpu.execute(0xBC, arg1, arg2);
    EXPECT_EQ(0x17, cpu.A);
    EXPECT_EQ(0x0C, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x23;
    cpu.L = 0x0A;
    cpu.execute(0xBD, arg1, arg2);
    EXPECT_EQ(0x23, cpu.A);
    EXPECT_EQ(0x0A, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x1A;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x0B;
    cpu.execute(0xBE, arg1, arg2);
    EXPECT_EQ(0x1A, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x0B, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.A = 0x1B;
    arg1 = 0x0C;
    cpu.execute(0xFE, arg1, arg2);
    EXPECT_EQ(0x1B, cpu.A);
    EXPECT_EQ(0x0C, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 87
TEST_F(TestCpu, CP_An_7Borrow) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0xA0;
    cpu.B = 0xB0;
    cpu.execute(0xB8, arg1, arg2);
    EXPECT_EQ(0xA0, cpu.A);
    EXPECT_EQ(0xB0, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x20;
    cpu.C = 0xF0;
    cpu.execute(0xB9, arg1, arg2);
    EXPECT_EQ(0x20, cpu.A);
    EXPECT_EQ(0xF0, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x40;
    cpu.D = 0x60;
    cpu.execute(0xBA, arg1, arg2);
    EXPECT_EQ(0x40, cpu.A);
    EXPECT_EQ(0x60, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xE0;
    cpu.E = 0xF0;
    cpu.execute(0xBB, arg1, arg2);
    EXPECT_EQ(0xE0, cpu.A);
    EXPECT_EQ(0xF0, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x76;
    cpu.H = 0x85;
    cpu.execute(0xBC, arg1, arg2);
    EXPECT_EQ(0x76, cpu.A);
    EXPECT_EQ(0x85, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x98;
    cpu.L = 0xA3;
    cpu.execute(0xBD, arg1, arg2);
    EXPECT_EQ(0x98, cpu.A);
    EXPECT_EQ(0xA3, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xA0;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0xB0;
    cpu.execute(0xBE, arg1, arg2);
    EXPECT_EQ(0xA0, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0xB0, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xB3;
    arg1 = 0xC1;
    cpu.execute(0xFE, arg1, arg2);
    EXPECT_EQ(0xB3, cpu.A);
    EXPECT_EQ(0xC1, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 87
TEST_F(TestCpu, CP_An_BothBorrow) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.A = 0xAA;
    cpu.B = 0xBB;
    cpu.execute(0xB8, arg1, arg2);
    EXPECT_EQ(0xAA, cpu.A);
    EXPECT_EQ(0xBB, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x22;
    cpu.C = 0xFF;
    cpu.execute(0xB9, arg1, arg2);
    EXPECT_EQ(0x22, cpu.A);
    EXPECT_EQ(0xFF, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x33;
    cpu.D = 0xEE;
    cpu.execute(0xBA, arg1, arg2);
    EXPECT_EQ(0x33, cpu.A);
    EXPECT_EQ(0xEE, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x44;
    cpu.E = 0xEE;
    cpu.execute(0xBB, arg1, arg2);
    EXPECT_EQ(0x44, cpu.A);
    EXPECT_EQ(0xEE, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x77;
    cpu.H = 0xCC;
    cpu.execute(0xBC, arg1, arg2);
    EXPECT_EQ(0x77, cpu.A);
    EXPECT_EQ(0xCC, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x99;
    cpu.L = 0xAA;
    cpu.execute(0xBD, arg1, arg2);
    EXPECT_EQ(0x99, cpu.A);
    EXPECT_EQ(0xAA, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0x23;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0xAB;
    cpu.execute(0xBE, arg1, arg2);
    EXPECT_EQ(0x23, cpu.A);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0xAB, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.A = 0xA7;
    arg1 = 0xB9;
    cpu.execute(0xFE, arg1, arg2);
    EXPECT_EQ(0xA7, cpu.A);
    EXPECT_EQ(0xB9, arg1);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 88
TEST_F(TestCpu, INC_n_NoCarry_NonZero) {
    unsigned char arg1;
    unsigned char arg2;

    bool OLD_C;

    OLD_C = cpu.flag.C;
    cpu.A = 0x01;
    cpu.execute(0x3C, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.B = 0x02;
    cpu.execute(0x04, arg1, arg2);
    EXPECT_EQ(0x03, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.C = 0x00;
    cpu.execute(0x0C, arg1, arg2);
    EXPECT_EQ(0x01, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.D = 0x02;
    cpu.execute(0x14, arg1, arg2);
    EXPECT_EQ(0x03, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.E = 0x02;
    cpu.execute(0x1C, arg1, arg2);
    EXPECT_EQ(0x03, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.H = 0x02;
    cpu.execute(0x24, arg1, arg2);
    EXPECT_EQ(0x03, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.L = 0x02;
    cpu.execute(0x2C, arg1, arg2);
    EXPECT_EQ(0x03, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x01;
    cpu.execute(0x34, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x02, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);
}

// Page 88
TEST_F(TestCpu, INC_n_Zero) {
    unsigned char arg1;
    unsigned char arg2;

    bool OLD_C;

    OLD_C = cpu.flag.C;
    cpu.A = 0xFF;
    cpu.execute(0x3C, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.B = 0xFF;
    cpu.execute(0x04, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.C = 0xFF;
    cpu.execute(0x0C, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.D = 0xFF;
    cpu.execute(0x14, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.E = 0xFF;
    cpu.execute(0x1C, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.H = 0xFF;
    cpu.execute(0x24, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.L = 0xFF;
    cpu.execute(0x2C, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0xFF;
    cpu.execute(0x34, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);
}

// Page 88
TEST_F(TestCpu, INC_n_Carry) {
    unsigned char arg1;
    unsigned char arg2;

    bool OLD_C;

    OLD_C = cpu.flag.C;
    cpu.A = 0x0F;
    cpu.execute(0x3C, arg1, arg2);
    EXPECT_EQ(0x10, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.B = 0x1F;
    cpu.execute(0x04, arg1, arg2);
    EXPECT_EQ(0x20, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.C = 0x2F;
    cpu.execute(0x0C, arg1, arg2);
    EXPECT_EQ(0x30, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.D = 0x0F;
    cpu.execute(0x14, arg1, arg2);
    EXPECT_EQ(0x10, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.E = 0x8F;
    cpu.execute(0x1C, arg1, arg2);
    EXPECT_EQ(0x90, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.H = 0x0F;
    cpu.execute(0x24, arg1, arg2);
    EXPECT_EQ(0x10, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.L = 0xAF;
    cpu.execute(0x2C, arg1, arg2);
    EXPECT_EQ(0xB0, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0xEF;
    cpu.execute(0x34, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0xF0, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);
}

// Page 89
TEST_F(TestCpu, DEC_n_NoBorrow_NonZero) {
    unsigned char arg1;
    unsigned char arg2;

    bool OLD_C;

    OLD_C = cpu.flag.C;
    cpu.A = 0x02;
    cpu.execute(0x3D, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.B = 0x03;
    cpu.execute(0x05, arg1, arg2);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.C = 0x1F;
    cpu.execute(0x0D, arg1, arg2);
    EXPECT_EQ(0x1E, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.D = 0x02;
    cpu.execute(0x15, arg1, arg2);
    EXPECT_EQ(0x01, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.E = 0x11;
    cpu.execute(0x1D, arg1, arg2);
    EXPECT_EQ(0x10, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.H = 0x25;
    cpu.execute(0x25, arg1, arg2);
    EXPECT_EQ(0x24, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.L = 0x9;
    cpu.execute(0x2D, arg1, arg2);
    EXPECT_EQ(0x08, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x03;
    cpu.execute(0x35, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x02, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);
}

// Page 89
TEST_F(TestCpu, DEC_n_Zero) {
    unsigned char arg1;
    unsigned char arg2;

    bool OLD_C;

    OLD_C = cpu.flag.C;
    cpu.A = 0x01;
    cpu.execute(0x3D, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.B = 0x01;
    cpu.execute(0x05, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.C = 0x01;
    cpu.execute(0x0D, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.D = 0x01;
    cpu.execute(0x15, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.E = 0x01;
    cpu.execute(0x1D, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.H = 0x01;
    cpu.execute(0x25, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.L = 0x01;
    cpu.execute(0x2D, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x01;
    cpu.execute(0x35, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);
}

// Page 89
TEST_F(TestCpu, DEC_n_Carry) {
    unsigned char arg1;
    unsigned char arg2;

    bool OLD_C;

    OLD_C = cpu.flag.C;
    cpu.A = 0x10;
    cpu.execute(0x3D, arg1, arg2);
    EXPECT_EQ(0x0F, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.B = 0x20;
    cpu.execute(0x05, arg1, arg2);
    EXPECT_EQ(0x1F, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.C = 0x40;
    cpu.execute(0x0D, arg1, arg2);
    EXPECT_EQ(0x3F, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.D = 0xF0;
    cpu.execute(0x15, arg1, arg2);
    EXPECT_EQ(0xEF, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.E = 0x80;
    cpu.execute(0x1D, arg1, arg2);
    EXPECT_EQ(0x7F, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.H = 0x00;
    cpu.execute(0x25, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    OLD_C = cpu.flag.C;
    cpu.L = 0x10;
    cpu.execute(0x2D, arg1, arg2);
    EXPECT_EQ(0x0F, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x20;
    cpu.execute(0x35, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x1F, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);
}

// Page 90
TEST_F(TestCpu, ADD16_HLn_NoCarry) {
    unsigned char arg1;
    unsigned char arg2;

    // NOTE: Endianness -- H + B, L + C, H is msb

    bool OLD_Z;

    OLD_Z = cpu.flag.Z;
    cpu.H = 0x01;
    cpu.L = 0x01;
    cpu.B = 0x01;
    cpu.C = 0x01;
    cpu.execute(0x09, arg1, arg2);
    EXPECT_EQ(0x02, cpu.H);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(0x01, cpu.B);
    EXPECT_EQ(0x01, cpu.C);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    OLD_Z = cpu.flag.Z;
    cpu.H = 0x11;
    cpu.L = 0x22;
    cpu.D = 0x03;
    cpu.E = 0x07;
    cpu.execute(0x19, arg1, arg2);
    EXPECT_EQ(0x14, cpu.H);
    EXPECT_EQ(0x29, cpu.L);
    EXPECT_EQ(0x03, cpu.D);
    EXPECT_EQ(0x07, cpu.E);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    OLD_Z = cpu.flag.Z;
    cpu.H = 0x13;
    cpu.L = 0x22;
    cpu.execute(0x29, arg1, arg2);
    EXPECT_EQ(0x26, cpu.H);
    EXPECT_EQ(0x44, cpu.L);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    OLD_Z = cpu.flag.Z;
    cpu.H = 0x11;
    cpu.L = 0x22;
    cpu.SP = 0x1010;
    cpu.execute(0x39, arg1, arg2);
    EXPECT_EQ(0x21, cpu.H);
    EXPECT_EQ(0x32, cpu.L);
    EXPECT_EQ(0x1010, cpu.SP);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 90
TEST_F(TestCpu, ADD16_HLn_11Carry) {
    unsigned char arg1;
    unsigned char arg2;

    bool OLD_Z;

    OLD_Z = cpu.flag.Z;
    cpu.H = 0x0F;
    cpu.L = 0x01;
    cpu.B = 0x01;
    cpu.C = 0x01;
    cpu.execute(0x09, arg1, arg2);
    EXPECT_EQ(0x10, cpu.H);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(0x01, cpu.B);
    EXPECT_EQ(0x01, cpu.C);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    OLD_Z = cpu.flag.Z;
    cpu.H = 0x1F;
    cpu.L = 0x22;
    cpu.D = 0x03;
    cpu.E = 0x07;
    cpu.execute(0x19, arg1, arg2);
    EXPECT_EQ(0x22, cpu.H);
    EXPECT_EQ(0x29, cpu.L);
    EXPECT_EQ(0x03, cpu.D);
    EXPECT_EQ(0x07, cpu.E);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    OLD_Z = cpu.flag.Z;
    cpu.H = 0x19;
    cpu.L = 0x22;
    cpu.execute(0x29, arg1, arg2);
    EXPECT_EQ(0x32, cpu.H);
    EXPECT_EQ(0x44, cpu.L);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    OLD_Z = cpu.flag.Z;
    cpu.H = 0x1A;
    cpu.L = 0x22;
    cpu.SP = 0x1A10;
    cpu.execute(0x39, arg1, arg2);
    EXPECT_EQ(0x34, cpu.H);
    EXPECT_EQ(0x32, cpu.L);
    EXPECT_EQ(0x1A10, cpu.SP);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 90
TEST_F(TestCpu, ADD16_HLn_15Carry) {
    unsigned char arg1;
    unsigned char arg2;

    bool OLD_Z;

    OLD_Z = cpu.flag.Z;
    cpu.H = 0xF1;
    cpu.L = 0x01;
    cpu.B = 0x11;
    cpu.C = 0x01;
    cpu.execute(0x09, arg1, arg2);
    EXPECT_EQ(0x02, cpu.H);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(0x11, cpu.B);
    EXPECT_EQ(0x01, cpu.C);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    OLD_Z = cpu.flag.Z;
    cpu.H = 0xE1;
    cpu.L = 0x22;
    cpu.D = 0x33;
    cpu.E = 0x07;
    cpu.execute(0x19, arg1, arg2);
    EXPECT_EQ(0x14, cpu.H);
    EXPECT_EQ(0x29, cpu.L);
    EXPECT_EQ(0x33, cpu.D);
    EXPECT_EQ(0x07, cpu.E);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    OLD_Z = cpu.flag.Z;
    cpu.H = 0x93;
    cpu.L = 0x22;
    cpu.execute(0x29, arg1, arg2);
    EXPECT_EQ(0x26, cpu.H);
    EXPECT_EQ(0x44, cpu.L);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    OLD_Z = cpu.flag.Z;
    cpu.H = 0x11;
    cpu.L = 0x22;
    cpu.SP = 0xF010;
    cpu.execute(0x39, arg1, arg2);
    EXPECT_EQ(0x01, cpu.H);
    EXPECT_EQ(0x32, cpu.L);
    EXPECT_EQ(0xF010, cpu.SP);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 90
TEST_F(TestCpu, ADD16_HLn_BothCarry) {
    unsigned char arg1;
    unsigned char arg2;

    bool OLD_Z;

    OLD_Z = cpu.flag.Z;
    cpu.H = 0xFF;
    cpu.L = 0x01;
    cpu.B = 0x01;
    cpu.C = 0x01;
    cpu.execute(0x09, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(0x01, cpu.B);
    EXPECT_EQ(0x01, cpu.C);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    OLD_Z = cpu.flag.Z;
    cpu.H = 0xFF;
    cpu.L = 0x22;
    cpu.D = 0x03;
    cpu.E = 0x07;
    cpu.execute(0x19, arg1, arg2);
    EXPECT_EQ(0x02, cpu.H);
    EXPECT_EQ(0x29, cpu.L);
    EXPECT_EQ(0x03, cpu.D);
    EXPECT_EQ(0x07, cpu.E);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    OLD_Z = cpu.flag.Z;
    cpu.H = 0x99;
    cpu.L = 0x22;
    cpu.execute(0x29, arg1, arg2);
    EXPECT_EQ(0x32, cpu.H);
    EXPECT_EQ(0x44, cpu.L);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    OLD_Z = cpu.flag.Z;
    cpu.H = 0xAA;
    cpu.L = 0x22;
    cpu.SP = 0xAA10;
    cpu.execute(0x39, arg1, arg2);
    EXPECT_EQ(0x54, cpu.H);
    EXPECT_EQ(0x32, cpu.L);
    EXPECT_EQ(0xAA10, cpu.SP);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 91
TEST_F(TestCpu, ADD16_SPn_NoCarry) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.SP = 0x0001;
    arg1 = 0x01;
    cpu.execute(0xE8, arg1, arg2);
    EXPECT_EQ(0x02, cpu.SP);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 91
TEST_F(TestCpu, ADD16_SPn_3Carry) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.SP = 0x000F;
    arg1 = 0x01;
    cpu.execute(0xE8, arg1, arg2);
    EXPECT_EQ(0x0010, cpu.SP);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 91
TEST_F(TestCpu, ADD16_SPn_7Carry) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.SP = 0x00F0;
    arg1 = 0x10;
    cpu.execute(0xE8, arg1, arg2);
    EXPECT_EQ(0x0100, cpu.SP);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 91
TEST_F(TestCpu, ADD16_SPn_BothCarry) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.SP = 0x00FF;
    arg1 = 0x01;
    cpu.execute(0xE8, arg1, arg2);
    EXPECT_EQ(0x0100, cpu.SP);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 92
TEST_F(TestCpu, INC16_nn_NoOverflow) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.B = 0x01;
    cpu.C = 0x01;
    cpu.execute(0x03, arg1, arg2);
    EXPECT_EQ(0x01, cpu.B);
    EXPECT_EQ(0x02, cpu.C);

    cpu.D = 0x02;
    cpu.E = 0x02;
    cpu.execute(0x13, arg1, arg2);
    EXPECT_EQ(0x02, cpu.D);
    EXPECT_EQ(0x03, cpu.E);

    cpu.H = 0x01;
    cpu.L = 0x01;
    cpu.execute(0x23, arg1, arg2);
    EXPECT_EQ(0x01, cpu.B);
    EXPECT_EQ(0x02, cpu.C);

    cpu.SP = 0x0011;
    cpu.execute(0x33, arg1, arg2);
    EXPECT_EQ(0x0012, cpu.SP);
}

// Page 92
TEST_F(TestCpu, INC16_nn_LSBOverflow) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.B = 0x01;
    cpu.C = 0xFF;
    cpu.execute(0x03, arg1, arg2);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(0x00, cpu.C);

    cpu.D = 0x02;
    cpu.E = 0xFF;
    cpu.execute(0x13, arg1, arg2);
    EXPECT_EQ(0x03, cpu.D);
    EXPECT_EQ(0x00, cpu.E);

    cpu.H = 0x01;
    cpu.L = 0xFF;
    cpu.execute(0x23, arg1, arg2);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(0x00, cpu.C);

    cpu.SP = 0x00FF;
    cpu.execute(0x33, arg1, arg2);
    EXPECT_EQ(0x0100, cpu.SP);
}

// Page 92
TEST_F(TestCpu, INC16_nn_MSBOverflow) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.B = 0xFF;
    cpu.C = 0xFF;
    cpu.execute(0x03, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(0x00, cpu.C);

    cpu.D = 0xFF;
    cpu.E = 0xFF;
    cpu.execute(0x13, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);
    EXPECT_EQ(0x00, cpu.E);

    cpu.H = 0xFF;
    cpu.L = 0xFF;
    cpu.execute(0x23, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(0x00, cpu.C);

    cpu.SP = 0xFFFF;
    cpu.execute(0x33, arg1, arg2);
    EXPECT_EQ(0x0000, cpu.SP);
}

// Page 93
TEST_F(TestCpu, DEC16_nn_NoBorrow) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.B = 0x01;
    cpu.C = 0x01;
    cpu.execute(0x0B, arg1, arg2);
    EXPECT_EQ(0x01, cpu.B);
    EXPECT_EQ(0x00, cpu.C);

    cpu.D = 0x02;
    cpu.E = 0x02;
    cpu.execute(0x1B, arg1, arg2);
    EXPECT_EQ(0x02, cpu.D);
    EXPECT_EQ(0x01, cpu.E);

    cpu.H = 0x01;
    cpu.L = 0x01;
    cpu.execute(0x2B, arg1, arg2);
    EXPECT_EQ(0x01, cpu.B);
    EXPECT_EQ(0x00, cpu.C);

    cpu.SP = 0x0011;
    cpu.execute(0x3B, arg1, arg2);
    EXPECT_EQ(0x0010, cpu.SP);
}

// Page 93
TEST_F(TestCpu, DEC16_nn_LSBBorrow) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.B = 0x01;
    cpu.C = 0x00;
    cpu.execute(0x0B, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(0xFF, cpu.C);

    cpu.D = 0x02;
    cpu.E = 0x00;
    cpu.execute(0x1B, arg1, arg2);
    EXPECT_EQ(0x01, cpu.D);
    EXPECT_EQ(0xFF, cpu.E);

    cpu.H = 0x01;
    cpu.L = 0x00;
    cpu.execute(0x2B, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(0xFF, cpu.C);

    cpu.SP = 0x0100;
    cpu.execute(0x3B, arg1, arg2);
    EXPECT_EQ(0x00FF, cpu.SP);
}

// Page 93
TEST_F(TestCpu, DEC16_nn_MSBBorrow) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.B = 0x00;
    cpu.C = 0x00;
    cpu.execute(0x0B, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.B);
    EXPECT_EQ(0xFF, cpu.C);

    cpu.D = 0x00;
    cpu.E = 0x00;
    cpu.execute(0x1B, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.D);
    EXPECT_EQ(0xFF, cpu.E);

    cpu.H = 0x00;
    cpu.L = 0x00;
    cpu.execute(0x2B, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.B);
    EXPECT_EQ(0xFF, cpu.C);

    cpu.SP = 0x0000;
    cpu.execute(0x3B, arg1, arg2);
    EXPECT_EQ(0xFFFF, cpu.SP);
}

// Page 94
TEST_F(TestCpu, SWAP_n_nonZero) {
    unsigned char arg1; 
    unsigned char arg2;

    cpu.A = 0x0F; 
    arg1 = 0x37;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xF0, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z); 
    EXPECT_EQ(false, cpu.flag.N); 
    EXPECT_EQ(false, cpu.flag.H); 
    EXPECT_EQ(false, cpu.flag.C); 

    cpu.B = 0x01; 
    arg1 = 0x30;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z); 
    EXPECT_EQ(false, cpu.flag.N); 
    EXPECT_EQ(false, cpu.flag.H); 
    EXPECT_EQ(false, cpu.flag.C); 

    cpu.C = 0x05; 
    arg1 = 0x31;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x50, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z); 
    EXPECT_EQ(false, cpu.flag.N); 
    EXPECT_EQ(false, cpu.flag.H); 
    EXPECT_EQ(false, cpu.flag.C); 

    cpu.D = 0x1A; 
    arg1 = 0x32;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xA1, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z); 
    EXPECT_EQ(false, cpu.flag.N); 
    EXPECT_EQ(false, cpu.flag.H); 
    EXPECT_EQ(false, cpu.flag.C); 

    cpu.E = 0x0F; 
    arg1 = 0x33;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xF0, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z); 
    EXPECT_EQ(false, cpu.flag.N); 
    EXPECT_EQ(false, cpu.flag.H); 
    EXPECT_EQ(false, cpu.flag.C); 

    cpu.H = 0x89; 
    arg1 = 0x34;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x98, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z); 
    EXPECT_EQ(false, cpu.flag.N); 
    EXPECT_EQ(false, cpu.flag.H); 
    EXPECT_EQ(false, cpu.flag.C); 

    cpu.L = 0xAA; 
    arg1 = 0x35;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xAA, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z); 
    EXPECT_EQ(false, cpu.flag.N); 
    EXPECT_EQ(false, cpu.flag.H); 
    EXPECT_EQ(false, cpu.flag.C); 

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x01;
    arg1 = 0x36;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x10, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 94
TEST_F(TestCpu, SWAP_n_Zero) {
    unsigned char arg1; 
    unsigned char arg2;

    cpu.A = 0x00; 
    arg1 = 0x37;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z); 
    EXPECT_EQ(false, cpu.flag.N); 
    EXPECT_EQ(false, cpu.flag.H); 
    EXPECT_EQ(false, cpu.flag.C); 

    cpu.B = 0x00; 
    arg1 = 0x30;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z); 
    EXPECT_EQ(false, cpu.flag.N); 
    EXPECT_EQ(false, cpu.flag.H); 
    EXPECT_EQ(false, cpu.flag.C); 

    cpu.C = 0x00; 
    arg1 = 0x31;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z); 
    EXPECT_EQ(false, cpu.flag.N); 
    EXPECT_EQ(false, cpu.flag.H); 
    EXPECT_EQ(false, cpu.flag.C); 

    cpu.D = 0x00; 
    arg1 = 0x32;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z); 
    EXPECT_EQ(false, cpu.flag.N); 
    EXPECT_EQ(false, cpu.flag.H); 
    EXPECT_EQ(false, cpu.flag.C); 

    cpu.E = 0x00; 
    arg1 = 0x33;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z); 
    EXPECT_EQ(false, cpu.flag.N); 
    EXPECT_EQ(false, cpu.flag.H); 
    EXPECT_EQ(false, cpu.flag.C); 

    cpu.H = 0x00; 
    arg1 = 0x34;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z); 
    EXPECT_EQ(false, cpu.flag.N); 
    EXPECT_EQ(false, cpu.flag.H); 
    EXPECT_EQ(false, cpu.flag.C); 

    cpu.L = 0x00; 
    arg1 = 0x35;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z); 
    EXPECT_EQ(false, cpu.flag.N); 
    EXPECT_EQ(false, cpu.flag.H); 
    EXPECT_EQ(false, cpu.flag.C); 

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0x36;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

#if 0
This instruction is a little hard, so I based the test case on this table from
http://www.z80.info/z80syntx.htm#DAA
--------------------------------------------------------------------------------
|           | C Flag  | HEX value in | H Flag | HEX value in | Number  | C flag|
| Operation | Before  | upper digit  | Before | lower digit  | added   | After |
|           | DAA     | (bit 7-4)    | DAA    | (bit 3-0)    | to byte | DAA   |
|------------------------------------------------------------------------------|
|01|        |    0    |     0-9      |   0    |     0-9      |   00    |   0   |
|02|  ADD   |    0    |     0-8      |   0    |     A-F      |   06    |   0   |
|03|        |    0    |     0-9      |   1    |     0-3      |   06    |   0   |
|04|  ADC   |    0    |     A-F      |   0    |     0-9      |   60    |   1   |
|05|        |    0    |     9-F      |   0    |     A-F      |   66    |   1   |
|06|  INC   |    0    |     A-F      |   1    |     0-3      |   66    |   1   |
|07|        |    1    |     0-2      |   0    |     0-9      |   60    |   1   |
|08|        |    1    |     0-2      |   0    |     A-F      |   66    |   1   |
|09|        |    1    |     0-3      |   1    |     0-3      |   66    |   1   |
|--|---------------------------------------------------------------------------|
|10|  SUB   |    0    |     0-9      |   0    |     0-9      |   00    |   0   |
|11|  SBC   |    0    |     0-8      |   1    |     6-F      |   FA    |   0   |
|12|  DEC   |    1    |     7-F      |   0    |     0-9      |   A0    |   1   |
|13|  NEG   |    1    |     6-F      |   1    |     6-F      |   9A    |   1   |
|------------------------------------------------------------------------------|
#endif

void doDAA(CPU &cpu,
           unsigned char lower,
           unsigned char upper,
           unsigned char error,
           bool C_before,
           bool H_before,
           bool C_after)
{
    unsigned char arg1;
    unsigned char arg2;

    cpu.flag.C = C_before;
    cpu.flag.H = H_before;
    cpu.A = lower | upper;
    cpu.execute(0x27, arg1, arg2);
    EXPECT_EQ((unsigned char) ((lower | upper) + error),
              (unsigned char) cpu.A);
    EXPECT_EQ(((unsigned char) ((lower | upper) + error)) == 0x00U,
              cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(C_after, cpu.flag.C);
}

void testDAA(CPU &cpu,
    unsigned char lowLower,
    unsigned char midLower,
    unsigned char hiLower,
    unsigned char lowUpper,
    unsigned char midUpper,
    unsigned char hiUpper,
    unsigned char error,
    bool C_before,
    bool H_before,
    bool C_after)
{
    {
        // Low-LOW
        SCOPED_TRACE("");
        doDAA(cpu,
              lowLower, lowUpper, error,
              C_before, H_before, C_after);
    }
    
    {
        // Low-Mid
        SCOPED_TRACE("");
        doDAA(cpu,
              lowLower, midUpper, error,
              C_before, H_before, C_after);
    }

    {
        // Low-Hi
        SCOPED_TRACE("");
        doDAA(cpu,
              lowLower, hiUpper, error,
              C_before, H_before, C_after);
    }

    {
        // Mid-Low
        SCOPED_TRACE("");
        doDAA(cpu,
              midLower, lowUpper, error,
              C_before, H_before, C_after);
    }

    {
        // Mid-Mid
        SCOPED_TRACE("");
        doDAA(cpu,
              midLower, midUpper, error,
              C_before, H_before, C_after);
    }

    {
        // Mid-Hi
        SCOPED_TRACE("");
        doDAA(cpu,
              midLower, hiUpper, error,
              C_before, H_before, C_after);
    }

    {
    // Hi-Low
    SCOPED_TRACE("");
    doDAA(cpu,
          hiLower, lowUpper, error,
          C_before, H_before, C_after);
    }

    {
    // Hi-Mid
    SCOPED_TRACE("");
    doDAA(cpu,
          hiLower, midUpper, error,
          C_before, H_before, C_after);
    }

    {
    // Hi-Hi
    SCOPED_TRACE("");
    doDAA(cpu,
          hiLower, hiUpper, error,
          C_before, H_before, C_after);
    }
}

// Page 95
TEST_F(TestCpu, DAA_Case_01) {
    unsigned char lowUpper = 0x00;
    unsigned char midUpper = 0x50;
    unsigned char hiUpper  = 0x90;

    unsigned char lowLower = 0x00;
    unsigned char midLower = 0x05;
    unsigned char hiLower  = 0x09;

    unsigned char error = 0x00;

    bool C_before = false;
    bool H_before = false;
    bool C_after  = false;
    
    SCOPED_TRACE("");
    testDAA(cpu,
            lowLower, midLower, hiLower,
            lowUpper, midUpper, hiUpper,
            error,
            C_before, H_before, C_after);
}

// Page 95
TEST_F(TestCpu, DAA_Case_02) {
    unsigned char lowUpper = 0x00;
    unsigned char midUpper = 0x40;
    unsigned char hiUpper  = 0x80;

    unsigned char lowLower = 0x0A;
    unsigned char midLower = 0x0C;
    unsigned char hiLower  = 0x0F;

    unsigned char error = 0x06;

    bool C_before = false;
    bool H_before = false;
    bool C_after  = false;

    SCOPED_TRACE("");
    testDAA(cpu,
            lowLower, midLower, hiLower,
            lowUpper, midUpper, hiUpper,
            error,
            C_before, H_before, C_after);
}

// Page 95
TEST_F(TestCpu, DAA_Case_03) {
    unsigned char lowUpper = 0x00;
    unsigned char midUpper = 0x40;
    unsigned char hiUpper  = 0x90;

    unsigned char lowLower = 0x00;
    unsigned char midLower = 0x02;
    unsigned char hiLower  = 0x03;

    unsigned char error = 0x06;

    bool C_before = false;
    bool H_before = true;
    bool C_after  = false;

    SCOPED_TRACE("");
    testDAA(cpu,
            lowLower, midLower, hiLower,
            lowUpper, midUpper, hiUpper,
            error,
            C_before, H_before, C_after);
}

// Page 95
TEST_F(TestCpu, DAA_Case_04) {
    unsigned char lowUpper = 0xA0;
    unsigned char midUpper = 0xC0;
    unsigned char hiUpper  = 0xF0;

    unsigned char lowLower = 0x00;
    unsigned char midLower = 0x05;
    unsigned char hiLower  = 0x09;

    unsigned char error = 0x60;

    bool C_before = false;
    bool H_before = false;
    bool C_after  = true;

    SCOPED_TRACE("");
    testDAA(cpu,
            lowLower, midLower, hiLower,
            lowUpper, midUpper, hiUpper,
            error,
            C_before, H_before, C_after);
}

// Page 95
TEST_F(TestCpu, DAA_Case_05) {
    unsigned char lowUpper = 0x90;
    unsigned char midUpper = 0xC0;
    unsigned char hiUpper  = 0xF0;

    unsigned char lowLower = 0x0A;
    unsigned char midLower = 0x0C;
    unsigned char hiLower  = 0x0F;

    unsigned char error = 0x66;

    bool C_before = false;
    bool H_before = false;
    bool C_after  = true;

    SCOPED_TRACE("");
    testDAA(cpu,
            lowLower, midLower, hiLower,
            lowUpper, midUpper, hiUpper,
            error,
            C_before, H_before, C_after);
}

// Page 95
TEST_F(TestCpu, DAA_Case_06) {
    unsigned char lowUpper = 0xA0;
    unsigned char midUpper = 0xC0;
    unsigned char hiUpper  = 0xF0;

    unsigned char lowLower = 0x00;
    unsigned char midLower = 0x02;
    unsigned char hiLower  = 0x03;

    unsigned char error = 0x66;

    bool C_before = false;
    bool H_before = true;
    bool C_after  = true;

    SCOPED_TRACE("");
    testDAA(cpu,
            lowLower, midLower, hiLower,
            lowUpper, midUpper, hiUpper,
            error,
            C_before, H_before, C_after);
}

// Page 95
TEST_F(TestCpu, DAA_Case_07) {
    unsigned char lowUpper = 0x00;
    unsigned char midUpper = 0x10;
    unsigned char hiUpper  = 0x20;

    unsigned char lowLower = 0x00;
    unsigned char midLower = 0x05;
    unsigned char hiLower  = 0x09;

    unsigned char error = 0x60;

    bool C_before = true;
    bool H_before = false;
    bool C_after  = true;

    SCOPED_TRACE("");
    testDAA(cpu,
            lowLower, midLower, hiLower,
            lowUpper, midUpper, hiUpper,
            error,
            C_before, H_before, C_after);
}

// Page 95
TEST_F(TestCpu, DAA_Case_08) {
    unsigned char lowUpper = 0x00;
    unsigned char midUpper = 0x10;
    unsigned char hiUpper  = 0x20;

    unsigned char lowLower = 0x0A;
    unsigned char midLower = 0x0C;
    unsigned char hiLower  = 0x0F;

    unsigned char error = 0x66;

    bool C_before = true;
    bool H_before = false;
    bool C_after  = true;

    SCOPED_TRACE("");
    testDAA(cpu,
            lowLower, midLower, hiLower,
            lowUpper, midUpper, hiUpper,
            error,
            C_before, H_before, C_after);
}

// Page 95
TEST_F(TestCpu, DAA_Case_09) {
    unsigned char lowUpper = 0x00;
    unsigned char midUpper = 0x10;
    unsigned char hiUpper  = 0x30;

    unsigned char lowLower = 0x00;
    unsigned char midLower = 0x02;
    unsigned char hiLower  = 0x03;

    unsigned char error = 0x66;

    bool C_before = true;
    bool H_before = true;
    bool C_after  = true;

    SCOPED_TRACE("");
    testDAA(cpu,
            lowLower, midLower, hiLower,
            lowUpper, midUpper, hiUpper,
            error,
            C_before, H_before, C_after);
}

// Page 95
TEST_F(TestCpu, DAA_Case_10) {
    // Same as 01 but left in for completeness
    unsigned char lowUpper = 0x00;
    unsigned char midUpper = 0x50;
    unsigned char hiUpper  = 0x90;

    unsigned char lowLower = 0x00;
    unsigned char midLower = 0x05;
    unsigned char hiLower  = 0x09;

    unsigned char error = 0x00;

    bool C_before = false;
    bool H_before = false;
    bool C_after  = false;

    SCOPED_TRACE("");
    testDAA(cpu,
            lowLower, midLower, hiLower,
            lowUpper, midUpper, hiUpper,
            error,
            C_before, H_before, C_after);
}

// Page 95
TEST_F(TestCpu, DAA_Case_11) {
    // Same as 01 but left in for completeness
    unsigned char lowUpper = 0x00;
    unsigned char midUpper = 0x40;
    unsigned char hiUpper  = 0x80;

    unsigned char lowLower = 0x06;
    unsigned char midLower = 0x0A;
    unsigned char hiLower  = 0x0F;

    unsigned char error = 0xFA;

    bool C_before = false;
    bool H_before = true;
    bool C_after  = false;

    SCOPED_TRACE("");
    testDAA(cpu,
            lowLower, midLower, hiLower,
            lowUpper, midUpper, hiUpper,
            error,
            C_before, H_before, C_after);
}

// Page 95
TEST_F(TestCpu, DAA_Case_12) {
    // Same as 01 but left in for completeness
    unsigned char lowUpper = 0x70;
    unsigned char midUpper = 0x90;
    unsigned char hiUpper  = 0xF0;

    unsigned char lowLower = 0x00;
    unsigned char midLower = 0x05;
    unsigned char hiLower  = 0x09;

    unsigned char error = 0xA0;

    bool C_before = true;
    bool H_before = false;
    bool C_after  = true;

    SCOPED_TRACE("");
    testDAA(cpu,
            lowLower, midLower, hiLower,
            lowUpper, midUpper, hiUpper,
            error,
            C_before, H_before, C_after);
}

// Page 95
TEST_F(TestCpu, DAA_Case_13) {
    // Same as 01 but left in for completeness
    unsigned char lowUpper = 0x60;
    unsigned char midUpper = 0x90;
    unsigned char hiUpper  = 0xF0;

    unsigned char lowLower = 0x06;
    unsigned char midLower = 0x0A;
    unsigned char hiLower  = 0x0F;

    unsigned char error = 0x9A;

    bool C_before = true;
    bool H_before = true;
    bool C_after  = true;

    SCOPED_TRACE("");
    testDAA(cpu,
            lowLower, midLower, hiLower,
            lowUpper, midUpper, hiUpper,
            error,
            C_before, H_before, C_after);
}

// Page 95
TEST_F(TestCpu, CPL_A) {
    unsigned char arg1;
    unsigned char arg2;

    bool OLD_Z;
    bool OLD_C;

    OLD_Z = cpu.flag.Z;
    OLD_C = cpu.flag.C;
    cpu.A = 0x00;
    cpu.execute(0x2F, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(OLD_C, cpu.flag.C);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);

    OLD_Z = cpu.flag.Z;
    OLD_C = cpu.flag.C;
    cpu.A = 0x0F;
    cpu.execute(0x2F, arg1, arg2);
    EXPECT_EQ(0xF0, cpu.A);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(OLD_C, cpu.flag.C);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);

    OLD_Z = cpu.flag.Z;
    OLD_C = cpu.flag.C;
    cpu.A = 0xF0;
    cpu.execute(0x2F, arg1, arg2);
    EXPECT_EQ(0x0F, cpu.A);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(OLD_C, cpu.flag.C);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);

    OLD_Z = cpu.flag.Z;
    OLD_C = cpu.flag.C;
    cpu.A = 0xFF;
    cpu.execute(0x2F, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(OLD_C, cpu.flag.C);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);

    OLD_Z = cpu.flag.Z;
    OLD_C = cpu.flag.C;
    cpu.A = 0x5A;
    cpu.execute(0x2F, arg1, arg2);
    EXPECT_EQ(0xA5, cpu.A);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(OLD_C, cpu.flag.C);
    EXPECT_EQ(true, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
}

// Page 96
TEST_F(TestCpu, CCF) {
    unsigned char arg1;
    unsigned char arg2;

    bool OLD_Z;

    OLD_Z = cpu.flag.Z;
    cpu.flag.C = false;
    cpu.execute(0x3F, arg1, arg2);
    EXPECT_EQ(true, cpu.flag.C);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);

    OLD_Z = cpu.flag.Z;
    cpu.flag.C = true;
    cpu.execute(0x3F, arg1, arg2);
    EXPECT_EQ(false, cpu.flag.C);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
}

// Page 96
TEST_F(TestCpu, SCF) {
    unsigned char arg1;
    unsigned char arg2;

    bool OLD_Z;

    OLD_Z = cpu.flag.Z;
    cpu.flag.C = false;
    cpu.execute(0x37, arg1, arg2);
    EXPECT_EQ(true, cpu.flag.C);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);

    OLD_Z = cpu.flag.Z;
    cpu.flag.C = true;
    cpu.execute(0x37, arg1, arg2);
    EXPECT_EQ(true, cpu.flag.C);
    EXPECT_EQ(OLD_Z, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
}

// Page 97
TEST_F(TestCpu, NOP) {
    // I decided to use this test to confirm that operations
    // in general don't corrupt the state of the cpu.

    unsigned char arg1 = 0x00;
    unsigned char arg2 = 0x00;

    bool OLD_flag_Z = cpu.flag.Z;
    bool OLD_flag_H = cpu.flag.H;
    bool OLD_flag_N = cpu.flag.N;
    bool OLD_flag_C = cpu.flag.C;

    unsigned char OLD_A = cpu.A;
    unsigned char OLD_B = cpu.B;
    unsigned char OLD_C = cpu.C;
    unsigned char OLD_D = cpu.D;
    unsigned char OLD_E = cpu.E;
    unsigned char OLD_F = cpu.F;
    unsigned char OLD_H = cpu.H;
    unsigned char OLD_L = cpu.L;

    unsigned short OLD_SP = cpu.SP;
    unsigned short OLD_PC = cpu.PC;

    cpu.execute(0x00, arg1, arg2);

    EXPECT_EQ(0x00, arg1);
    EXPECT_EQ(0x00, arg2);

    EXPECT_EQ(OLD_flag_Z, cpu.flag.Z);
    EXPECT_EQ(OLD_flag_H, cpu.flag.H);
    EXPECT_EQ(OLD_flag_N, cpu.flag.N);
    EXPECT_EQ(OLD_flag_C, cpu.flag.C);

    EXPECT_EQ(OLD_A, cpu.A);
    EXPECT_EQ(OLD_B, cpu.B);
    EXPECT_EQ(OLD_C, cpu.C);
    EXPECT_EQ(OLD_D, cpu.D);
    EXPECT_EQ(OLD_E, cpu.E);
    EXPECT_EQ(OLD_F, cpu.F);
    EXPECT_EQ(OLD_H, cpu.H);
    EXPECT_EQ(OLD_L, cpu.L);

    EXPECT_EQ(OLD_SP, cpu.SP);
    EXPECT_EQ(OLD_PC + 1, cpu.PC);
}

// Page 97
TEST_F(TestCpu, not_HALT_or_STOP) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.memory()[0xFFFF] = 0x00;
    EXPECT_EQ(CPU::CONTINUE_EXECUTION, cpu.execute(0x00, arg1, arg2));
    EXPECT_NE(CPU::HALT_EXECUTION, cpu.execute(0x00, arg1, arg2));
    EXPECT_NE(CPU::STOP_EXECUTION, cpu.execute(0x00, arg1, arg2));

    cpu.memory()[0xFFFF] = 0xFF;
    EXPECT_EQ(CPU::CONTINUE_EXECUTION, cpu.execute(0x00, arg1, arg2));
    EXPECT_NE(CPU::HALT_EXECUTION, cpu.execute(0x00, arg1, arg2));
    EXPECT_NE(CPU::STOP_EXECUTION, cpu.execute(0x00, arg1, arg2));
}

// Page 97
TEST_F(TestCpu, HALT) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.memory()[0xFFFF] = 0x00;
    EXPECT_EQ(CPU::CONTINUE_EXECUTION, cpu.execute(0x76, arg1, arg2));
    EXPECT_NE(CPU::HALT_EXECUTION, cpu.execute(0x76, arg1, arg2));
    EXPECT_NE(CPU::STOP_EXECUTION, cpu.execute(0x76, arg1, arg2));

    cpu.memory()[0xFFFF] = 0xFF;
    EXPECT_NE(CPU::CONTINUE_EXECUTION, cpu.execute(0x76, arg1, arg2));
    EXPECT_EQ(CPU::HALT_EXECUTION, cpu.execute(0x76, arg1, arg2));
    EXPECT_NE(CPU::STOP_EXECUTION, cpu.execute(0x76, arg1, arg2));
}

// Page 97
TEST_F(TestCpu, STOP) {
    unsigned char arg1;
    unsigned char arg2;

    arg1 = 0x00;

    cpu.memory()[0xFFFF] = 0x00;
    EXPECT_EQ(CPU::CONTINUE_EXECUTION, cpu.execute(0x10, arg1, arg2));
    EXPECT_NE(CPU::HALT_EXECUTION, cpu.execute(0x10, arg1, arg2));
    EXPECT_NE(CPU::STOP_EXECUTION, cpu.execute(0x10, arg1, arg2));

    cpu.memory()[0xFFFF] = 0xFF;
    EXPECT_NE(CPU::CONTINUE_EXECUTION, cpu.execute(0x10, arg1, arg2));
    EXPECT_NE(CPU::HALT_EXECUTION, cpu.execute(0x10, arg1, arg2));
    EXPECT_EQ(CPU::STOP_EXECUTION, cpu.execute(0x10, arg1, arg2));
}

// Page 98
TEST_F(TestCpu, DI) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.memory()[0xFFFF] = 0x00;
    cpu.execute(0xF3, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0xFFFF]);

    cpu.memory()[0xFFFF] = 0xFF;
    cpu.execute(0xF3, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0xFFFF]);
}

// Page 98
TEST_F(TestCpu, EI) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.memory()[0xFFFF] = 0x00;
    cpu.execute(0xFB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.memory()[0xFFFF]);

    cpu.memory()[0xFFFF] = 0xFF;
    cpu.execute(0xFB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.memory()[0xFFFF]);
}

// Page 99
TEST_F(TestCpu, RLCA) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.flag.C = false;
    cpu.A = 0x00;
    cpu.execute(0x07, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x01;
    cpu.execute(0x07, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x08;
    cpu.execute(0x07, arg1, arg2);
    EXPECT_EQ(0x10, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x0F;
    cpu.execute(0x07, arg1, arg2);
    EXPECT_EQ(0x1E, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x10;
    cpu.execute(0x07, arg1, arg2);
    EXPECT_EQ(0x20, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x80;
    cpu.execute(0x07, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x00;
    cpu.execute(0x07, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x01;
    cpu.execute(0x07, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x80;
    cpu.execute(0x07, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0xFF;
    cpu.execute(0x07, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 99
TEST_F(TestCpu, RLA) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.flag.C = false;
    cpu.A = 0x00;
    cpu.execute(0x17, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x01;
    cpu.execute(0x17, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x08;
    cpu.execute(0x17, arg1, arg2);
    EXPECT_EQ(0x10, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x0F;
    cpu.execute(0x17, arg1, arg2);
    EXPECT_EQ(0x1E, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x10;
    cpu.execute(0x17, arg1, arg2);
    EXPECT_EQ(0x20, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x80;
    cpu.execute(0x17, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x00;
    cpu.execute(0x17, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x01;
    cpu.execute(0x17, arg1, arg2);
    EXPECT_EQ(0x03, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x80;
    cpu.execute(0x17, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0xFF;
    cpu.execute(0x17, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0xFF;
    cpu.execute(0x17, arg1, arg2);
    EXPECT_EQ(0xFE, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 100
TEST_F(TestCpu, RRCA) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.flag.C = false;
    cpu.A = 0x00;
    cpu.execute(0x0F, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x80;
    cpu.execute(0x0F, arg1, arg2);
    EXPECT_EQ(0x40, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x10;
    cpu.execute(0x0F, arg1, arg2);
    EXPECT_EQ(0x08, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0xF0;
    cpu.execute(0x0F, arg1, arg2);
    EXPECT_EQ(0x78, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x08;
    cpu.execute(0x0F, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x01;
    cpu.execute(0x0F, arg1, arg2);
    EXPECT_EQ(0x80, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x00;
    cpu.execute(0x0F, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x80;
    cpu.execute(0x0F, arg1, arg2);
    EXPECT_EQ(0x40, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x01;
    cpu.execute(0x0F, arg1, arg2);
    EXPECT_EQ(0x80, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0xFF;
    cpu.execute(0x0F, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 100
TEST_F(TestCpu, RRA) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.flag.C = false;
    cpu.A = 0x00;
    cpu.execute(0x1F, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x80;
    cpu.execute(0x1F, arg1, arg2);
    EXPECT_EQ(0x40, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x10;
    cpu.execute(0x1F, arg1, arg2);
    EXPECT_EQ(0x08, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0xF0;
    cpu.execute(0x1F, arg1, arg2);
    EXPECT_EQ(0x78, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x08;
    cpu.execute(0x1F, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x01;
    cpu.execute(0x1F, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x00;
    cpu.execute(0x1F, arg1, arg2);
    EXPECT_EQ(0x80, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x80;
    cpu.execute(0x1F, arg1, arg2);
    EXPECT_EQ(0xC0, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x01;
    cpu.execute(0x1F, arg1, arg2);
    EXPECT_EQ(0x80, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0xFF;
    cpu.execute(0x1F, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 101
TEST_F(TestCpu, RLC_n) {
    // For the sake of brevity, only a single case from each OP Code has been
    // tested. The full functionality was tested in RCLA:  all this test is
    // really checking for is correct "wiring".

    unsigned char arg1;
    unsigned char arg2;

    cpu.flag.C = false;
    cpu.A = 0x00;
    arg1 = 0x07;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.B = 0x01;
    arg1 = 0x00;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.C = 0x08;
    arg1 = 0x01;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.D = 0x0F;
    arg1 = 0x02;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x1E, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.E = 0x10;
    arg1 = 0x03;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.H = 0x80;
    arg1 = 0x04;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.L = 0x00;
    arg1 = 0x05;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x01;
    arg1 = 0x06;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x02, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 102
TEST_F(TestCpu, RL_n) {
    // For the sake of brevity, only a single case from each OP Code has been
    // tested. The full functionality was tested in RLA:  all this test is
    // really checking for is correct "wiring".
    unsigned char arg1;
    unsigned char arg2;

    cpu.flag.C = false;
    cpu.A = 0x00;
    arg1 = 0x17;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.B = 0x01;
    arg1 = 0x10;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.C = 0x08;
    arg1 = 0x11;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.D = 0x0F;
    arg1 = 0x12;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x1E, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.E = 0x10;
    arg1 = 0x13;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.H = 0x80;
    arg1 = 0x14;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.L = 0x00;
    arg1 = 0x15;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x01;
    arg1 = 0x16;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x03, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 103
TEST_F(TestCpu, RRC_n) {
    // For the sake of brevity, only a single case from each OP Code has been
    // tested. The full functionality was tested in RLA:  all this test is
    // really checking for is correct "wiring".
    unsigned char arg1;
    unsigned char arg2;

    cpu.flag.C = false;
    cpu.A = 0x00;
    arg1 = 0x0F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.B = 0x80;
    arg1 = 0x08;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.C = 0x10;
    arg1 = 0x09;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.D = 0xF0;
    arg1 = 0x0A;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x78, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.E = 0x08;
    arg1 = 0x0B;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.H = 0x01;
    arg1 = 0x0C;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.L = 0x00;
    arg1 = 0x0D;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x80;
    arg1 = 0x0E;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x40, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 104
TEST_F(TestCpu, RR_n) {
    // For the sake of brevity, only a single case from each OP Code has been
    // tested. The full functionality was tested in RLA:  all this test is
    // really checking for is correct "wiring".
    unsigned char arg1;
    unsigned char arg2;

    cpu.flag.C = false;
    cpu.A = 0x00;
    arg1 = 0x1F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.B = 0x80;
    arg1 = 0x18;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.C = 0x10;
    arg1 = 0x19;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.D = 0xF0;
    arg1 = 0x1A;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x78, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.E = 0x08;
    arg1 = 0x1B;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.H = 0x01;
    arg1 = 0x1C;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.L = 0x00;
    arg1 = 0x1D;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x80;
    arg1 = 0x1E;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0xC0, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 105
TEST_F(TestCpu, SLA_A) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.flag.C = false;
    cpu.A = 0x00;
    arg1 = 0x27;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x01;
    arg1 = 0x27;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x08;
    arg1 = 0x27;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x0F;
    arg1 = 0x27;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x1E, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x10;
    arg1 = 0x27;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x80;
    arg1 = 0x27;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x00;
    arg1 = 0x27;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x01;
    arg1 = 0x27;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x80;
    arg1 = 0x27;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0xFF;
    arg1 = 0x27;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFE, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0xFF;
    arg1 = 0x27;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFE, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 105
TEST_F(TestCpu, SLA_n) {
    // Brevity - one test case - see previous test
    unsigned char arg1;
    unsigned char arg2;

    cpu.flag.C = false;
    cpu.A = 0x00;
    arg1 = 0x27;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.B = 0x01;
    arg1 = 0x20;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.C = 0x08;
    arg1 = 0x21;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.D = 0x0F;
    arg1 = 0x22;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x1E, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.E = 0x10;
    arg1 = 0x23;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.H = 0x80;
    arg1 = 0x24;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.L = 0x00;
    arg1 = 0x25;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x01;
    arg1 = 0x26;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x02, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 106
TEST_F(TestCpu, SRA_A) {
    // Note SRA is Shift Right Arithmetic, it leaves the Most Significant bit
    // unchanged as it is assumed this bit is a sign bit.
    unsigned char arg1;
    unsigned char arg2;

    cpu.flag.C = false;
    cpu.A = 0x00;
    arg1 = 0x2F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x80;
    arg1 = 0x2F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xC0, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x10;
    arg1 = 0x2F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0xF0;
    arg1 = 0x2F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xF8, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x08;
    arg1 = 0x2F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x01;
    arg1 = 0x2F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x00;
    arg1 = 0x2F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x80;
    arg1 = 0x2F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xC0, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x01;
    arg1 = 0x2F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0xFF;
    arg1 = 0x2F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0xFF;
    arg1 = 0x2F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 106
TEST_F(TestCpu, SRA_n) {
    // Brevity - One test case - See Previous test
    unsigned char arg1;
    unsigned char arg2;

    cpu.flag.C = false;
    cpu.A = 0x00;
    arg1 = 0x2F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.B = 0x80;
    arg1 = 0x28;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xC0, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.C = 0x10;
    arg1 = 0x29;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.D = 0xF0;
    arg1 = 0x2A;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xF8, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.E = 0x08;
    arg1 = 0x2B;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.H = 0x01;
    arg1 = 0x2C;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.L = 0x00;
    arg1 = 0x2D;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x80;
    arg1 = 0x2E;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0xC0, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 107
TEST_F(TestCpu, SRL_A) {
    // Note SRL is Shift Right Logical, it is the opposite of SLA...
    unsigned char arg1;
    unsigned char arg2;

    cpu.flag.C = false;
    cpu.A = 0x00;
    arg1 = 0x3F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x80;
    arg1 = 0x3F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x10;
    arg1 = 0x3F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0xF0;
    arg1 = 0x3F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x78, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x08;
    arg1 = 0x3F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0x01;
    arg1 = 0x3F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x00;
    arg1 = 0x3F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x80;
    arg1 = 0x3F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0x01;
    arg1 = 0x3F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.A = 0xFF;
    arg1 = 0x3F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x7F, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = false;
    cpu.A = 0xFF;
    arg1 = 0x3F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x7F, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);
}

// Page 107
TEST_F(TestCpu, SRL_n) {
    // Brevity - One test case - See Previous test
    unsigned char arg1;
    unsigned char arg2;

    cpu.flag.C = false;
    cpu.A = 0x00;
    arg1 = 0x3F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.B = 0x80;
    arg1 = 0x38;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.C = 0x10;
    arg1 = 0x39;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.D = 0xF0;
    arg1 = 0x3A;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x78, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.E = 0x08;
    arg1 = 0x3B;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = false;
    cpu.H = 0x01;
    arg1 = 0x3C;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(true, cpu.flag.C);

    cpu.flag.C = true;
    cpu.L = 0x00;
    arg1 = 0x3D;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);

    cpu.flag.C = true;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x80;
    arg1 = 0x3E;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(0x40, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(false, cpu.flag.H);
    EXPECT_EQ(false, cpu.flag.C);
}

// Page 108
TEST_F(TestCpu, BIT_b_A) {
    // I like the idea of writing these tests in functions to avoid repetition,
    // but it makes it far too difficult to see exactly what is failing
    // -- Viva la Repetition!

    unsigned char arg1;
    unsigned char arg2;

    bool OLD_C;

    // ============================== BIT ZERO ===============================
    // All OFF
    OLD_C = cpu.flag.C;
    cpu.A = 0x00;
    arg1 = 0x47;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // All ON
    OLD_C = cpu.flag.C;
    cpu.A = 0xFF;
    arg1 = 0x47;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // Zero ON
    OLD_C = cpu.flag.C;
    cpu.A = 0x01;
    arg1 = 0x47;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // Others ON
    OLD_C = cpu.flag.C;
    cpu.A = 0xFE;
    arg1 = 0x47;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFE, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // ============================== BIT ONE ================================
    // All OFF
    OLD_C = cpu.flag.C;
    cpu.A = 0x00;
    arg1 = 0x4F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // All ON
    OLD_C = cpu.flag.C;
    cpu.A = 0xFF;
    arg1 = 0x4F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // One ON
    OLD_C = cpu.flag.C;
    cpu.A = 0x02;
    arg1 = 0x4F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // Others ON
    OLD_C = cpu.flag.C;
    cpu.A = 0xFD;
    arg1 = 0x4F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFD, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // ============================== BIT TWO ================================
    // All OFF
    OLD_C = cpu.flag.C;
    cpu.A = 0x00;
    arg1 = 0x57;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // All ON
    OLD_C = cpu.flag.C;
    cpu.A = 0xFF;
    arg1 = 0x57;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // Two ON
    OLD_C = cpu.flag.C;
    cpu.A = 0x04;
    arg1 = 0x57;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // Others ON
    OLD_C = cpu.flag.C;
    cpu.A = 0xFB;
    arg1 = 0x57;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFB, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // ============================== BIT THREE ==============================
    // All OFF
    OLD_C = cpu.flag.C;
    cpu.A = 0x00;
    arg1 = 0x5F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // All ON
    OLD_C = cpu.flag.C;
    cpu.A = 0xFF;
    arg1 = 0x5F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // Three ON
    OLD_C = cpu.flag.C;
    cpu.A = 0x08;
    arg1 = 0x5F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // Others ON
    OLD_C = cpu.flag.C;
    cpu.A = 0xF7;
    arg1 = 0x5F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xF7, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // ============================== BIT FOUR ===============================
    // All OFF
    OLD_C = cpu.flag.C;
    cpu.A = 0x00;
    arg1 = 0x67;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // All ON
    OLD_C = cpu.flag.C;
    cpu.A = 0xFF;
    arg1 = 0x67;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // Four  ON
    OLD_C = cpu.flag.C;
    cpu.A = 0x10;
    arg1 = 0x67;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // Others ON
    OLD_C = cpu.flag.C;
    cpu.A = 0xEF;
    arg1 = 0x67;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xEF, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // ============================== BIT FIVE ===============================
    // All OFF
    OLD_C = cpu.flag.C;
    cpu.A = 0x00;
    arg1 = 0x6F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // All ON
    OLD_C = cpu.flag.C;
    cpu.A = 0xFF;
    arg1 = 0x6F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    //Five ON
    OLD_C = cpu.flag.C;
    cpu.A = 0x20;
    arg1 = 0x6F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // Others ON
    OLD_C = cpu.flag.C;
    cpu.A = 0xDF;
    arg1 = 0x6F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xDF, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // ============================== BIT SIX ================================
    // All OFF
    OLD_C = cpu.flag.C;
    cpu.A = 0x00;
    arg1 = 0x77;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // All ON
    OLD_C = cpu.flag.C;
    cpu.A = 0xFF;
    arg1 = 0x77;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // Six ON
    OLD_C = cpu.flag.C;
    cpu.A = 0x40;
    arg1 = 0x77;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // Others ON
    OLD_C = cpu.flag.C;
    cpu.A = 0xBF;
    arg1 = 0x77;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xBF, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // ============================== BIT SEVEN ==============================
    // All OFF
    OLD_C = cpu.flag.C;
    cpu.A = 0x00;
    arg1 = 0x7F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // All ON
    OLD_C = cpu.flag.C;
    cpu.A = 0xFF;
    arg1 = 0x7F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // Seven ON
    OLD_C = cpu.flag.C;
    cpu.A = 0x80;
    arg1 = 0x7F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.A);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);

    // Others ON
    OLD_C = cpu.flag.C;
    cpu.A = 0x7F;
    arg1 = 0x7F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x7F, cpu.A);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);
    EXPECT_EQ(true, cpu.flag.H);
    EXPECT_EQ(OLD_C, cpu.flag.C);
}

// Page 108
TEST_F(TestCpu, BIT_b_B) {
    // This is not super thorough becuase it is only testing wiring, the actual
    // business logic is tested in BIT_b_A.
    unsigned char arg1;
    unsigned char arg2;

    // ============================== BIT ZERO ===============================
    // OFF
    cpu.B = 0x00;
    arg1 = 0x40;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.B = 0x01;
    arg1 = 0x40;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT ONE ================================
    // OFF
    cpu.B = 0x00;
    arg1 = 0x48;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.B = 0x02;
    arg1 = 0x48;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT TWO ================================
    // OFF
    cpu.B = 0x00;
    arg1 = 0x50;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.B = 0x04;
    arg1 = 0x50;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT THREE ==============================
    // OFF
    cpu.B = 0x00;
    arg1 = 0x58;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.B = 0x08;
    arg1 = 0x58;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT FOUR ===============================
    // OFF
    cpu.B = 0x00;
    arg1 = 0x60;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.B = 0x10;
    arg1 = 0x60;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT FIVE ===============================
    // OFF
    cpu.B = 0x00;
    arg1 = 0x68;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.B = 0x20;
    arg1 = 0x68;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT SIX ================================
    // OFF
    cpu.B = 0x00;
    arg1 = 0x70;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.B = 0x40;
    arg1 = 0x70;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT SEVEN ==============================
    // OFF
    cpu.B = 0x00;
    arg1 = 0x78;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.B = 0x80;
    arg1 = 0x78;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.B);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);
}

// Page 108
TEST_F(TestCpu, BIT_b_C) {
    // This is not super thorough becuase it is only testing wiring, the actual
    // business logic is tested in BIT_b_A.
    unsigned char arg1;
    unsigned char arg2;

    // ============================== BIT ZERO ===============================
    // OFF
    cpu.C = 0x00;
    arg1 = 0x41;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.C = 0x01;
    arg1 = 0x41;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT ONE ================================
    // OFF
    cpu.C = 0x00;
    arg1 = 0x49;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.C = 0x02;
    arg1 = 0x49;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT TWO ================================
    // OFF
    cpu.C = 0x00;
    arg1 = 0x51;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.C = 0x04;
    arg1 = 0x51;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT THREE ==============================
    // OFF
    cpu.C = 0x00;
    arg1 = 0x59;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.C = 0x08;
    arg1 = 0x59;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT FOUR ===============================
    // OFF
    cpu.C = 0x00;
    arg1 = 0x61;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.C = 0x10;
    arg1 = 0x61;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT FIVE ===============================
    // OFF
    cpu.C = 0x00;
    arg1 = 0x69;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.C = 0x20;
    arg1 = 0x69;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT SIX ================================
    // OFF
    cpu.C = 0x00;
    arg1 = 0x71;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.C = 0x40;
    arg1 = 0x71;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT SEVEN ==============================
    // OFF
    cpu.C = 0x00;
    arg1 = 0x79;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.C = 0x80;
    arg1 = 0x79;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.C);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);
}

// Page 108
TEST_F(TestCpu, BIT_b_D) {
    // This is not super thorough becuase it is only testing wiring, the actual
    // business logic is tested in BIT_b_A.
    unsigned char arg1;
    unsigned char arg2;

    // ============================== BIT ZERO ===============================
    // OFF
    cpu.D = 0x00;
    arg1 = 0x42;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.D = 0x01;
    arg1 = 0x42;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT ONE ================================
    // OFF
    cpu.D = 0x00;
    arg1 = 0x4A;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.D = 0x02;
    arg1 = 0x4A;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT TWO ================================
    // OFF
    cpu.D = 0x00;
    arg1 = 0x52;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.D = 0x04;
    arg1 = 0x52;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT THREE ==============================
    // OFF
    cpu.D = 0x00;
    arg1 = 0x5A;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.D = 0x08;
    arg1 = 0x5A;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT FOUR ===============================
    // OFF
    cpu.D = 0x00;
    arg1 = 0x62;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.D = 0x10;
    arg1 = 0x62;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT FIVE ===============================
    // OFF
    cpu.D = 0x00;
    arg1 = 0x6A;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.D = 0x20;
    arg1 = 0x6A;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT SIX ================================
    // OFF
    cpu.D = 0x00;
    arg1 = 0x72;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.D = 0x40;
    arg1 = 0x72;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT SEVEN ==============================
    // OFF
    cpu.D = 0x00;
    arg1 = 0x7A;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.D = 0x80;
    arg1 = 0x7A;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.D);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);
}

// Page 108
TEST_F(TestCpu, BIT_b_E) {
    // This is not super thorough becuase it is only testing wiring, the actual
    // business logic is tested in BIT_b_A.
    unsigned char arg1;
    unsigned char arg2;

    // ============================== BIT ZERO ===============================
    // OFF
    cpu.E = 0x00;
    arg1 = 0x43;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.E = 0x01;
    arg1 = 0x43;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT ONE ================================
    // OFF
    cpu.E = 0x00;
    arg1 = 0x4B;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.E = 0x02;
    arg1 = 0x4B;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT TWO ================================
    // OFF
    cpu.E = 0x00;
    arg1 = 0x53;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.E = 0x04;
    arg1 = 0x53;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT THREE ==============================
    // OFF
    cpu.E = 0x00;
    arg1 = 0x5B;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.E = 0x08;
    arg1 = 0x5B;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT FOUR ===============================
    // OFF
    cpu.E = 0x00;
    arg1 = 0x63;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.E = 0x10;
    arg1 = 0x63;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT FIVE ===============================
    // OFF
    cpu.E = 0x00;
    arg1 = 0x6B;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.E = 0x20;
    arg1 = 0x6B;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT SIX ================================
    // OFF
    cpu.E = 0x00;
    arg1 = 0x73;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.E = 0x40;
    arg1 = 0x73;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT SEVEN ==============================
    // OFF
    cpu.E = 0x00;
    arg1 = 0x7B;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.E = 0x80;
    arg1 = 0x7B;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.E);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);
}

// Page 108
TEST_F(TestCpu, BIT_b_H) {
    // This is not super thorough becuase it is only testing wiring, the actual
    // business logic is tested in BIT_b_A.
    unsigned char arg1;
    unsigned char arg2;

    // ============================== BIT ZERO ===============================
    // OFF
    cpu.H = 0x00;
    arg1 = 0x44;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x01;
    arg1 = 0x44;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT ONE ================================
    // OFF
    cpu.H = 0x00;
    arg1 = 0x4C;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x02;
    arg1 = 0x4C;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT TWO ================================
    // OFF
    cpu.H = 0x00;
    arg1 = 0x54;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x04;
    arg1 = 0x54;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT THREE ==============================
    // OFF
    cpu.H = 0x00;
    arg1 = 0x5C;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x08;
    arg1 = 0x5C;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT FOUR ===============================
    // OFF
    cpu.H = 0x00;
    arg1 = 0x64;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x10;
    arg1 = 0x64;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT FIVE ===============================
    // OFF
    cpu.H = 0x00;
    arg1 = 0x6C;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x20;
    arg1 = 0x6C;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT SIX ================================
    // OFF
    cpu.H = 0x00;
    arg1 = 0x74;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x40;
    arg1 = 0x74;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT SEVEN ==============================
    // OFF
    cpu.H = 0x00;
    arg1 = 0x7C;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x80;
    arg1 = 0x7C;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.H);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);
}

// Page 108
TEST_F(TestCpu, BIT_b_L) {
    // This is not super thorough becuase it is only testing wiring, the actual
    // business logic is tested in BIT_b_A.
    unsigned char arg1;
    unsigned char arg2;

    // ============================== BIT ZERO ===============================
    // OFF
    cpu.L = 0x00;
    arg1 = 0x45;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.L = 0x01;
    arg1 = 0x45;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT ONE ================================
    // OFF
    cpu.L = 0x00;
    arg1 = 0x4D;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.L = 0x02;
    arg1 = 0x4D;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT TWO ================================
    // OFF
    cpu.L = 0x00;
    arg1 = 0x55;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.L = 0x04;
    arg1 = 0x55;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT THREE ==============================
    // OFF
    cpu.L = 0x00;
    arg1 = 0x5D;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.L = 0x08;
    arg1 = 0x5D;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT FOUR ===============================
    // OFF
    cpu.L = 0x00;
    arg1 = 0x65;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.L = 0x10;
    arg1 = 0x65;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT FIVE ===============================
    // OFF
    cpu.L = 0x00;
    arg1 = 0x6D;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.L = 0x20;
    arg1 = 0x6D;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT SIX ================================
    // OFF
    cpu.L = 0x00;
    arg1 = 0x75;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.L = 0x40;
    arg1 = 0x75;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT SEVEN ==============================
    // OFF
    cpu.L = 0x00;
    arg1 = 0x7D;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.L = 0x80;
    arg1 = 0x7D;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.L);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);
}

// Page 108
TEST_F(TestCpu, BIT_b_HL) {
    // This is not super thorough becuase it is only testing wiring, the actual
    // business logic is tested in BIT_b_A.
    unsigned char arg1;
    unsigned char arg2;

    // ============================== BIT ZERO ===============================
    // OFF
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0x46;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x01;
    arg1 = 0x46;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT ONE ================================
    // OFF
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0x4E;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x02;
    arg1 = 0x4E;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT TWO ================================
    // OFF
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0x56;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x04;
    arg1 = 0x56;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT THREE ==============================
    // OFF
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0x5E;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x08;
    arg1 = 0x5E;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT FOUR ===============================
    // OFF
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0x66;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x10;
    arg1 = 0x66;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT FIVE ===============================
    // OFF
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0x6E;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x20;
    arg1 = 0x6E;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT SIX ===============================
    // OFF
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0x76;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x40;
    arg1 = 0x76;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);

    // ============================== BIT SEVEN ===============================
    // OFF
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0x7E;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);
    EXPECT_EQ(true, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N); EXPECT_EQ(true, cpu.flag.H);

    // ON
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x80;
    arg1 = 0x7E;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.memory()[0x0001]);
    EXPECT_EQ(false, cpu.flag.Z);
    EXPECT_EQ(false, cpu.flag.N);  EXPECT_EQ(true, cpu.flag.H);
}

// Page 109
TEST_F(TestCpu, SET_b_A) {
    // Set_b_A is overly thorough, so the others don't have to be...
    // That's the theory at least :)

    unsigned char arg1;
    unsigned char arg2;

    // ============================ NOT SET ==================================
    cpu.A = 0x00;
    arg1 = 0xC7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);

    cpu.A = 0x00;
    arg1 = 0xCF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);

    cpu.A = 0x00;
    arg1 = 0xD7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);

    cpu.A = 0x00;
    arg1 = 0xDF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.A);

    cpu.A = 0x00;
    arg1 = 0xE7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.A);

    cpu.A = 0x00;
    arg1 = 0xEF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.A);

    cpu.A = 0x00;
    arg1 = 0xF7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.A);

    cpu.A = 0x00;
    arg1 = 0xFF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.A);

    // ============================== SET ====================================
    cpu.A = 0x01;
    arg1 = 0xC7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.A);

    cpu.A = 0x02;
    arg1 = 0xCF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.A);

    cpu.A = 0x04;
    arg1 = 0xD7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.A);

    cpu.A = 0x08;
    arg1 = 0xDF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.A);

    cpu.A = 0x10;
    arg1 = 0xE7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.A);

    cpu.A = 0x20;
    arg1 = 0xEF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.A);

    cpu.A = 0x40;
    arg1 = 0xF7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.A);

    cpu.A = 0x80;
    arg1 = 0xFF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.A);

    // ========================== ALL SET ====================================
    cpu.A = 0xFF;
    arg1 = 0xC7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);

    cpu.A = 0xFF;
    arg1 = 0xCF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);

    cpu.A = 0xFF;
    arg1 = 0xD7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);

    cpu.A = 0xFF;
    arg1 = 0xDF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);

    cpu.A = 0xFF;
    arg1 = 0xE7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);

    cpu.A = 0xFF;
    arg1 = 0xEF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);

    cpu.A = 0xFF;
    arg1 = 0xF7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);

    cpu.A = 0xFF;
    arg1 = 0xFF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);

    // ======================= OTHERS SET ====================================
    cpu.A = 0xFE;
    arg1 = 0xC7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);

    cpu.A = 0xFD;
    arg1 = 0xCF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);

    cpu.A = 0xFB;
    arg1 = 0xD7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);

    cpu.A = 0xF7;
    arg1 = 0xDF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);

    cpu.A = 0xEF;
    arg1 = 0xE7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);

    cpu.A = 0xDF;
    arg1 = 0xEF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);

    cpu.A = 0xBF;
    arg1 = 0xF7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);

    cpu.A = 0x7F;
    arg1 = 0xFF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFF, cpu.A);
}

// Page 109
TEST_F(TestCpu, SET_b_B) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.B = 0x00;
    arg1 = 0xC0;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.B);

    cpu.B = 0x00;
    arg1 = 0xC8;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.B);

    cpu.B = 0x00;
    arg1 = 0xD0;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.B);

    cpu.B = 0x00;
    arg1 = 0xD8;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.B);

    cpu.B = 0x00;
    arg1 = 0xE0;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.B);

    cpu.B = 0x00;
    arg1 = 0xE8;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.B);

    cpu.B = 0x00;
    arg1 = 0xF0;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.B);

    cpu.B = 0x00;
    arg1 = 0xF8;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.B);
}

// Page 109
TEST_F(TestCpu, SET_b_C) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.C = 0x00;
    arg1 = 0xC1;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.C);

    cpu.C = 0x00;
    arg1 = 0xC9;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.C);

    cpu.C = 0x00;
    arg1 = 0xD1;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.C);

    cpu.C = 0x00;
    arg1 = 0xD9;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.C);

    cpu.C = 0x00;
    arg1 = 0xE1;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.C);

    cpu.C = 0x00;
    arg1 = 0xE9;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.C);

    cpu.C = 0x00;
    arg1 = 0xF1;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.C);

    cpu.C = 0x00;
    arg1 = 0xF9;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.C);
}

// Page 109
TEST_F(TestCpu, SET_b_D) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.D = 0x00;
    arg1 = 0xC2;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.D);

    cpu.D = 0x00;
    arg1 = 0xCA;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.D);

    cpu.D = 0x00;
    arg1 = 0xD2;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.D);

    cpu.D = 0x00;
    arg1 = 0xDA;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.D);

    cpu.D = 0x00;
    arg1 = 0xE2;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.D);

    cpu.D = 0x00;
    arg1 = 0xEA;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.D);

    cpu.D = 0x00;
    arg1 = 0xF2;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.D);

    cpu.D = 0x00;
    arg1 = 0xFA;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.D);
}

// Page 109
TEST_F(TestCpu, SET_b_E) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.E = 0x00;
    arg1 = 0xC3;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.E);

    cpu.E = 0x00;
    arg1 = 0xCB;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.E);

    cpu.E = 0x00;
    arg1 = 0xD3;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.E);

    cpu.E = 0x00;
    arg1 = 0xDB;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.E);

    cpu.E = 0x00;
    arg1 = 0xE3;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.E);

    cpu.E = 0x00;
    arg1 = 0xEB;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.E);

    cpu.E = 0x00;
    arg1 = 0xF3;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.E);

    cpu.E = 0x00;
    arg1 = 0xFB;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.E);
}

// Page 109
TEST_F(TestCpu, SET_b_H) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.H = 0x00;
    arg1 = 0xC4;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.H);

    cpu.H = 0x00;
    arg1 = 0xCC;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.H);

    cpu.H = 0x00;
    arg1 = 0xD4;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.H);

    cpu.H = 0x00;
    arg1 = 0xDC;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.H);

    cpu.H = 0x00;
    arg1 = 0xE4;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.H);

    cpu.H = 0x00;
    arg1 = 0xEC;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.H);

    cpu.H = 0x00;
    arg1 = 0xF4;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.H);

    cpu.H = 0x00;
    arg1 = 0xFC;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.H);
}

// Page 109
TEST_F(TestCpu, SET_b_L) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.L = 0x00;
    arg1 = 0xC5;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.L);

    cpu.L = 0x00;
    arg1 = 0xCD;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.L);

    cpu.L = 0x00;
    arg1 = 0xD5;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.L);

    cpu.L = 0x00;
    arg1 = 0xDD;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.L);

    cpu.L = 0x00;
    arg1 = 0xE5;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.L);

    cpu.L = 0x00;
    arg1 = 0xED;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.L);

    cpu.L = 0x00;
    arg1 = 0xF5;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.L);

    cpu.L = 0x00;
    arg1 = 0xFD;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.L);
}

// Page 109
TEST_F(TestCpu, SET_b_HL) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0xC6;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x01, cpu.memory()[0x0001]);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0xCE;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x02, cpu.memory()[0x0001]);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0xD6;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x04, cpu.memory()[0x0001]);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0xDE;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x08, cpu.memory()[0x0001]);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0xE6;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x10, cpu.memory()[0x0001]);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0xEE;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x20, cpu.memory()[0x0001]);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0xF6;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x40, cpu.memory()[0x0001]);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x00;
    arg1 = 0xFE;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x80, cpu.memory()[0x0001]);
}

// Page 110
TEST_F(TestCpu, RES_b_A) {
    // Set_b_A is overly thorough, so the others don't have to be...
    // That's the theory at least :)

    unsigned char arg1;
    unsigned char arg2;

    // ============================ NOT SET ==================================
    cpu.A = 0x00;
    arg1 = 0x87;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    cpu.A = 0x00;
    arg1 = 0x8F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    cpu.A = 0x00;
    arg1 = 0x97;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    cpu.A = 0x00;
    arg1 = 0x9F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    cpu.A = 0x00;
    arg1 = 0xA7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    cpu.A = 0x00;
    arg1 = 0xAF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    cpu.A = 0x00;
    arg1 = 0xB7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    cpu.A = 0x00;
    arg1 = 0xBF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    // ============================== SET ====================================
    cpu.A = 0x01;
    arg1 = 0x87;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    cpu.A = 0x02;
    arg1 = 0x8F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    cpu.A = 0x04;
    arg1 = 0x97;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    cpu.A = 0x08;
    arg1 = 0x9F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    cpu.A = 0x10;
    arg1 = 0xA7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    cpu.A = 0x20;
    arg1 = 0xAF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    cpu.A = 0x40;
    arg1 = 0xB7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    cpu.A = 0x80;
    arg1 = 0xBF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.A);

    // ========================== ALL SET ====================================
    cpu.A = 0xFF;
    arg1 = 0x87;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFE, cpu.A);

    cpu.A = 0xFF;
    arg1 = 0x8F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFD, cpu.A);

    cpu.A = 0xFF;
    arg1 = 0x97;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFB, cpu.A);

    cpu.A = 0xFF;
    arg1 = 0x9F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xF7, cpu.A);

    cpu.A = 0xFF;
    arg1 = 0xA7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xEF, cpu.A);

    cpu.A = 0xFF;
    arg1 = 0xAF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xDF, cpu.A);

    cpu.A = 0xFF;
    arg1 = 0xB7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xBF, cpu.A);

    cpu.A = 0xFF;
    arg1 = 0xBF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x7F, cpu.A);

    // ======================= OTHERS SET ====================================
    cpu.A = 0xFE;
    arg1 = 0x87;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFE, cpu.A);

    cpu.A = 0xFD;
    arg1 = 0x8F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFD, cpu.A);

    cpu.A = 0xFB;
    arg1 = 0x97;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xFB, cpu.A);

    cpu.A = 0xF7;
    arg1 = 0x9F;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xF7, cpu.A);

    cpu.A = 0xEF;
    arg1 = 0xA7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xEF, cpu.A);

    cpu.A = 0xDF;
    arg1 = 0xAF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xDF, cpu.A);

    cpu.A = 0xBF;
    arg1 = 0xB7;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0xBF, cpu.A);

    cpu.A = 0x7F;
    arg1 = 0xBF;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x7F, cpu.A);
}

// Page 110
TEST_F(TestCpu, RES_b_B) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.B = 0x01;
    arg1 = 0x80;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);

    cpu.B = 0x02;
    arg1 = 0x88;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);

    cpu.B = 0x04;
    arg1 = 0x90;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);

    cpu.B = 0x08;
    arg1 = 0x98;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);

    cpu.B = 0x10;
    arg1 = 0xA0;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);

    cpu.B = 0x20;
    arg1 = 0xA8;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);

    cpu.B = 0x40;
    arg1 = 0xB0;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);

    cpu.B = 0x80;
    arg1 = 0xB8;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.B);
}

// Page 110
TEST_F(TestCpu, RES_b_C) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.C = 0x01;
    arg1 = 0x81;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);

    cpu.C = 0x02;
    arg1 = 0x89;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);

    cpu.C = 0x04;
    arg1 = 0x91;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);

    cpu.C = 0x08;
    arg1 = 0x99;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);

    cpu.C = 0x10;
    arg1 = 0xA1;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);

    cpu.C = 0x20;
    arg1 = 0xA9;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);

    cpu.C = 0x40;
    arg1 = 0xB1;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);

    cpu.C = 0x80;
    arg1 = 0xB9;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.C);
}

// Page 110
TEST_F(TestCpu, RES_b_D) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.D = 0x01;
    arg1 = 0x82;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);

    cpu.D = 0x02;
    arg1 = 0x8A;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);

    cpu.D = 0x04;
    arg1 = 0x92;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);

    cpu.D = 0x08;
    arg1 = 0x9A;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);

    cpu.D = 0x10;
    arg1 = 0xA2;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);

    cpu.D = 0x20;
    arg1 = 0xAA;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);

    cpu.D = 0x40;
    arg1 = 0xB2;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);

    cpu.D = 0x80;
    arg1 = 0xBA;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.D);
}

// Page 110
TEST_F(TestCpu, RES_b_E) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.E = 0x01;
    arg1 = 0x83;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);

    cpu.E = 0x02;
    arg1 = 0x8B;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);

    cpu.E = 0x04;
    arg1 = 0x93;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);

    cpu.E = 0x08;
    arg1 = 0x9B;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);

    cpu.E = 0x10;
    arg1 = 0xA3;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);

    cpu.E = 0x00;
    arg1 = 0xAB;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);

    cpu.E = 0x00;
    arg1 = 0xB3;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);

    cpu.E = 0x00;
    arg1 = 0xBB;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.E);
}

// Page 110
TEST_F(TestCpu, RES_b_H) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.H = 0x01;
    arg1 = 0x84;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);

    cpu.H = 0x02;
    arg1 = 0x8C;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);

    cpu.H = 0x04;
    arg1 = 0x94;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);

    cpu.H = 0x08;
    arg1 = 0x9C;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);

    cpu.H = 0x10;
    arg1 = 0xA4;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);

    cpu.H = 0x20;
    arg1 = 0xAC;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);

    cpu.H = 0x40;
    arg1 = 0xB4;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);

    cpu.H = 0x80;
    arg1 = 0xBC;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.H);
}

// Page 110
TEST_F(TestCpu, RES_b_L) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.L = 0x01;
    arg1 = 0x85;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);

    cpu.L = 0x02;
    arg1 = 0x8D;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);

    cpu.L = 0x04;
    arg1 = 0x95;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);

    cpu.L = 0x08;
    arg1 = 0x9D;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);

    cpu.L = 0x10;
    arg1 = 0xA5;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);

    cpu.L = 0x20;
    arg1 = 0xAD;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);

    cpu.L = 0x40;
    arg1 = 0xB5;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);

    cpu.L = 0x80;
    arg1 = 0xBD;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.L);
}

// Page 110
TEST_F(TestCpu, RES_b_HL) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x01;
    arg1 = 0x86;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x02;
    arg1 = 0x8E;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x04;
    arg1 = 0x96;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x08;
    arg1 = 0x9E;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x10;
    arg1 = 0xA6;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x20;
    arg1 = 0xAE;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x40;
    arg1 = 0xB6;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);

    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0x80;
    arg1 = 0xBE;
    cpu.execute(0xCB, arg1, arg2);
    EXPECT_EQ(0x00, cpu.memory()[0x0001]);
}

// Page 111
TEST_F(TestCpu, JP_nn) {
    unsigned char arg1;
    unsigned char arg2;

    arg1 = 0x00;
    arg2 = 0x00;
    cpu.execute(0xC3, arg1, arg2);
    EXPECT_EQ(0x0000, cpu.PC);

    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xC3, arg1, arg2);
    EXPECT_EQ(0xABCD, cpu.PC);
}

// Page 111
TEST_F(TestCpu, JP_NZ_nn) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;
    cpu.flag.Z = true;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xC2, arg1, arg2);
    EXPECT_EQ(0x0003, cpu.PC);

    cpu.PC = 0x0000;
    cpu.flag.Z = false;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xC2, arg1, arg2);
    EXPECT_EQ(0xABCD, cpu.PC);
}

// Page 111
TEST_F(TestCpu, JP_Z_nn) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;
    cpu.flag.Z = false;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xCA, arg1, arg2);
    EXPECT_EQ(0x0003, cpu.PC);

    cpu.PC = 0x0000;
    cpu.flag.Z = true;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xCA, arg1, arg2);
    EXPECT_EQ(0xABCD, cpu.PC);
}

// Page 111
TEST_F(TestCpu, JP_NC_nn) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;
    cpu.flag.C = true;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xD2, arg1, arg2);
    EXPECT_EQ(0x0003, cpu.PC);

    cpu.PC = 0x0000;
    cpu.flag.C = false;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xD2, arg1, arg2);
    EXPECT_EQ(0xABCD, cpu.PC);
}

// Page 111
TEST_F(TestCpu, JP_C_nn) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;
    cpu.flag.C = false;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xDA, arg1, arg2);
    EXPECT_EQ(0x0003, cpu.PC);

    cpu.PC = 0x0000;
    cpu.flag.C = true;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xDA, arg1, arg2);
    EXPECT_EQ(0xABCD, cpu.PC);
}

// Page 112
TEST_F(TestCpu, JP_HL) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;
    cpu.H = 0x00;
    cpu.L = 0x01;
    cpu.memory()[0x0001] = 0xCD;
    cpu.memory()[0x0002] = 0xAB;
    cpu.execute(0xE9, arg1, arg2);
    EXPECT_EQ(0xABCD, cpu.PC);
}

// Page 112
TEST_F(TestCpu, JR_n) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;
    arg1 = 0x01;
    cpu.execute(0x18, arg1, arg2);
    EXPECT_EQ(0x0003, cpu.PC);

    cpu.PC = 0xAB00;
    arg1 = 0x0F;
    cpu.execute(0x18, arg1, arg2);
    EXPECT_EQ(0xAB11, cpu.PC);

    cpu.PC = 0xAB01;
    arg1 = 0xFF;
    cpu.execute(0x18, arg1, arg2);
    EXPECT_EQ(0xAB02, cpu.PC);
}

// Page 113
TEST_F(TestCpu, JR_NZ_n) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;
    cpu.flag.Z = true;
    arg1 = 0xCD;
    cpu.execute(0x20, arg1, arg2);
    EXPECT_EQ(0x0002, cpu.PC);

    cpu.PC = 0x0000;
    cpu.flag.Z = false;
    arg1 = 0x01;
    cpu.execute(0x20, arg1, arg2);
    EXPECT_EQ(0x0003, cpu.PC);

    cpu.PC = 0xAB00;
    cpu.flag.Z = false;
    arg1 = 0x0F;
    cpu.execute(0x20, arg1, arg2);
    EXPECT_EQ(0xAB11, cpu.PC);

    cpu.PC = 0xAB01;
    cpu.flag.Z = false;
    arg1 = 0xFF;
    cpu.execute(0x20, arg1, arg2);
    EXPECT_EQ(0xAB02, cpu.PC);
}

// Page 113
TEST_F(TestCpu, JR_Z_n) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;
    cpu.flag.Z = false;
    arg1 = 0xCD;
    cpu.execute(0x28, arg1, arg2);
    EXPECT_EQ(0x0002, cpu.PC);

    cpu.PC = 0x0000;
    cpu.flag.Z = true;
    arg1 = 0x01;
    cpu.execute(0x28, arg1, arg2);
    EXPECT_EQ(0x0003, cpu.PC);

    cpu.PC = 0xAB00;
    cpu.flag.Z = true;
    arg1 = 0x0F;
    cpu.execute(0x28, arg1, arg2);
    EXPECT_EQ(0xAB11, cpu.PC);

    cpu.PC = 0xAB01;
    cpu.flag.Z = true;
    arg1 = 0xFF;
    cpu.execute(0x28, arg1, arg2);
    EXPECT_EQ(0xAB02, cpu.PC);
}

// Page 113
TEST_F(TestCpu, JR_NC_n) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;
    cpu.flag.C = true;
    arg1 = 0xCD;
    cpu.execute(0x30, arg1, arg2);
    EXPECT_EQ(0x0002, cpu.PC);

    cpu.PC = 0x0000;
    cpu.flag.C = false;
    arg1 = 0x01;
    cpu.execute(0x30, arg1, arg2);
    EXPECT_EQ(0x0003, cpu.PC);

    cpu.PC = 0xAB00;
    cpu.flag.C = false;
    arg1 = 0x0F;
    cpu.execute(0x30, arg1, arg2);
    EXPECT_EQ(0xAB11, cpu.PC);

    cpu.PC = 0xAB01;
    cpu.flag.C = false;
    arg1 = 0xFF;
    cpu.execute(0x30, arg1, arg2);
    EXPECT_EQ(0xAB02, cpu.PC);
}

// Page 113
TEST_F(TestCpu, JR_C_n) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;
    cpu.flag.C = false;
    arg1 = 0xCD;
    cpu.execute(0x38, arg1, arg2);
    EXPECT_EQ(0x0002, cpu.PC);

    cpu.PC = 0x0000;
    cpu.flag.C = true;
    arg1 = 0x01;
    cpu.execute(0x38, arg1, arg2);
    EXPECT_EQ(0x0003, cpu.PC);

    cpu.PC = 0xAB00;
    cpu.flag.C = true;
    arg1 = 0x0F;
    cpu.execute(0x38, arg1, arg2);
    EXPECT_EQ(0xAB11, cpu.PC);

    cpu.PC = 0xAB01;
    cpu.flag.C = true;
    arg1 = 0xFF;
    cpu.execute(0x38, arg1, arg2);
    EXPECT_EQ(0xAB02, cpu.PC);
}

// Page 114
TEST_F(TestCpu, CALL_nn) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;

    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xCD, arg1, arg2);
    EXPECT_EQ(0xABCD, cpu.PC);
    EXPECT_EQ(0x03, cpu.memory()[cpu.SP]);
    EXPECT_EQ(0x00, cpu.memory()[cpu.SP + 1]);

    arg1 = 0xFF;
    arg2 = 0xFF;
    cpu.execute(0xCD, arg1, arg2);
    EXPECT_EQ(0xFFFF, cpu.PC);
    EXPECT_EQ(0xD0, cpu.memory()[cpu.SP]);
    EXPECT_EQ(0xAB, cpu.memory()[cpu.SP + 1]);
}

// Page 115
TEST_F(TestCpu, CALL_NZ_nn) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;

    cpu.flag.Z = true;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xC4, arg1, arg2);
    EXPECT_EQ(0x0003, cpu.PC);

    cpu.flag.Z = false;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xC4, arg1, arg2);
    EXPECT_EQ(0xABCD, cpu.PC);
    EXPECT_EQ(0x06, cpu.memory()[cpu.SP]);
    EXPECT_EQ(0x00, cpu.memory()[cpu.SP + 1]);
}

// Page 115
TEST_F(TestCpu, CALL_Z_nn) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;

    cpu.flag.Z = false;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xCC, arg1, arg2);
    EXPECT_EQ(0x0003, cpu.PC);

    cpu.flag.Z = true;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xCC, arg1, arg2);
    EXPECT_EQ(0xABCD, cpu.PC);
    EXPECT_EQ(0x06, cpu.memory()[cpu.SP]);
    EXPECT_EQ(0x00, cpu.memory()[cpu.SP + 1]);
}

// Page 115
TEST_F(TestCpu, CALL_NC_nn) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;

    cpu.flag.C = true;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xD4, arg1, arg2);
    EXPECT_EQ(0x0003, cpu.PC);

    cpu.flag.C = false;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xD4, arg1, arg2);
    EXPECT_EQ(0xABCD, cpu.PC);
    EXPECT_EQ(0x06, cpu.memory()[cpu.SP]);
    EXPECT_EQ(0x00, cpu.memory()[cpu.SP + 1]);
}

// Page 115
TEST_F(TestCpu, CALL_C_nn) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;

    cpu.flag.C = false;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xDC, arg1, arg2);
    EXPECT_EQ(0x0003, cpu.PC);

    cpu.flag.C = true;
    arg1 = 0xCD;
    arg2 = 0xAB;
    cpu.execute(0xDC, arg1, arg2);
    EXPECT_EQ(0xABCD, cpu.PC);
    EXPECT_EQ(0x06, cpu.memory()[cpu.SP]);
    EXPECT_EQ(0x00, cpu.memory()[cpu.SP + 1]);
}

// Page 116
TEST_F(TestCpu, RST_n) {
    unsigned char arg1;
    unsigned char arg2;

    cpu.PC = 0x0000;

    cpu.execute(0xC7, arg1, arg2);
    EXPECT_EQ(0x0000, cpu.PC);
    EXPECT_EQ(0x01, cpu.memory()[cpu.SP]);
    EXPECT_EQ(0x00, cpu.memory()[cpu.SP + 1]);

    cpu.execute(0xCF, arg1, arg2);
    EXPECT_EQ(0x0008, cpu.PC);
    EXPECT_EQ(0x01, cpu.memory()[cpu.SP]);
    EXPECT_EQ(0x00, cpu.memory()[cpu.SP + 1]);

    cpu.execute(0xD7, arg1, arg2);
    EXPECT_EQ(0x0010, cpu.PC);
    EXPECT_EQ(0x09, cpu.memory()[cpu.SP]);
    EXPECT_EQ(0x00, cpu.memory()[cpu.SP + 1]);

    cpu.execute(0xDF, arg1, arg2);
    EXPECT_EQ(0x0018, cpu.PC);
    EXPECT_EQ(0x11, cpu.memory()[cpu.SP]);
    EXPECT_EQ(0x00, cpu.memory()[cpu.SP + 1]);

    cpu.execute(0xE7, arg1, arg2);
    EXPECT_EQ(0x0020, cpu.PC);
    EXPECT_EQ(0x19, cpu.memory()[cpu.SP]);
    EXPECT_EQ(0x00, cpu.memory()[cpu.SP + 1]);

    cpu.execute(0xEF, arg1, arg2);
    EXPECT_EQ(0x0028, cpu.PC);
    EXPECT_EQ(0x21, cpu.memory()[cpu.SP]);
    EXPECT_EQ(0x00, cpu.memory()[cpu.SP + 1]);

    cpu.execute(0xF7, arg1, arg2);
    EXPECT_EQ(0x0030, cpu.PC);
    EXPECT_EQ(0x29, cpu.memory()[cpu.SP]);
    EXPECT_EQ(0x00, cpu.memory()[cpu.SP + 1]);

    cpu.execute(0xFF, arg1, arg2);
    EXPECT_EQ(0x0038, cpu.PC);
    EXPECT_EQ(0x31, cpu.memory()[cpu.SP]);
    EXPECT_EQ(0x00, cpu.memory()[cpu.SP + 1]);
}

// Page 117
TEST_F(TestCpu, RET) {
    unsigned char arg1;
    unsigned char arg2;

    unsigned short OLD_SP = cpu.SP;

    cpu.PC = 0x1234;

    // Push some bytes
    cpu.execute(0xFF, arg1, arg2);

    cpu.execute(0xC9, arg1, arg2);
    EXPECT_EQ(0x1234 + 0x01, cpu.PC);
    EXPECT_EQ(OLD_SP, cpu.SP);
}

// Page 117
TEST_F(TestCpu, RET_NZ) {
    unsigned char arg1;
    unsigned char arg2;

    unsigned short OLD_SP = cpu.SP;

    cpu.PC = 0x1234;

    // Push some bytes
    cpu.execute(0xFF, arg1, arg2);

    cpu.flag.Z = true;
    cpu.execute(0xC0, arg1, arg2);
    EXPECT_EQ(0x0038 + 0x01, cpu.PC);

    cpu.flag.Z = false;
    cpu.execute(0xC0, arg1, arg2);
    EXPECT_EQ(0x1234 + 0x01, cpu.PC);
    EXPECT_EQ(OLD_SP, cpu.SP);
}

// Page 117
TEST_F(TestCpu, RET_Z) {
    unsigned char arg1;
    unsigned char arg2;

    unsigned short OLD_SP = cpu.SP;

    cpu.PC = 0x1234;

    // Push some bytes
    cpu.execute(0xFF, arg1, arg2);

    cpu.flag.Z = false;
    cpu.execute(0xC8, arg1, arg2);
    EXPECT_EQ(0x0038 + 0x01, cpu.PC);

    cpu.flag.Z = true;
    cpu.execute(0xC8, arg1, arg2);
    EXPECT_EQ(0x1234 + 0x01, cpu.PC);
    EXPECT_EQ(OLD_SP, cpu.SP);
}

// Page 117
TEST_F(TestCpu, RET_NC) {
    unsigned char arg1;
    unsigned char arg2;

    unsigned short OLD_SP = cpu.SP;

    cpu.PC = 0x1234;

    // Push some bytes
    cpu.execute(0xFF, arg1, arg2);

    cpu.flag.C = true;
    cpu.execute(0xD0, arg1, arg2);
    EXPECT_EQ(0x0038 + 0x01, cpu.PC);

    cpu.flag.C = false;
    cpu.execute(0xD0, arg1, arg2);
    EXPECT_EQ(0x1234 + 0x01, cpu.PC);
    EXPECT_EQ(OLD_SP, cpu.SP);
}

// Page 117
TEST_F(TestCpu, RET_C) {
    unsigned char arg1;
    unsigned char arg2;

    unsigned short OLD_SP = cpu.SP;

    cpu.PC = 0x1234;

    // Push some bytes
    cpu.execute(0xFF, arg1, arg2);

    cpu.flag.C = false;
    cpu.execute(0xD8, arg1, arg2);
    EXPECT_EQ(0x0038 + 0x01, cpu.PC);

    cpu.flag.C = true;
    cpu.execute(0xD8, arg1, arg2);
    EXPECT_EQ(0x1234 + 0x01, cpu.PC);
    EXPECT_EQ(OLD_SP, cpu.SP);
}

// Page 118
TEST_F(TestCpu, RETI) {
    unsigned char arg1;
    unsigned char arg2;

    unsigned short OLD_SP = cpu.SP;

    cpu.PC = 0x1234;

    // Push some bytes
    cpu.execute(0xFF, arg1, arg2);

    cpu.execute(0xD9, arg1, arg2);
    EXPECT_EQ(0x1234 + 0x01, cpu.PC);
    EXPECT_EQ(OLD_SP, cpu.SP);
}
