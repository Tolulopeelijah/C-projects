#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10  // Define the size of the hash table

// ==========================
// 1. Define the Hash Table Structure
// ==========================

typedef struct HashNode {
    char* key;
    int value;
    struct HashNode* next; // Pointer for chaining
} HashNode;

typedef struct HashTable {
    HashNode* table[TABLE_SIZE]; // Array of pointers to HashNodes
} HashTable;

// ==========================
// 2. Implement the Hash Function
// ==========================

unsigned int hash_function(const char* key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % TABLE_SIZE;
}

// ==========================
// 3. Initialize the Hash Table
// ==========================

HashTable* create_table() {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    if (!hashTable) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

// ==========================
// 4. Insert Key-Value Pairs
// ==========================

HashNode* create_node(const char* key, int value) {
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insert(HashTable* hashTable, const char* key, int value) {
    unsigned int index = hash_function(key);
    HashNode* newNode = create_node(key, value);
    if (!newNode) return;
    
    if (!hashTable->table[index]) {
        hashTable->table[index] = newNode;
    } else {
        HashNode* temp = hashTable->table[index];
        while (temp) {
            if (strcmp(temp->key, key) == 0) {
                temp->value = value;
                free(newNode->key);
                free(newNode);
                return;
            }
            if (!temp->next) break;
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// ==========================
// 5. Search for a Key
// ==========================

int search(HashTable* hashTable, const char* key) {
    unsigned int index = hash_function(key);
    HashNode* temp = hashTable->table[index];
    while (temp) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        }
        temp = temp->next;
    }
    return -1;
}

// ==========================
// 6. Delete a Key
// ==========================

void delete(HashTable* hashTable, const char* key) {
    unsigned int index = hash_function(key);
    HashNode* temp = hashTable->table[index];
    HashNode* prev = NULL;
    while (temp) {
        if (strcmp(temp->key, key) == 0) {
            if (prev) {
                prev->next = temp->next;
            } else {
                hashTable->table[index] = temp->next;
            }
            free(temp->key);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

// ==========================
// 7. Display the Hash Table
// ==========================

void display(HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        HashNode* temp = hashTable->table[i];
        while (temp) {
            printf("(%s, %d) -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// ==========================
// 8. Free Memory
// ==========================

void free_table(HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* temp = hashTable->table[i];
        while (temp) {
            HashNode* next = temp->next;
            free(temp->key);
            free(temp);
            temp = next;
        }
    }
    free(hashTable);
}

// ==========================
// 9. Test the Implementation (Main Function)
// ==========================

int main() {
    HashTable* hashTable = create_table();
    
    insert(hashTable, "Alice", 25);
    insert(hashTable, "Bob", 30);
    insert(hashTable, "Charlie", 35);
    insert(hashTable, "David", 40);
    insert(hashTable, "Alice", 28);
    
    printf("\nHash Table:\n");
    display(hashTable);
    
    printf("\nSearching for Bob: %d\n", search(hashTable, "Bob"));
    printf("Searching for Eve: %d\n", search(hashTable, "Eve"));
    
    printf("\nDeleting Charlie...\n");
    delete(hashTable, "Charlie");
    
    printf("\nHash Table After Deletion:\n");
    display(hashTable);
    
    free_table(hashTable);
    return 0;
}
