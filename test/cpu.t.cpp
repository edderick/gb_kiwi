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

    cpu.A = 0x22;
    cpu.C = 0xFF;
    cpu.execute(0x81, arg1, arg2);
    EXPECT_EQ(0x21, cpu.A);
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
