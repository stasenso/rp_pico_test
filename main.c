#include "main.h"
#include "Thread.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include "DrawBezier.h"

int main() {
    uint16_t red = 0;
    uint16_t green = 0;
    uint16_t blue = 0;
    uint16_t summcolor=0;
    uint32_t data;
    // Точки для кривой Безье
    int points_x[30];
    int points_y[30];
    size_t num_points = 30;
    uint16_t color = reverse(0b0000011111100000);
    stdio_init_all();
    multicore_launch_core1(coreEntry); //Запускаю в ядре 1 процесс вывода на экран
    int x=0;
    while (x<50)
    {
        data = multicore_fifo_pop_blocking();
        generate_sine_wave_points(points_x, points_y, num_points, 50, 1, x, HEIGHT / 2);
        fillBufer(frame_buffer,reverse(0x4A69));//
        draw_bezier(points_x, points_y, num_points, color);
        multicore_fifo_push_blocking(0); //Экран 0 нарисован       
        x+=5;   
    }
    
    while (1) {
        tight_loop_contents();
    }
}

void fillBufer (uint16_t* buffer,uint16_t color){
    for (uint16_t  y = 0; y < HEIGHT; y++)
    {
        for (uint16_t x = 0; x < WIDTH; x++)
        {
            buffer[y*WIDTH+x]=color;
        }        
    }
    
}

unsigned short reverse(unsigned short x)
{
    x = (x & 0xFF) << 8 | (x & 0xFF00) >>  8;
    return x;
}

void generate_sine_wave_points(int *points_x, int *points_y, size_t num_points, int amplitude, int frequency, int offset_x, int offset_y) {
    if (num_points == 0) {
        return;
    }

    float step = (2.0f * M_PI * frequency) / (num_points - 1);

    for (size_t i = 0; i < num_points; i++) {
        points_x[i] = offset_x + i * (WIDTH / num_points);
        points_y[i] = offset_y + (int)(amplitude * sinf(i * step));
    }
}