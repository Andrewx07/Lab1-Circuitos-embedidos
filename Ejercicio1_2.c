#include <stdint.h>

struct bitfield_definitions {
    uint8_t bit_0 : 1;
    uint8_t bit_1 : 1;
    uint8_t bit_2 : 1;
    uint8_t : 5;    
};

struct bitfield_Gravity_L {
    uint8_t : 1;
    uint8_t bit_2 : 1;
    uint8_t bit_3 : 1;
    uint8_t bit_4 : 1;
    uint8_t bit_5 : 1;
    uint8_t bit_6 : 1;
    uint8_t bit_7 : 1;
};

struct bitfield_Gravity_H {
    uint8_t bit_0 : 1;
    uint8_t bit_1 : 1;
    uint8_t bit_2 : 1;
    uint8_t bit_3 : 1;
    uint8_t : 4;

};

struct interrupt_configure{
    uint8_t bit_0 : 1;
    uint8_t bit_1 : 1;
    uint8_t bit_2 : 1;
    uint8_t bit_3 : 1;
    uint8_t : 4;
};

union definitions {
    uint8_t byte;
    struct bitfield_definitions bits;
    
};

union gravity_L {
    uint8_t byte;
    struct bitfield_Gravity_L bits;
};

union gravity_H {
    uint8_t byte;
    struct bitfield_Gravity_H bits;
};

union interrupt {
    uint8_t byte;
    struct interrupt_configure bits;
};
