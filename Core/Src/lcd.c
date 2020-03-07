#include "stm32f1xx_hal.h"
#include "lcd.h"
#include "st7735.h"
#include "gpio.h"

extern SPI_HandleTypeDef hspi1;

st7735_driver lcd;

static void
lcd_send(uint8_t cmd, uint8_t *data, uint8_t len)
{
    /* Select Chip */
    HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_RESET);
    /* Command Mode */
    HAL_GPIO_WritePin(GPIOB, LCD_DC_Pin, GPIO_PIN_RESET);
    /* Send Command */
    HAL_SPI_Transmit(&hspi1, &cmd, 1, 1000);
    /* Data Mode */
    HAL_GPIO_WritePin(GPIOB, LCD_DC_Pin, GPIO_PIN_SET);
    /* Send Data */
    if (data != NULL && len != 0)
        HAL_SPI_Transmit(&hspi1, data, len, 10000);
    /* Release Chip */
    HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_SET);
    return;
}

static void
lcd_reset()
{
    HAL_GPIO_WritePin(GPIOB, LCD_RES_Pin, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOB, LCD_RES_Pin, GPIO_PIN_SET);
    HAL_Delay(120);
}

static void
lcd_wait_ms(uint16_t ms)
{
    HAL_Delay((uint32_t)ms);
}

void
lcd_init()
{
    lcd.send = lcd_send;
    lcd.reset = lcd_reset;
    lcd.wait_ms = lcd_wait_ms;
    lcd.x = 26;
    lcd.y = 1;
    lcd.w = 80;
    lcd.h = 160;
    st7735_init(&lcd);
}

void lcd_fill(uint16_t color)
{
    st7735_fill(&lcd, color);
}

void lcd_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    st7735_rect(&lcd, x, y, w, h, color);
}


void lcd_dot(uint16_t x, uint16_t y, uint16_t color)
{
    st7735_dot(&lcd, x, y, color);
}