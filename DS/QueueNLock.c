#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Node {
    int data;
    struct Node* next;
    pthread_mutex_t lock;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    pthread_mutex_t queue_lock;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = NULL;
    pthread_mutex_init(&q->queue_lock, NULL);
}

void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    pthread_mutex_init(&newNode->lock, NULL);

    pthread_mutex_lock(&q->queue_lock);
    if (q->rear) {
        pthread_mutex_lock(&q->rear->lock);
        q->rear->next = newNode;
        pthread_mutex_unlock(&q->rear->lock);
    } else {
        q->front = newNode;
    }
    q->rear = newNode;
    pthread_mutex_unlock(&q->queue_lock);
}

int dequeue(Queue* q) {
    pthread_mutex_lock(&q->queue_lock);
    if (!q->front) {
        pthread_mutex_unlock(&q->queue_lock);
        return -1;
    }
    Node* temp = q->front;
    pthread_mutex_lock(&temp->lock);
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    int value = temp->data;
    pthread_mutex_unlock(&temp->lock);
    free(temp);
    pthread_mutex_unlock(&q->queue_lock);
    return value;
}

void printQueue(Queue* q) {
    pthread_mutex_lock(&q->queue_lock);
    Node* temp = q->front;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
    pthread_mutex_unlock(&q->queue_lock);
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
