#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    pthread_mutex_t lock;
} LinkedList;

void initList(LinkedList* list) {
    list->head = NULL;
    pthread_mutex_init(&list->lock, NULL);
}

void insert(LinkedList* list, int value) {
    pthread_mutex_lock(&list->lock);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = list->head;
    list->head = newNode;
    pthread_mutex_unlock(&list->lock);
}

void printList(LinkedList* list) {
    pthread_mutex_lock(&list->lock);
    Node* temp = list->head;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
    pthread_mutex_unlock(&list->lock);
}

int main() {
    LinkedList list;
    initList(&list);
    insert(&list, 1);
    insert(&list, 2);
    insert(&list, 3);
    printList(&list);
    return 0;
}
