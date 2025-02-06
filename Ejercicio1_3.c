#include <stdint.h>

struct bitfield//fixed from class
{
    uint8_t : 1;
    uint8_t touch : 1;
    uint8_t Gravity : 1;
    uint8_t inactivity: 1;
    uint8_t double_tap: 1;
    uint8_t : 3;
};


typedef union INTERRUPT
{
    uint8_t byte;
    struct bitfield bits;
}interrupts;

typedef struct ITEM{
    interrupts interrupt;
    uint8_t data;
    uint8_t address;
}item;