#ifndef ST7735_PRIV_H
#define ST7735_PRIV_H

/* Read commands omited since not supported by HW */
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
    CMD_GAMSET  = 0x26, /* 1: GC[3:0] */
    CMD_DISPOFF = 0x28,
    CMD_DISPON  = 0x29,
    CMD_CASET   = 0x2A, /* 1: XSH, 2: XSL, 3: XEH, 4: XEL */
    CMD_RASET   = 0x2B, /* 1: YSH, 2: YSL, 3: YEH, 4: YEL */
    CMD_RAMWR   = 0x2C, /* 1...N: data */
    CMD_PTLAR   = 0x30, /* 1: LSH, 2: LSL, 3: LEH, 4: LEL */
    CMD_TEOFF   = 0x34,
    CMD_TEON    = 0x35, /* 1: TELOM[0] */
    CMD_MADCTL  = 0x36, /* 1: MY[7], MX[6], MV[5], ML[4], RGB[3], MH[2] */
    CMD_IDMOFF  = 0x38,
    CMD_IDMON   = 0x39,
    CMD_COLMOD  = 0x3A, /* 1: IFPF2[2:0] */
};

#endif //ST7735_PRIV_H