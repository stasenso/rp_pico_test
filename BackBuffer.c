#include "BackBuffer.h"
#include <math.h>

uint16_t frame_buffer[WIDTH * HEIGHT]; // Буфер для экрана
// Установка пикселя в буфере (с проверкой границ)

unsigned short reverse(unsigned short x)
{
    x = (x & 0xFF) << 8 | (x & 0xFF00) >>  8;
    return x;
}

void set_pixel(uint16_t x, uint16_t y, uint16_t color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        frame_buffer[y * WIDTH + x] = color;
    }
}

void generate_sine_wave_points(uint16_t num_points, int amplitude, float frequency, int offset_x, int offset_y, float phase_shift) {
    if (num_points == 0) {
        return;
    }

    float step = (2.0f * M_PI * frequency) / (num_points - 1);
    float x_step = (float)WIDTH / (num_points - 1);

    for (size_t i = 0; i < num_points; i++) {
        int x = offset_x + (int)(i * x_step);
        int y = offset_y + (int)(amplitude * sinf(i * step + phase_shift)); // Добавлен сдвиг фазы
        set_pixel(x, y, reverse(0b0000011111100000));
    }
}

// Функция для вычисления базисного полинома Бернштейна
float bernstein(int i, int n, float t) {
    // Вычисление биномиального коэффициента C(n, i)
    float binomial = 1.0f;
    for (int j = 0; j < i; j++) {
        binomial *= (n - j) / (float)(j + 1);
    }
    return binomial * powf(t, i) * powf(1.0f - t, n - i);
}

// Рисование кривой Безье
void draw_bezier(const int *points_x, const int *points_y, size_t num_points, uint16_t color) {
    if (num_points < 2) {
        return; // Кривая требует минимум 2 точки
    }

    const int steps = 1000; // Количество шагов для построения кривой

    for (int step = 0; step <= steps; step++) {
        float t = step / (float)steps;
        float x = 0.0f;
        float y = 0.0f;

        // Вычисление координат точки на кривой
        for (size_t i = 0; i < num_points; i++) {
            float b = bernstein(i, num_points - 1, t);
            x += b * points_x[i];
            y += b * points_y[i];
        }

        // Установка пикселя на экране
        set_pixel((int)(x + 0.5f), (int)(y + 0.5f), color);
    }
}

void grid (uint16_t x, uint16_t y, uint16_t step, uint16_t color){
    for (uint16_t vgrid = x; vgrid < WIDTH; vgrid+=step)
    {
        for (uint16_t hgrid = 0;  hgrid< HEIGHT; hgrid++)
        {
            set_pixel(vgrid,hgrid,reverse(color));
        }
    }

    for (uint16_t hgrid = y;  hgrid< HEIGHT; hgrid+=step)
    {
        for (uint16_t vgrid = 0; vgrid < WIDTH; vgrid++)
        {
            set_pixel(vgrid,hgrid,reverse(color));
        }  
    }
}