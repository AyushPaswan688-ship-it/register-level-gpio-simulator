#include <stdio.h>
#include <stdint.h>

// Function declarations
void gpio_set_output(uint8_t *direction, uint8_t pin);
void gpio_clear_input(uint8_t *direction, uint8_t pin);
void gpio_write(const uint8_t *direction, uint8_t *output, uint8_t value, uint8_t pin);
void gpio_print_status(const uint8_t *direction, const uint8_t *output);

int main(void)
{
    uint8_t direction = 0;
    uint8_t output = 0;

    gpio_set_output(&direction, 2);
    gpio_set_output(&direction, 5);
    gpio_set_output(&direction, 7);

    gpio_write(&direction, &output, 1, 2);
    gpio_write(&direction, &output, 0, 5);
    gpio_write(&direction, &output, 1, 7);

    gpio_print_status(&direction, &output);

    return 0;
}

void gpio_set_output(uint8_t *direction, uint8_t pin)
{
    *direction |= (1U << pin);
}

void gpio_clear_input(uint8_t *direction, uint8_t pin)
{
    *direction &= ~(1U << pin);
}

void gpio_write(const uint8_t *direction, uint8_t *output, uint8_t value, uint8_t pin)
{
    if ((*direction & (1U << pin)) == 0)
    {
        printf("Error: pin is in input mode\n");
        return;
    }

    if (value == 1)
    {
        *output |= (1U << pin);
    }
    else if (value == 0)
    {
        *output &= ~(1U << pin);
    }
    else
    {
        printf("Invalid write value\n");
    }
}

void gpio_print_status(const uint8_t *direction, const uint8_t *output)
{
    for (uint8_t pin = 0; pin < 8; pin++)
    {
        printf("Pin %u: ", pin);

        if (*direction & (1U << pin))
        {
            printf("OUTPUT mode, ");
        }
        else
        {
            printf("INPUT mode, ");
        }

        if (*output & (1U << pin))
        {
            printf("output latch HIGH\n");
        }
        else
        {
            printf("output latch LOW\n");
        }
    }
}
