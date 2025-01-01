#include "DrawBezier.h"
#include "SetPixel.h"
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