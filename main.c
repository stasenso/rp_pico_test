#include "main.h"
#include "Thread.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"

int main() {
    uint16_t red = 0;
    uint16_t green = 0;
    uint16_t blue = 0;
    uint16_t summcolor=0;
    uint32_t data;
    stdio_init_all();
    multicore_launch_core1(coreEntry); //Запускаю в ядре 1 процесс вывода на экран
 
    while (red<32)
    {
        //uint8_t red_value = (pixel & red_mask) >> 11;
        //uint8_t green_value = (pixel & green_mask) >> 5;
        //uint8_t blue_value = (pixel & blue_mask);
        data = multicore_fifo_pop_blocking();
        fillBufer(frame_buffer,reverse(summcolor & 0b0000011111111111 | red << 11));//;
        multicore_fifo_push_blocking(0); //Экран 0 нарисован
        /*data = multicore_fifo_pop_blocking();
        fillBufer(frame_buffer1,0x0000);
        multicore_fifo_push_blocking(1); //Экран 0 нарисован*/
        red+=1;
        sleep_ms(20);       
    }

    while (green<64)
    {
        data = multicore_fifo_pop_blocking();
        fillBufer(frame_buffer,reverse(summcolor & 0b1111100000011111 | green << 5)); //
        multicore_fifo_push_blocking(0); //Экран 0 нарисован
        green+=1;
        sleep_ms(20);
    }

    while (blue<32)
    {
        data = multicore_fifo_pop_blocking();
        fillBufer(frame_buffer,reverse(summcolor & 0b1111111111100000 | blue)); //
        multicore_fifo_push_blocking(0); //Экран 0 нарисован
        blue+=1;
        sleep_ms(20);
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

