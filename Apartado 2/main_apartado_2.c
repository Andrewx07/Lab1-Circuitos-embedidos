#include "linear_queue.h"
#include "circular_queue.h"

int main()
{
    linearqueue l;
    circularqueue c;
    initLinearqueue(&l);
    initCircularqueue(&c);

    SPI_ITEM item_spi[MAX_LINEAR] = {
        {.mode = READ,
         .reg = Gravity_L,
         .data = NULL},
        {.mode = WRITE,
         .reg = Gravity_H,
         .data = NULL},
        {.mode = READ,
         .reg = Gravity_H,
         .data = NULL},
        {.mode = READ,
         .reg = INTERRUPT_REGISTER,
         .data = NULL},
        {.mode = WRITE,
         .reg = DEVICE_DEFINITION,
         .data = (void *)0xff}

    };

    interrupts item_gpio[MAX_CIRCULAR] = {Touch, Gravity_change, Inactivity, Double_tap, Touch, Inactivity, Double_tap, Gravity_change, Touch, Inactivity };

    for (int i = 0; i < MAX_LINEAR; i++)
    {
        enqueue_linear(&l, item_spi[i]);

    }

    SPI_PIN_HANDLER(&l);

    for (int i = 0; i < MAX_CIRCULAR; i++)
    {
        enqueue_circular(&c, item_gpio[i]);
    }

    GPIO_PIN_HANDLER(&c);

    return 0;
}