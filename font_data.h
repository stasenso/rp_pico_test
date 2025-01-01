#ifndef FONT_DATA_H
#define FONT_DATA_H

#include <stdint.h>
#include <wchar.h>
extern const uint16_t font_width;
extern const uint16_t font_height;
extern const uint8_t font_data[];

void draw_string(uint16_t x, uint16_t y, const wchar_t *str);
void draw_char(uint16_t x, uint16_t y,uint8_t wdh, wchar_t c);
uint8_t get_char_width(wchar_t c);
#endif // FONT_DATA_H
