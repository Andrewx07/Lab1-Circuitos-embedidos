#include <stdint.h>
// #include <stdio.h>

typedef enum GPIO
{

    CS = 0xA0,
    int1 = 0xA1,
    int2 = 0xA2,
    int3 = 0xA3,
    int4 = 0xA4,

} gpio;

typedef enum SPI
{

    SDO = 0xE0,
    SDI = 0xE1,
    SCK = 0xE2,
} spi;

int main(void)
{
    // test for debugging
    return 0;
}