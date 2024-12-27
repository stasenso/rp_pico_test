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
 
    while (red<32) //Red ++
    {

        data = multicore_fifo_pop_blocking();
        summcolor=summcolor & 0b0000011111111111 | red << 11;
        fillBufer(frame_buffer,reverse(summcolor));//;
        multicore_fifo_push_blocking(0); //Экран 0 нарисован
        red+=1;
        sleep_ms(40);       
    }

    sleep_ms (1000);
    while (green<64) //Red+Green
    {
        data = multicore_fifo_pop_blocking();
        summcolor=summcolor & 0b1111100000011111 | green << 5;
        fillBufer(frame_buffer,reverse(summcolor)); //
        multicore_fifo_push_blocking(0); //Экран 0 нарисован
        green+=1;
        sleep_ms(20);
    }

    sleep_ms (1000);
    red=32;
        while (red!=0)      //Green++
    {
        red-=1;
        data = multicore_fifo_pop_blocking();
        summcolor=(summcolor & 0b0000011111111111) | (red << 11);
        fillBufer(frame_buffer,reverse(summcolor));//;
        multicore_fifo_push_blocking(0); //Экран 0 нарисован
        sleep_ms(20);       
    }
    
    sleep_ms (1000);
    while (blue<32)     //Green+blue
    {
        data = multicore_fifo_pop_blocking();
        summcolor=summcolor & 0b1111111111100000 | blue;
        fillBufer(frame_buffer,reverse(summcolor)); //
        multicore_fifo_push_blocking(0); //Экран 0 нарисован
        blue+=1;
        sleep_ms(40);
    }

    sleep_ms (1000);
    green=64;
    while (green!=0)      //blue++
    {
        green-=1;
        data = multicore_fifo_pop_blocking();
        summcolor=summcolor & 0b1111100000011111 | green << 5;
        fillBufer(frame_buffer,reverse(summcolor));//;
        multicore_fifo_push_blocking(0); //Экран 0 нарисован
        sleep_ms(20);       
    }

    sleep_ms (1000);
    red=0;
    while (red<32) //Red+Blue
    {

        data = multicore_fifo_pop_blocking();
        summcolor=summcolor & 0b0000011111111111 | red << 11;
        fillBufer(frame_buffer,reverse(summcolor));//;
        multicore_fifo_push_blocking(0); //Экран 0 нарисован
        red+=1;
        sleep_ms(40);       
    }

    sleep_ms (1000);
    green=0;
    while (green<64) //Red+Green
    {
        data = multicore_fifo_pop_blocking();
        summcolor=summcolor & 0b1111100000011111 | green << 5;
        fillBufer(frame_buffer,reverse(summcolor)); //
        multicore_fifo_push_blocking(0); //Экран 0 нарисован
        green+=1;
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

