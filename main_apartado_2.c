#include "linear_queue.h"
#include "circular_queue.h"

typedef enum GPIO_PIN
{
    CS = 0xA0,// Chip select
    int1 = 0xA1,// Interrupt 1
    int2 = 0xA2,// Interrupt 2
    int3 = 0xA3,// Interrupt 3
    int4 = 0xA4,// Interrupt 4

} gpio;

typedef enum SPI_PIN
{
    SDO = 0xE0,// Data output(read)
    SDI = 0xE1,// Data input(write)
    SCK = 0xE2,// Clock
} spi;

typedef enum{

    INTERRUPT_REGISTER = 0x20,
    Gravity_L = 0x10,
    Gravity_H = 0x11,

}ACCELERATION_REGISTERS;

typedef enum{
        
}



int main(){
    linearqueue L;
    circularqueue C; 

    

    
    return 0;
}