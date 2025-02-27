#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Node {
    int data;
    struct Node* next;
    pthread_mutex_t lock;
} Node;

typedef struct {
    Node* head;
} LinkedList;

void initList(LinkedList* list) {
    list->head = NULL;
}

void insert(LinkedList* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    pthread_mutex_init(&newNode->lock, NULL);

    if (list->head != NULL) {
        pthread_mutex_lock(&list->head->lock);
    }

    newNode->next = list->head;
    list->head = newNode;

    if (newNode->next != NULL) {
        pthread_mutex_unlock(&newNode->next->lock);
    }
}

void printList(LinkedList* list) {
    Node* temp = list->head;
    while (temp) {
        pthread_mutex_lock(&temp->lock);
        printf("%d -> ", temp->data);
        Node* next = temp->next;
        pthread_mutex_unlock(&temp->lock);
        temp = next;
    }
    printf("NULL\n");
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
