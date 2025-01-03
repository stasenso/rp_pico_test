#ifndef __BACKBUFFER_H__
#define __BACKBUFFER_H__

#include <stdint.h>
#include <stddef.h>

#define WIDTH  320
#define HEIGHT 240
#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF

extern uint16_t frame_buffer[WIDTH * HEIGHT];

float bernstein(int i, int n, float t);
void draw_bezier(const int *points_x, const int *points_y, size_t num_points, uint16_t color);
unsigned short reverse(unsigned short x);
void set_pixel(uint16_t x, uint16_t y, uint16_t color);
void generate_sine_wave_points(uint16_t num_points, int amplitude, float frequency, int offset_x, int offset_y, float phase_shift);

#endif // __BACKBUFFER_H__