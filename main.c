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
    int points_x[] = {0,50, 150, 250, 300,320};
    int points_y[] = {0,200, 50, 50, 200,240};
    size_t num_points = sizeof(points_x) / sizeof(points_x[0]);
    uint16_t color = reverse(0b0000011111100000);
    stdio_init_all();
    multicore_launch_core1(coreEntry); //Запускаю в ядре 1 процесс вывода на экран

        data = multicore_fifo_pop_blocking();
        
        fillBufer(frame_buffer,reverse(0x4A69));//
        draw_bezier(points_x, points_y, num_points, color);
        multicore_fifo_push_blocking(0); //Экран 0 нарисован
        red+=1;
        sleep_ms(40);       
    
    
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

