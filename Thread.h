#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#define SPI_PORT spi0
#define PIN_MISO -1
#define PIN_MOSI 19
#define PIN_SCK  18
#define PIN_CS   17
#define PIN_DC   22
#define PIN_RST  13
#define PIN_BL   12

#define WIDTH  320
#define HEIGHT 240
#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF

extern uint16_t frame_buffer[WIDTH * HEIGHT];
extern uint16_t frame_buffer1[WIDTH * HEIGHT];

void st7789_send_command(uint8_t cmd);
void st7789_send_data(uint8_t data);
void st7789_send_framebuffer(uint16_t *buffer);
void coreEntry();
void st7789_init();

#endif