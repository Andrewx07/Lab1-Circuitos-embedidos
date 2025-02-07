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
 
//circular queue
typedef struct {
    gpio queue[MAX_CIRCULAR] __attribute__((packed));
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

void initCircularqueue(circularqueue* q) {
    q->front = -1;
    q->rear = -1;
}  

int isFull_circular(circularqueue* q) {
    return (q->rear + 1) % MAX_CIRCULAR == q->front;
}

int isEmpty_circular(circularqueue* q) {
    return q->front == -1;
}


void enqueue_circular(circularqueue* q, uint8_t data){
    if(isFull_circular(q)){
        printf("Queue is full\n");
        return;
    }
    q->front == -1 ? q->front = 0 : q->front;
    q->rear = (q->rear + 1) % MAX_CIRCULAR;
    q->queue[q->rear] = data;
}

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

int peek_circular(circularqueue* q){
    if(isEmpty_circular(q)){
        printf("Queue is empty\n");
        return -1;
    }
    return q->queue[q->front];
}

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
#endif

