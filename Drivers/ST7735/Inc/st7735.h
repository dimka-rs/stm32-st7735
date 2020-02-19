#ifndef ST7735_H
#define ST7735_H

uint8_t st7735_init(void);
uint8_t st7735_send(uint8_t cmd, uint8_t *data, uint8_t len);
uint8_t st7735_fill(uint16_t color);

enum st7735_cmds
{
    CMD_NOP     = 0x00,
    CMD_SWRESET = 0x01,
    CMD_SLPIN   = 0x10,
    CMD_SLPOUT  = 0x11,
    CMD_PTLON   = 0x12,
    CMD_NORON   = 0x13,
    CMD_INVOFF  = 0x20,
    CMD_INVON   = 0x21,
    CMD_GAMSET  = 0x26,
    CMD_DISPOFF = 0x28,
    CMD_DISPON  = 0x29,
    CMD_CASET   = 0x2A,
    CMD_RASET   = 0x2B,
    CMD_RAMWR   = 0x2C,
    CMD_MADCTL  = 0x36,
    CMD_COLMOD  = 0x3A,
};

#endif /* ST7735_H */