#include "main.h"
#include "gpio.h"
#include "lcd.h"

enum
{
    X_STEP = 20,
    Y_STEP = 25,
    X_SIZE = 15,
    Y_SIZE = 20,
    BORDER = 2,
};


enum
{
    WHITE = 0x0000,
    GREEN = 0xF800, /* not sure */
    BLUE = 0x07E0, /* not sure */
    RED = 0x001F, /* not sure */
    BLACK = 0xFFFF,
};

uint8_t digit_bits[] = {2, 4, 3, 4, 3, 4};

static void
draw_digit(uint8_t index, uint8_t digit, uint8_t bits, uint16_t color, uint16_t fill)
{
    if (bits > 4)
        return;

    if ((digit >> bits) > 0)
        return;

    for (int i = 0; i < bits; i++)
    {

        /* outer */
        lcd_rect(
            i * X_STEP,
            index * Y_STEP + Y_STEP / 2,
            X_SIZE,
            Y_SIZE,
            color);

        /* inner */
        if ( (digit & (1 << i)) == 0)
            lcd_rect(
                i * X_STEP + BORDER,
                index * Y_STEP + Y_STEP / 2 + BORDER,
                X_SIZE - BORDER * 2,
                Y_SIZE - BORDER * 2,
                fill);
    }

}

static void
inc_time(uint8_t *time)
{

    time[2]++;

    /* seconds */
    if (time[2] >= 60)
    {
        time[2] = 0;
        time[1]++;
    }

    /* minutes */
    if (time[1] >= 60)
    {
        time[1] = 0;
        time[0]++;
    }

    /* hours */
    if (time[0] >= 24)
    {
        time[0] = 0;
    }
}

static void
get_digits(uint8_t *time, uint8_t *digits)
{
    /* seconds */
    digits[5] = time[2] % 10;
    digits[4] = time[2] / 10;

    /* minutes */
    digits[3] = time[1] % 10;
    digits[2] = time[1] / 10;

    /* hours */
    digits[1] = time[0] % 10;
    digits[0] = time[0] / 10;
}

void
app_start(void)
{
    uint8_t time[3] = { 0 };
    uint8_t digits[6] = { 0 };

    lcd_init();

    while(1)
    {
        inc_time(&time);
        get_digits(&time, &digits);

        lcd_fill(BLACK);
        for (int idx = 0; idx < 6; idx++)
        {
            draw_digit(idx, digits[idx], digit_bits[idx], WHITE, BLACK);
        }
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        HAL_Delay(1000);
    }
}