#include <gtest/gtest.h>
#include "../cpu.h"

TEST(CPU, cpuCanBeCreated) {
    CPU cpu; 
    EXPECT_EQ(0, cpu.PC); 
}

TEST(CPU, 8_bitLoadsWordCorrectly) {
    CPU cpu; 

    unsigned char expected = 5;
    cpu.LD(cpu.A, expected);

    EXPECT_EQ(expected, cpu.A);
}

TEST(CPU, 16_bitLoadsWordCorrectly) {
    CPU cpu; 
    
    unsigned char expectedA = 5;
    unsigned char expectedB = 6;
    
    cpu.LD_16(cpu.A, cpu.B, expectedA, expectedB);

    EXPECT_EQ(expectedA, cpu.A);
    EXPECT_EQ(expectedB, cpu.B);
}
