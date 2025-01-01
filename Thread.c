#include "Thread.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pico/multicore.h"

uint16_t frame_buffer[WIDTH * HEIGHT]; // Буфер для экрана

//uint16_t frame_buffer1[WIDTH * HEIGHT]; // Буфер для экрана1

void coreEntry(){
    st7789_init(); // Initialize SPI and GPIO
    gpio_put(PIN_BL, 1); // Подсветка
    multicore_fifo_push_blocking(0); //Экран 0 свободен
    //multicore_fifo_push_blocking(1); //Экран 1 свободен

    while (true)
    {
        uint32_t data = multicore_fifo_pop_blocking();
        if (data==0)
        {
            st7789_send_framebuffer(frame_buffer); //Рисую экран 0
            multicore_fifo_push_blocking(0); //Экран 0 свободен
        }
        /*else if (data==1)
        {
            st7789_send_framebuffer(frame_buffer1); // Рисую первый экран
            multicore_fifo_push_blocking(1); //Экран 1 свободен
        }*/
        else
        {
            multicore_reset_core1(); // Сброс и остановка ядра 1
        }
        
    }
    

}

void st7789_init() {
    // Initialize SPI
    spi_init(SPI_PORT, 1000 * 100 * 625); // 62.5MHz
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);

    // Initialize control pins
    gpio_init(PIN_CS);
    gpio_init(PIN_DC);
    gpio_init(PIN_RST);
    gpio_init(PIN_BL);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_set_dir(PIN_DC, GPIO_OUT);
    gpio_set_dir(PIN_RST, GPIO_OUT);
    gpio_set_dir(PIN_BL, GPIO_OUT);

    // Reset the display
    gpio_put(PIN_RST, 0);
    sleep_ms(50);
    gpio_put(PIN_RST, 1);
    sleep_ms(50);

    // Initialize ST7789 commands
    st7789_send_command(0x01); // Software reset
    sleep_ms(150);
    st7789_send_command(0x11); // Exit sleep mode
    sleep_ms(150);

    st7789_send_command(0x36); // Memory data access control 215
    st7789_send_data(0b10100000); // RGB
    //st7789_send_data(0b00101000); // BGR

    st7789_send_command(0x3A); // Interface pixel format
    st7789_send_data(0b01010101);    // 16-bit/pixel

       /*/ Настройка гаммы
    st7789_send_command(0x26); // Gamma set
    st7789_send_data(0x02); // Gamma curve 1 (User-defined)

    st7789_send_command(0xE0); // Positive gamma correction
    st7789_send_data(0xD0); // V0
    st7789_send_data(0x00); // V1
    st7789_send_data(0x02); // V2
    st7789_send_data(0x07); // V4
    st7789_send_data(0x0a); // V6
    st7789_send_data(0x29); // V13
    st7789_send_data(0x32); // V20
    st7789_send_data(0x44); // V36
    st7789_send_data(0x42); // V43
    st7789_send_data(0x06); // V50
    st7789_send_data(0x0e); // V57
    st7789_send_data(0x12); // V64
    st7789_send_data(0x14); // V71
    st7789_send_data(0x17); // V78

    st7789_send_command(0xE1); // Negative gamma correction
    st7789_send_data(0xD0); // V0
    st7789_send_data(0x00); // V1
    st7789_send_data(0x02); // V2
    st7789_send_data(0x07); // V4
    st7789_send_data(0x0a); // V6
    st7789_send_data(0x28); // V13
    st7789_send_data(0x31); // V20
    st7789_send_data(0x54); // V36
    st7789_send_data(0x47); // V43
    st7789_send_data(0x0e); // V50
    st7789_send_data(0x1c); // V57
    st7789_send_data(0x17); // V64
    st7789_send_data(0x1b); // V71
    st7789_send_data(0x1e); // V78*/

    st7789_send_command(0x21); //INVON (21h): Display Inversion On
    st7789_send_command(0x29); // Display ON
}

void st7789_send_command(uint8_t cmd) {
    gpio_put(PIN_DC, 0);
    gpio_put(PIN_CS, 0);
    spi_write_blocking(SPI_PORT, &cmd, 1);
    gpio_put(PIN_CS, 1);
}

void st7789_send_data(uint8_t data) {
    gpio_put(PIN_DC, 1);
    gpio_put(PIN_CS, 0);
    spi_write_blocking(SPI_PORT, &data, 1);
    gpio_put(PIN_CS, 1);
}

void st7789_send_framebuffer(uint16_t *buffer) {
    // Установить область для записи на весь экран
    st7789_send_command(0x2A); // Column address set
    st7789_send_data(0x00);
    st7789_send_data(0x00);           // X-start = 0
    st7789_send_data((WIDTH - 1) >> 8);
    st7789_send_data((WIDTH - 1) & 0xFF); // X-end = WIDTH-1

    st7789_send_command(0x2B); // Row address set
    st7789_send_data(0x00);
    st7789_send_data(0x00);           // Y-start = 0
    st7789_send_data((HEIGHT - 1) >> 8);
    st7789_send_data((HEIGHT - 1) & 0xFF); // Y-end = HEIGHT-1

    // Команда записи данных в память дисплея
    st7789_send_command(0x2C); // Memory write

    // Передача буфера на дисплей
    gpio_put(PIN_DC, 1); // Режим данных
    gpio_put(PIN_CS, 0); // Выбор устройства

    // Отправка буфера по SPI
    spi_write_blocking(SPI_PORT, (uint8_t *)buffer, WIDTH * HEIGHT * 2);

    gpio_put(PIN_CS, 1); // Завершить передачу
}