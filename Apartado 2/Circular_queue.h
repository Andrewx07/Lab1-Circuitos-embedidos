#ifndef QUEUE_CIRCULAR_h
#define QUEUE_CIRCULAR_h

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_CIRCULAR 10

//interruption pin address
typedef enum GPIO_PIN
{
    CS = 0xA0,   // Chip select(input)
    INT1 = 0xA1, // Interrupt 1
    INT2 = 0xA2, // Interrupt 2
    INT3 = 0xA3, // Interrupt 3
    INT4 = 0xA4, // Interrupt 4

} gpio;

//interruptions definitions
typedef enum interruptions//fixed from class
{
    Touch = 0x01,
    Gravity_change = 0x02,
    Inactivity = 0x03,
    Double_tap = 0x04,

}interrupts;

//circular queue
typedef struct __attribute__((packed)){
    interrupts queue[MAX_CIRCULAR];
    int8_t front;
    int8_t rear;
}circularqueue;



void initCircularqueue(circularqueue* queue);
int isFull_circular(circularqueue* queue);
int isEmpty_circular(circularqueue* queue);
void enqueue_circular(circularqueue* queue, uint8_t data);
int dequeue_circular(circularqueue* queue);
int peek_circular(circularqueue* queue);
void display_circular(circularqueue* queue);

//initialization for a circular queue
void initCircularqueue(circularqueue* q) {
    q->front = -1;
    q->rear = -1;
}  

//check if the queue is full
int isFull_circular(circularqueue* q) {
    return (q->rear + 1) % MAX_CIRCULAR == q->front;
}

//chech if the queue is empty
int isEmpty_circular(circularqueue* q) {
    return q->front == -1;
}

//push an item on the queue
void enqueue_circular(circularqueue* q, uint8_t data){
    if(isFull_circular(q)){
        printf("Queue is full\n");
        return;
    }
    q->front == -1 ? q->front = 0 : q->front;
    q->rear = (q->rear + 1) % MAX_CIRCULAR;
    q->queue[q->rear] = data;
}


//pop an item on the queue
int dequeue_circular(circularqueue* q){
    if(isEmpty_circular(q)){
        printf("Queue is empty\n");
        return -1;
    }
    uint8_t data = q->queue[q->front];
    if(q->front == q->rear){
        q->front = -1;
        q->rear = -1;
    }else{
        q->front = (q->front + 1) % MAX_CIRCULAR;
    }
    return data;
}

//peek the top of the queue
int peek_circular(circularqueue* q){
    if(isEmpty_circular(q)){
        printf("Queue is empty\n");
        return -1;
    }
    return q->queue[q->front];
}

//display all the queue 
void display_circular (circularqueue* q){
    if(isEmpty_circular(q)){
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements:");
    if(q->rear >= q->front){
        for(uint8_t i = q->front; i <= q->rear; i++){
            printf("0x%.2x ", q->queue[i]);
        }
    }else{
        for(uint8_t i = q->front; i < MAX_CIRCULAR; i++){
            printf(" 0x%.2x ", q->queue[i]);
        }
        for(uint8_t i = 0; i <= q->rear; i++){
            printf(" 0x%.2x ", q->queue[i]);
        }
    }
    printf("\n");
}

//GPIO interruption handler
void GPIO_PIN_HANDLER(circularqueue *q)
{
    printf("Interruptions to handle on GPIO: \n");
    while (!isEmpty_circular(q))
    {
        switch (peek_circular(q))
        {
        case CS:
            break;
        case Touch:
            printf("interruption: touch 0x%.2x\n", INT1);

            break;
        case Gravity_change:
            printf("interruption: Gravity change 0x%.2x\n", INT2);
            break;
        case Inactivity:
            printf("interruption: inactivity 0x%.2x\n", INT3);
            break;
        case Double_tap:
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


#endif

