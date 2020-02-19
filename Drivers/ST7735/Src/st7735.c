#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "st7735.h"

extern SPI_HandleTypeDef hspi1;

uint8_t
st7735_send(uint8_t cmd, uint8_t *data, uint8_t len)
{
    HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, LCD_DC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, &cmd, 1, 1000);
    HAL_GPIO_WritePin(GPIOB, LCD_DC_Pin, GPIO_PIN_SET);
    
    if (data != NULL && len != 0)
        HAL_SPI_Transmit(&hspi1, data, len, 10000);

    HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_SET);
    return 0;
}

uint8_t
st7735_fill(uint16_t color)
{
    uint8_t cmd = CMD_RAMWR;

    HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, LCD_DC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, &cmd, 1, 1000);
    HAL_GPIO_WritePin(GPIOB, LCD_DC_Pin, GPIO_PIN_SET);
    
    for (int i = 0; i < 128*160; i++)
        HAL_SPI_Transmit(&hspi1, color, sizeof(color), 1000);

    HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_SET);
    return 0;
}

uint8_t
st7735_init(void)
{
    uint8_t data[4];

    HAL_GPIO_WritePin(GPIOB, LCD_RES_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOB, LCD_RES_Pin, GPIO_PIN_SET);
    st7735_send(CMD_SWRESET, NULL, 0);
    HAL_Delay(120);

    st7735_send(CMD_SLPOUT, NULL, 0);
    HAL_Delay(120);

    data[0] = 0x08;
    st7735_send(CMD_MADCTL, data, 1);

    data[0] = 5; /* 16 bit/pixel */
    st7735_send(CMD_COLMOD, data, 1);

    data[0] = 0;
    data[1] = 20;
    data[2] = 0;
    data[3] = 110;
    st7735_send(CMD_CASET, data, 4);

    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 160;
    st7735_send(CMD_RASET, data, 4);

    st7735_send(CMD_DISPON, NULL, 0);    
    return 0;
}
