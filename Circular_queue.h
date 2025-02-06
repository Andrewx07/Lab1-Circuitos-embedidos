#ifndef QUEUE_CIRCULAR_h
#define QUEUE_CIRCULAR_h

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_CIRCULAR 10

typedef struct __attribute__((packed)) {
    uint8_t queue[MAX_CIRCULAR];
    int8_t front;
    int8_t rear;
}circularqueue;

void initCircularqueue(circularqueue* queue);
int isFull(circularqueue* queue);
int isEmpty(circularqueue* queue);
void enqueue(circularqueue* queue, uint8_t data);
int dequeue(circularqueue* queue);
int peek(circularqueue* queue);
void display(circularqueue* queue);

void initCircularqueue(circularqueue* q) {
    q->front = -1;
    q->rear = -1;
}  

int isFull(circularqueue* q) {
    return (q->rear + 1) % MAX_CIRCULAR == q->front;
}

int isEmpty(circularqueue* q) {
    return q->front == -1;
}


void enqueue(circularqueue* q, uint8_t data){
    if(isFull(q)){
        printf("Queue is full\n");
        return;
    }
    q->front == -1 ? q->front = 0 : q->front;
    q->rear = (q->rear + 1) % MAX_CIRCULAR;
    q->queue[q->rear] = data;
}

int dequeue(circularqueue* q){
    if(isEmpty(q)){
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

int peek(circularqueue* q){
    if(isEmpty(q)){
        printf("Queue is empty\n");
        return -1;
    }
    return q->queue[q->front];
}

void display (circularqueue* q){
    if(isEmpty(q)){
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements:");
    if(q->rear >= q->front){
        for(uint8_t i = q->front; i <= q->rear; i++){
            printf(" %d ", q->queue[i]);
        }
    }else{
        for(uint8_t i = q->front; i < MAX_CIRCULAR; i++){
            printf(" %d ", q->queue[i]);
        }
        for(uint8_t i = 0; i <= q->rear; i++){
            printf(" %d ", q->queue[i]);
        }
    }
    printf("\n");
}
#endif

