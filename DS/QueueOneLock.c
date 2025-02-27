#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    pthread_mutex_t lock;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = NULL;
    pthread_mutex_init(&q->lock, NULL);
}

void enqueue(Queue* q, int value) {
    pthread_mutex_lock(&q->lock);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    pthread_mutex_unlock(&q->lock);
}

int dequeue(Queue* q) {
    pthread_mutex_lock(&q->lock);
    if (q->front == NULL) {
        pthread_mutex_unlock(&q->lock);
        return -1;  // Queue is empty
    }
    Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    pthread_mutex_unlock(&q->lock);
    return value;
}

void printQueue(Queue* q) {
    pthread_mutex_lock(&q->lock);
    Node* temp = q->front;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
    pthread_mutex_unlock(&q->lock);
}

int main() {
    Queue q;
    initQueue(&q);
    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    printQueue(&q);
    printf("Dequeued: %d\n", dequeue(&q));
    printQueue(&q);
    return 0;
}
