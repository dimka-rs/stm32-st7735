#ifndef ST7735_H
#define ST7735_H

uint8_t st7735_init(void);
uint8_t st7735_send_data(uint8_t *data, uint8_t len);
uint8_t st7735_send_cmd(uint8_t cmd);

enum st7735_cmds
{
    CMD_NOP     = 0x00,
    CMD_SWRESET = 0x01,
    CMD_SLPIN   = 0x10,
    CMD_SLPOUT  = 0x11,
    CMD_NORON   = 0x13,
    CMD_INVOFF  = 0x20,
    CMD_INVON   = 0x21,
    CMD_DISPOFF = 0x28,
    CMD_DISPON  = 0x29,
};

#endif /* ST7735_H */