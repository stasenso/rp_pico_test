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
    int points_x[60];
    int points_y[60];
    size_t num_points = 640;
    uint16_t color = reverse(0b0000011111100000);
    stdio_init_all();
    multicore_launch_core1(coreEntry); //Запускаю в ядре 1 процесс вывода на экран
    float x=0.0;
    float freq=1.0;
    bool minmax=false;
    while (x<500)
    {
        data = multicore_fifo_pop_blocking();
        
        fillBufer(frame_buffer,reverse(0x4A69));//
        generate_sine_wave_points(num_points, 50, freq, 0, HEIGHT / 2,x);
        //draw_bezier(points_x, points_y, num_points, color);
        multicore_fifo_push_blocking(0); //Экран 0 нарисован       
        x+=0.03;
        if (minmax)
        {
            if (freq<=0.0){
            minmax=false;}
            else freq-=0.005;
        }
        else
        {
            if (freq>=10.0){
            minmax=true;}
            else freq+=0.005;
        }
        //sleep_ms(20);   
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
