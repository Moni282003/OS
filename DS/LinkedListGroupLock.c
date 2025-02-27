#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define GROUP_SIZE 3  // Number of nodes per group lock

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    pthread_mutex_t group_locks[GROUP_SIZE];
} LinkedList;

void initList(LinkedList* list) {
    list->head = NULL;
    for (int i = 0; i < GROUP_SIZE; i++) {
        pthread_mutex_init(&list->group_locks[i], NULL);
    }
}

void insert(LinkedList* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    int group_index = value % GROUP_SIZE;  // Assign lock based on value
    pthread_mutex_lock(&list->group_locks[group_index]);

    newNode->next = list->head;
    list->head = newNode;

    pthread_mutex_unlock(&list->group_locks[group_index]);
}

void printList(LinkedList* list) {
    Node* temp = list->head;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    LinkedList list;
    initList(&list);
    insert(&list, 1);
    insert(&list, 2);
    insert(&list, 3);
    insert(&list, 4);
    insert(&list, 5);
    printList(&list);
    return 0;
}
