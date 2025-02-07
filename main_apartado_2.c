#include "linear_queue.h"
#include "circular_queue.h"

void SPI_PIN_HANDLER(linearqueue *q)
{
    printf("Read/write data from SPI registers: \n");
    while (!isEmpty_linear(q))
    {
        switch (peek_linear(q).reg)
        {
        case Gravity_L:

            peek_linear(q).mode == SDO ? printf("Read data from Gravity_L (0x%.2x) \n", Gravity_L) : printf("Only read allowed in Gravity_L(0x%.2x) \n", Gravity_L);

            break;

        case Gravity_H:

            peek_linear(q).mode == SDO ? printf("Read data from Gravity_H (0x%.2x) \n", Gravity_H) : printf("Only read allowed in Gravity_H (0x%.2x) \n", Gravity_H);

            break;

        case INTERRUPT_REGISTER:

            peek_linear(q).mode == SDO ? printf("Read data from INTERRUPT_REGISTER (0x%.2x) \n", INTERRUPT_REGISTER) : printf("Only read allowed in INTERRUPT_REGISTER (0x%.2x) \n", INTERRUPT_REGISTER);

            break;

        case DEVICE_DEFINITION:

            peek_linear(q).mode == SDO ? printf("Read data from DEVICE_DEFINITION (0x%.2x) \n", INTERRUPT_REGISTER) : peek_linear(q).mode == SDI ? printf("Write on DEVICE_DEFINITION, value = 0x%.2x\n", peek_linear(q).data)
                                                                                                                                                 : printf("Invalid instruction\n");

            break;
        default:
            printf("Invalid register\n");
            break;
        }
        dequeue_linear(q);
    }
    printf("\n");
}

void GPI_PIN_HANDLER(circularqueue *q)
{
    printf("Interruptions to handle on GPIO: \n");
    while (!isEmpty_circular(q))
    {
        switch (peek_circular(q))
        {
        case CS:
            break;
        case INT1:
            printf("interruption: touch 0x%.2x\n", INT1);

            break;
        case INT2:
            printf("interruption: Gravity change 0x%.2x\n", INT2);
            break;
        case INT3:
            printf("interruption: inactivity 0x%.2x\n", INT3);
            break;
        case INT4:
            printf("interruption: double tap 0x%.2x\n", INT4);
            break;
        default:
            printf("Unknow interruption\n");
            break;
        }
        dequeue_circular(q);
    }
    printf("\n");
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
         .reg = INTERRUPT_REGISTER,
         .data = NULL},
        {.mode = SDI,
         .reg = DEVICE_DEFINITION,
         .data = (void *)0xff}

    };

    gpio item_gpio[MAX_CIRCULAR] = {CS, INT1, INT2, INT4, INT3, CS, INT2, CS, INT4, INT3};

    for (int i = 0; i < MAX_LINEAR; i++)
    {
        enqueue_linear(&l, item_spi[i]);

    }

    SPI_PIN_HANDLER(&l);

    for (int i = 0; i < MAX_CIRCULAR; i++)
    {
        enqueue_circular(&c, item_gpio[i]);
    }

    GPI_PIN_HANDLER(&c);

    return 0;
}