#include "SetPixel.h"
#include "Thread.h"
// Установка пикселя в буфере (с проверкой границ)
void set_pixel(uint16_t x, uint16_t y, uint16_t color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        frame_buffer[y * WIDTH + x] = color;
    }
}
