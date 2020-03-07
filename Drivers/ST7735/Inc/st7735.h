#ifndef ST7735_H
#define ST7735_H

typedef struct st7735_driver_struct
{
    void(*send)(uint8_t cmd, uint8_t *data, uint16_t len, uint16_t count);
    void(*reset)(void);
    void(*wait_ms)(uint16_t ms);
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
} st7735_driver;

void st7735_init(st7735_driver *self);
void st7735_fill(st7735_driver *self, uint16_t color);
void st7735_dot(st7735_driver *self, uint16_t x, uint16_t y, uint16_t color);
void st7735_rect(st7735_driver *self, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

#endif /* ST7735_H */