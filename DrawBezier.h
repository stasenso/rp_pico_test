#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include "Thread.h"


float bernstein(int i, int n, float t);
void draw_bezier(const int *points_x, const int *points_y, size_t num_points, uint16_t color);