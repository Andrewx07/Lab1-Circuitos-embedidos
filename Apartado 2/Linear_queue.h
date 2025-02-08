#ifndef QUEUE_LINEAR_h
#define QUEUE_LINEAR_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINEAR 5

// action from register
typedef enum SPI_PIN
{
    SDO = 0xE0, // Data output(read)
    SDI = 0xE1, // Data input(write)
    SCK = 0xE2, // Clock
} SPI;

struct bitfield_definitions 
{
    uint8_t bit_0 : 1;
    uint8_t bit_1 : 1;
    uint8_t bit_2 : 1;
    uint8_t : 5;
};

union definitions
{
    uint8_t byte;
    struct bitfield_definitions definitions;
};

struct bitfield_Gravity_L 
{
    uint8_t : 1;
    uint8_t bit_2 : 1;
    uint8_t bit_3 : 1;
    uint8_t bit_4 : 1;
    uint8_t bit_5 : 1;
    uint8_t bit_6 : 1;
    uint8_t bit_7 : 1;
};

union gravity_L
{
    uint8_t byte;
    struct bitfield_Gravity_L G_L;
};

struct bitfield_Gravity_H
{
    uint8_t bit_0 : 1;
    uint8_t bit_1 : 1;
    uint8_t bit_2 : 1;
    uint8_t bit_3 : 1;
    uint8_t : 4;
};

union gravity_H
{
    uint8_t byte;
    struct bitfield_Gravity_H G_H;
};


struct interrupt_configure
{
    uint8_t bit_0 : 1;
    uint8_t bit_1 : 1;
    uint8_t bit_2 : 1;
    uint8_t bit_3 : 1;
    uint8_t : 4;
};

union interrupt
{
    uint8_t byte;
    struct interrupt_configure interrupt_config;
};



typedef enum
{ 
    READ = 0xff,
    WRITE = 0xfe,

}action;

// register address
typedef enum
{
    Gravity_L = 0x10,
    Gravity_H = 0x11,
    INTERRUPT_REGISTER = 0x20,
    DEVICE_DEFINITION = 0xff,
} ACCEL_REG;




// item for spi pin
typedef struct
{
    action mode;
    ACCEL_REG reg;
    void *data;

} SPI_ITEM;

// linear queue
typedef struct __attribute__((__packed__))
{
    SPI_ITEM queue[MAX_LINEAR];
    int8_t front;
    int8_t rear;
} linearqueue;

void initLinearqueue(linearqueue *queue);
int isFull_linear(linearqueue *queue);
int isEmpty_linear(linearqueue *queue);
void enqueue_linear(linearqueue *queue, SPI_ITEM data);
int dequeue_linear(linearqueue *queue);
SPI_ITEM peek_linear(linearqueue *queue);
void display_linear(linearqueue *queue);

void initLinearqueue(linearqueue *q)
{
    q->front = -1;
    q->rear = 0;
}

int isFull_linear(linearqueue *q)
{
    return q->rear == MAX_LINEAR;
}

int isEmpty_linear(linearqueue *q)
{
    return q->front == q->rear - 1;
}

void enqueue_linear(linearqueue *q, SPI_ITEM data)
{
    if (isFull_linear(q))
    {
        printf("Queue is full\n");
        return;
    }
    q->queue[q->rear] = data;
    q->rear++;
}

int dequeue_linear(linearqueue *q)
{
    isEmpty_linear(q) ? printf("Queue is empty\n") : q->front++;
}

SPI_ITEM peek_linear(linearqueue *q)
{
    // isEmpty_linear(q) ? printf("Queue is empty\n") :( printf("peek_linear: \n 0x%.2x\n", q->queue[q->front + 1].mode), printf("0x%.2x\n", q->queue[q->front + 1].reg), printf("0x%.2x\n", q->queue[q->front + 1].data));
    return q->queue[q->front + 1];
}

void display_linear(linearqueue *q)
{
    if (isEmpty_linear(q))
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue register: \n");
    for (uint8_t i = q->front + 1; i < q->rear; i++)
    {
        printf("%d - ", i);
        switch (q->queue[i].mode)
        {
        case SDI:
            printf("Read\n");
            break;

        case SDO:
            printf("Write\n");
            if (q->queue[i].data != NULL)
            {
                printf("%d", q->queue[i].data);
            }
            break;
        case SCK:
            printf("clock\n");

        default:
            printf("invalid pin \n");
            break;
        }

        switch (q->queue[i].reg)
        {
        case Gravity_L:
            printf("Gravity L register\n");
            break;
        case Gravity_H:
            printf("Gravity H register\n");
            break;
        case INTERRUPT_REGISTER:
            printf("interruption register \n");
            break;
        case DEVICE_DEFINITION:
            printf("Device Definitions  \n");
            break;
        default:
            printf("invalid register\n");
            break;
        }
    }
    printf("\n");
}

// Action on registers from SPI
void SPI_PIN_HANDLER(linearqueue *q)
{
    printf("Read/write data from SPI registers: \n");
    while (!isEmpty_linear(q))
    {
        switch (peek_linear(q).reg)
        {
        case Gravity_L:

            peek_linear(q).mode == READ ? printf("Read data from Gravity_L (0x%.2x) \n", Gravity_L) : printf("Only read allowed in Gravity_L(0x%.2x) \n", Gravity_L);

            break;

        case Gravity_H:

            peek_linear(q).mode == READ ? printf("Read data from Gravity_H (0x%.2x) \n", Gravity_H) : printf("Only read allowed in Gravity_H (0x%.2x) \n", Gravity_H);

            break;

        case INTERRUPT_REGISTER:

            peek_linear(q).mode == READ ? printf("Read data from INTERRUPT_REGISTER (0x%.2x) \n", INTERRUPT_REGISTER) : printf("Only read allowed in INTERRUPT_REGISTER (0x%.2x) \n", INTERRUPT_REGISTER);

            break;

        case DEVICE_DEFINITION:

            peek_linear(q).mode == READ ? printf("Read data from DEVICE_DEFINITION (0x%.2x) \n", INTERRUPT_REGISTER) : peek_linear(q).mode == WRITE ? printf("Write on DEVICE_DEFINITION, value = 0x%.2x\n", peek_linear(q).data)
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

#endif
