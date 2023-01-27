#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 20

size_t strlen(const char* str){
    size_t len = 0;
    while (str[len]) len++;
    return len;
}

void kernel_main();

#endif