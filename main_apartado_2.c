#include "linear_queue.h"
#include "circular_queue.h"



//GPI_PIN_HANDLER(GPIO_ITEM){}

void SPI_PIN_HANDLER(SPI_ITEM *q, SPI_ITEM item)
{
    switch (q->qu)
    {
    case constant expression:
        /* code */
        break;
    
    default:
        break;
    }

}
int main()
{
    linearqueue l;
    circularqueue c;
    initLinearqueue(&l);
    initCircularqueue(&c);

    SPI_ITEM item_spi[MAX_LINEAR] = {
        {.mode = SDO,
         .reg = Gravity_L,
         .data = NULL},
        {.mode = SDI,
         .reg = Gravity_H,
         .data = NULL},
        {.mode = SDO,
         .reg = Gravity_H,
         .data = NULL},
        {.mode = SDO,
         .reg = Gravity_H,
         .data = NULL},
        {.mode = SDO,
         .reg = INTERRUPT_REGISTER,
         .data = NULL},

    };

    gpio item_gpio[MAX_CIRCULAR] = {CS, INT1, INT2, INT4, INT3, CS, INT2, CS, INT4, INT3};

    uint8_t size_item_spi = sizeof(item_spi)/sizeof(item_spi[0]);
    for (int i = 0; i < size_item_spi; i++)
    {
        enqueue_linear(&l, item_spi[i]);
        isFull_linear(&l) ? SPI_PIN_HANDLER : NULL ; 
    }


    return 0;
}