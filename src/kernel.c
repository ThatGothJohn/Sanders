#include "kernel.h"

uint16_t* v_mem;

uint16_t terminal_row, terminal_column;

uint16_t terminal_make_char(char c, char color){
    return (color << 8) | c;
}

void terminal_putchar(int x, int y, char c, char color){
    v_mem[(y*VGA_WIDTH) + x] = terminal_make_char(c, color);
}

void terminal_writechar(char c, char color){
    if (c == '\n'){
        terminal_row+=1;
        terminal_column = 0;
        return;
    }
    terminal_putchar(terminal_column, terminal_row, c, color);
    terminal_column+=1;
    if (terminal_column >= VGA_WIDTH){
        terminal_column = 0;
        terminal_row += 1;
    }
}

void print(const char* str){
    size_t len = strlen(str);
    for (int i = 0; i < len; ++i) {
        terminal_writechar(str[i], 15);
    }
}

void terminal_init(){
    v_mem = (uint16_t*)(0xB8000);
    terminal_row = 0;
    terminal_column = 0;

    for (int y = 0; y < VGA_HEIGHT; ++y) {
        for (int x = 0; x < VGA_WIDTH; ++x) {
            terminal_putchar(x,y,' ',0);
        }
    }
}

void kernel_main() {
    terminal_init();
    print("Hello World!\nKEKW");
}