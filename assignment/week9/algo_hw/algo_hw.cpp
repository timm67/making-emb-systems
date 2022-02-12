// algo_hw.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
 * Implement one of the following:
 * How many bits are one in a given 32-bit uint?
 * How many leading zeros are in a 32-bit uint?
 * Trigonometry functions like sin, cos, tan
 * Integer division with remainder
 * Find the first 100 prime numbers
*/

#include <stdio.h>
#include <stdint.h>

int leading_zeros_lookup8(uint8_t foo)
{
    const uint8_t table[] =
    {
     8,  7,  6,  6,  5,  5,  5,  5,
     4,  4,  4,  4,  4,  4,  4,  4,
     3,  3,  3,  3,  3,  3,  3,  3,
     3,  3,  3,  3,  3,  3,  3,  3,
     2,  2,  2,  2,  2,  2,  2,  2,
     2,  2,  2,  2,  2,  2,  2,  2,
     2,  2,  2,  2,  2,  2,  2,  2,
     2,  2,  2,  2,  2,  2,  2,  2,
     1,  1,  1,  1,  1,  1,  1,  1,
     1,  1,  1,  1,  1,  1,  1,  1,
     1,  1,  1,  1,  1,  1,  1,  1,
     1,  1,  1,  1,  1,  1,  1,  1,
     1,  1,  1,  1,  1,  1,  1,  1,
     1,  1,  1,  1,  1,  1,  1,  1,
     1,  1,  1,  1,  1,  1,  1,  1,
     1,  1,  1,  1,  1,  1,  1,  1,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0
    };

    return table[foo];
}

int leading_zeros_lookup(uint32_t foo)
{
    int i, tmp, zeros = 0;
    union {
        uint32_t u32;
        uint8_t u8[4];
    } u;

    u.u32 = foo;

    for (i = 3; i >= 0; i--)
    {
        tmp = leading_zeros_lookup8(u.u8[i]);
        if (tmp)
            zeros += tmp;
        else
            break;
    }
    return zeros;
}

int leading_zeros_shift(uint32_t foo)
{
    uint32_t mask = 0x80000000;
    int i, zeros = 0;

    for (i = 0; i < 32; i++, mask >>= 1)
    {
        if ((foo & mask) == 0)
            zeros++;
        else
            break;
    }

    return zeros;
}

int main()
{
    uint32_t test1 = 0x80000000, test2 = 0x00000001, test3 = 0x00008000;
    int zeros_lookup, zeros_shift;

    printf("Math algorithm homework\n");

    zeros_lookup = leading_zeros_lookup(test1);
    zeros_shift = leading_zeros_shift(test1);
    printf("0x8000_0000\n");
    printf("zeros_lookup = %d\n", zeros_lookup);
    printf("zeros_shift = %d\n", zeros_shift);

    zeros_lookup = leading_zeros_lookup(test3);
    zeros_shift = leading_zeros_shift(test3);
    printf("0x0000_8000\n");
    printf("zeros_lookup = %d\n", zeros_lookup);
    printf("zeros_shift = %d\n", zeros_shift);
}


