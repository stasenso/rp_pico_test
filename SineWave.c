#include "SineWave.h"
#include "font_data.h"
#include "Thread.h"
#include "Reverse.h"
#include "SetPixel.h"
#include <math.h>
void generate_sine_wave_points(size_t num_points, int amplitude, float frequency, int offset_x, int offset_y, float phase_shift) {
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
