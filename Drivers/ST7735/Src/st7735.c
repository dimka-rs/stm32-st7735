#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "st7735.h"

extern SPI_HandleTypeDef hspi1;

static uint8_t
st7735_send(uint8_t *data, uint8_t len, uint8_t is_data)
{
    HAL_GPIO_WritePin(GPIOB, LCD_DC_Pin, is_data ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, data, len, 1000);
    HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_SET);
    return 0;
}

uint8_t
st7735_init(void)
{
    HAL_GPIO_WritePin(GPIOB, LCD_RES_Pin, GPIO_PIN_SET);
    st7735_send_cmd(CMD_SWRESET);
    HAL_Delay(120);
    st7735_send_cmd(CMD_SLPOUT);
    HAL_Delay(120);
    st7735_send_cmd(CMD_DISPON);
    return 0;
}

uint8_t
st7735_send_data(uint8_t *data, uint8_t len)
{
    return st7735_send(data, len, 1);
}

uint8_t
st7735_send_cmd(uint8_t cmd)
{
    return st7735_send(&cmd, 1, 0);
}