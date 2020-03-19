#include "main.h"
#include "gpio.h"
#include "lcd.h"

uint16_t color = 0xFFFF;
uint16_t colors[] = {
    0x0000, /* white */
    0xF800,
    0x07E0,
    0x001F,
    0xFFE0,
    0xF81F,
    0x07FF,
    0xFFFF, /* black */
};

void
app_start(void)
{
    lcd_init();

    while(1)
    {
        lcd_fill(color);
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
        HAL_Delay(3000);

        for (uint8_t i = 0; i < sizeof(colors)/sizeof(colors[0]); i++)
        {
            lcd_rect(0,  i * 20, 80, 20, colors[i]);
        }
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
        HAL_Delay(3000);
    }
}