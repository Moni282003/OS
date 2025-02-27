#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TABLE_SIZE 10

typedef struct Entry {
    int key;
    int value;
    struct Entry* next;
} Entry;

typedef struct {
    Entry* buckets[TABLE_SIZE];
    pthread_mutex_t lock;
} HashTable;

void initTable(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    pthread_mutex_init(&table->lock, NULL);
}

int hash(int key) {
    return key % TABLE_SIZE;
}

void insert(HashTable* table, int key, int value) {
    pthread_mutex_lock(&table->lock);
    int index = hash(key);
    Entry* newEntry = (Entry*)malloc(sizeof(Entry));
    newEntry->key = key;
    newEntry->value = value;
    newEntry->next = table->buckets[index];
    table->buckets[index] = newEntry;
    pthread_mutex_unlock(&table->lock);
}

int get(HashTable* table, int key) {
    pthread_mutex_lock(&table->lock);
    int index = hash(key);
    Entry* temp = table->buckets[index];
    while (temp) {
        if (temp->key == key) {
            pthread_mutex_unlock(&table->lock);
            return temp->value;
        }
        temp = temp->next;
    }
    pthread_mutex_unlock(&table->lock);
    return -1;
}

int main() {
    HashTable table;
    initTable(&table);
    insert(&table, 1, 100);
    insert(&table, 2, 200);
    printf("Value for key 1: %d\n", get(&table, 1));
    printf("Value for key 2: %d\n", get(&table, 2));
    return 0;
}
