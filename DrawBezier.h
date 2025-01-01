#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>
#include "Thread.h"

void set_pixel(uint16_t x, uint16_t y, uint16_t color);
float bernstein(int i, int n, float t);
void draw_bezier(const int *points_x, const int *points_y, size_t num_points, uint16_t color);