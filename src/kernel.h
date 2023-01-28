#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 20

size_t strlen(const char* str);

void print(const char* str);

void kernel_main();

#endif