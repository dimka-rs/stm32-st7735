#ifndef LCD_H
#define LCD_H

void lcd_init();
void lcd_fill(uint16_t color);
void lcd_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void lcd_dot(uint16_t x, uint16_t y, uint16_t color);

#endif // LCD_H