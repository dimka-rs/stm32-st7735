#include "stm32f1xx_hal.h"
#include "st7735.h"
#include "st7735_priv.h"

void
st7735_init(st7735_driver *self)
{
    uint8_t data[4];
    self->reset();

    self->send(CMD_SWRESET, NULL, 0);
    self->wait_ms(120);

    self->send(CMD_SLPOUT, NULL, 0);
    self->wait_ms(120);

    data[0] = 0x0;
    self->send(CMD_MADCTL, data, 1);

    data[0] = 5; /* 16 bit/pixel */
    self->send(CMD_COLMOD, data, 1);

    data[0] = self->y >> 8;
    data[1] = self->y & 0xFF;
    data[2] = (self->y + self->h) >> 8;
    data[3] = (self->y + self->h) & 0xFF;
    self->send(CMD_PTLAR, data, 4);

    self->send(CMD_DISPON, NULL, 0);
    return;
}

void
st7735_fill(st7735_driver *self, uint16_t color)
{
    for (uint16_t x = 0; x < self->w; x++)
    {
        for (uint16_t y = 0; y < self->h; y++)
        {
            st7735_dot(self, x + self->x, y + self->y, color);
        }
    }
    return;
}

void
st7735_dot(st7735_driver *self, uint16_t x, uint16_t y, uint16_t color)
{
    uint8_t data[4];

    data[0] = x >> 8;
    data[1] = x & 0xFF;
    data[2] = data[0];
    data[3] = data[1];
    self->send(CMD_CASET, data, 4);

    data[0] =  y >> 8;
    data[1] =  y & 0xFF;
    data[2] = data[0];
    data[3] = data[1];
    self->send(CMD_RASET, data, 4);

    data[0] =  color >> 8;
    data[1] =  color & 0xFF;
    self->send(CMD_RAMWR, data, 2);
    return;
}