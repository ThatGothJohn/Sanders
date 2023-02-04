#include "kheap.h"
#include "heap.h"
#include "config.h"
#include "kernel.h"
#include "../memory.h"

struct heap kernel_heap;

struct heap_table kernel_heap_table;

void kheap_init(){
    int total_heap_entries = SANDERS_HEAP_SIZE_BYTES / SANDERS_HEAP_BLOCK_SIZE;
    kernel_heap_table.entries = (HEAP_BLOCK_TABLE_ENTRY*) SANDERS_HEAP_TABLE_ADDRESS;
    kernel_heap_table.number_of_entries = total_heap_entries;

    void* end = (void*) (SANDERS_HEAP_ADDRESS + SANDERS_HEAP_SIZE_BYTES);
    int res = heap_create(&kernel_heap, (void*) SANDERS_HEAP_ADDRESS, end, &kernel_heap_table);
    if (res < 0){
        print("\nFailed to create kernel heap|\n");
    }
}

void* kmalloc(size_t size){
    return heap_malloc(&kernel_heap, size);
}

void* kzalloc(size_t size){
    void* ptr = kmalloc(size);
    if (!ptr)
        return 0;
    memset(ptr, 0, size);
    return ptr;
}

void kfree(void* ptr){
    heap_free(&kernel_heap, ptr);
}