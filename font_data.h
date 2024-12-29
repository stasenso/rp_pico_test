#ifndef FONT_DATA_H
#define FONT_DATA_H

#include <stdint.h>

extern const uint16_t font_width;
extern const uint16_t font_height;
extern const uint8_t font_data[];

void draw_string(uint16_t x, uint16_t y, const char *str);
void draw_char(uint8_t x, uint8_t y, char c);
#endif // FONT_DATA_H
