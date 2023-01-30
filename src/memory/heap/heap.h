#ifndef SANDERS_HEAP_H
#define SANDERS_HEAP_H

#include "config.h"
#include <stdint.h>
#include <stddef.h>

#define HEAP_BLOCK_TABLE_ENTRY_TAKEN 0x01
#define HEAP_BLOCK_TABLE_ENTRY_FREE  0x00

#define HEAP_BLOCK_HAS_NEXT 0b100000000
#define HEAP_BLOCK_IS_FIRST  0b010000000

typedef unsigned char HEAP_BLOCK_TABLE_ENTRY;

struct heap_table {
    HEAP_BLOCK_TABLE_ENTRY* entries;
    size_t number_of_entries;
};

struct heap {
    struct heap_table* table;
    void* saddr;
};

int heap_create(struct heap* heap, void* ptr, void* end, struct heap_table* table);

void* heap_malloc(struct heap* heap, size_t size);
void heap_free(struct heap* heap, void* ptr);

#endif //SANDERS_HEAP_H
