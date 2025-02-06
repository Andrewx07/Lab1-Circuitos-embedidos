#ifndef QUEUE_LINEAR_h
#define QUEUE_LINEAR_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINEAR 5

typedef struct __attribute__((packed)) { 
    uint8_t queue[MAX_LINEAR] ;
    int8_t front;
    int8_t rear;
}linearqueue;

void initLinearqueue(linearqueue* queue);
int isFull_linear(linearqueue* queue);
int isEmpty_linear(linearqueue* queue);
void enqueue_linear(linearqueue* queue, uint8_t data);
int dequeue_linear(linearqueue* queue);
int peek_linear(linearqueue* queue);
void display_linear(linearqueue* queue);

void initLinearqueue(linearqueue* q) {
    q->front = -1;
    q->rear = 0;
}

int isFull_linear(linearqueue* q) {
    return q->rear == MAX_LINEAR;
}

int isEmpty_linear(linearqueue* q) {
    return q->rear == q->front+1;
}

void enqueue_linear(linearqueue* q, uint8_t data){
    if(isFull_linear(q)){
        printf("Queue is full\n");
        return;
    }
    q->queue[q->rear] = data;
    q->rear++;
}

int dequeue_linear(linearqueue* q){
    isEmpty_linear(q) ? printf("Queue is empty\n") : q->front++;
}

int peek_linear(linearqueue* q){
    isEmpty_linear(q) ? printf("Queue is empty\n") : printf("peek_linear: %d\n", q->queue[q->front+1]);
}

void display_linear(linearqueue* q){
    if(isEmpty_linear(q)){
        printf("Queue is empty\n");
        return;
    }
    printf("Queue register:");
    for(uint8_t i = q->front+1; i < q->rear; i++){
        printf(" %d ", q->queue[i]);
    }
    printf("\n");
}

#endif
