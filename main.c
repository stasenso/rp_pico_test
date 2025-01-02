#include "main.h"
#include "Thread.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include "DrawBezier.h"
#include "font_data.h"
#include "Reverse.h"
int main() {
    uint16_t red = 0;
    uint16_t green = 0;
    uint16_t blue = 0;
    uint16_t summcolor=0;
    uint32_t data;
    // Точки для кривой Безье
    int points_x[60];
    int points_y[60];
    size_t num_points = 1600;
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
        draw_string(20,110,L"Кириллица работает!!!",0b1111111111111111); //
        draw_string(50,130,L"Does Latin work?",0b0000000000011111); //Does Latin work?
        draw_string(20,150,L"Проверка 0123456789!",0b1111100000000000); //Does Latin work?
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

