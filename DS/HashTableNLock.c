typedef struct {
    Entry* buckets[TABLE_SIZE];
    pthread_mutex_t locks[TABLE_SIZE];
} HashTable;

void initTable(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
        pthread_mutex_init(&table->locks[i], NULL);
    }
}

void insert(HashTable* table, int key, int value) {
    int index = hash(key);
    pthread_mutex_lock(&table->locks[index]);
    Entry* newEntry = (Entry*)malloc(sizeof(Entry));
    newEntry->key = key;
    newEntry->value = value;
    newEntry->next = table->buckets[index];
    table->buckets[index] = newEntry;
    pthread_mutex_unlock(&table->locks[index]);
}
