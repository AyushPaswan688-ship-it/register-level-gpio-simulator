#include <stdio.h>
#include <stdint.h>

#define GPIO_PIN_COUNT 8U

/*
 * Register-Level GPIO Simulator
 *
 * This program models the basic logic of an 8-bit GPIO port.
 * A direction bit of 1 means OUTPUT; 0 means INPUT.
 * The output variable represents the output latch, not the
 * physical voltage present on a real microcontroller pin.
 */

/* Function declarations */
void gpio_set_output(uint8_t *direction, uint8_t pin);
void gpio_set_input(uint8_t *direction, uint8_t pin);
void gpio_write(const uint8_t *direction, uint8_t *output,
                uint8_t value, uint8_t pin);
void gpio_toggle_bit(const uint8_t *direction, uint8_t *output,
                     uint8_t pin);
uint8_t gpio_read_bit(const uint8_t *output, uint8_t pin);
void gpio_print_status(const uint8_t *direction, const uint8_t *output);

int main(void)
{
    uint8_t direction = 0;
    uint8_t output = 0;

    /* Configure pins 2, 5, and 7 as outputs. */
    gpio_set_output(&direction, 2);
    gpio_set_output(&direction, 5);
    gpio_set_output(&direction, 7);

    /* Demonstrate switching pin 3 back to input mode. */
    gpio_set_output(&direction, 3);
    gpio_set_input(&direction, 3);

    /* Write initial output-latch values. */
    gpio_write(&direction, &output, 1, 2);  /* Pin 2: HIGH */
    gpio_write(&direction, &output, 0, 5);  /* Pin 5: LOW */
    gpio_write(&direction, &output, 1, 7);  /* Pin 7: HIGH */

    /* Toggle pin 2 twice (it returns to HIGH), and pin 5 once. */
    gpio_toggle_bit(&direction, &output, 2);
    gpio_toggle_bit(&direction, &output, 2);
    gpio_toggle_bit(&direction, &output, 5);

    /* Read and display the selected output-latch bits. */
    printf("\nSelected pin readings:\n");
    printf("Pin 2: %s\n", gpio_read_bit(&output, 2) ? "HIGH" : "LOW");
    printf("Pin 5: %s\n", gpio_read_bit(&output, 5) ? "HIGH" : "LOW");
    printf("Pin 7: %s\n", gpio_read_bit(&output, 7) ? "HIGH" : "LOW");

    /* Display the mode and output-latch state of all eight pins. */
    printf("\nGPIO port status:\n");
    gpio_print_status(&direction, &output);

    return 0;
}

/* Configure a pin as OUTPUT (direction bit = 1). */
void gpio_set_output(uint8_t *direction, uint8_t pin)
{
    if (pin >= GPIO_PIN_COUNT)
    {
        printf("Error: invalid GPIO pin %u\n", pin);
        return;
    }

    *direction |= (uint8_t)(1U << pin);
}

/* Configure a pin as INPUT (direction bit = 0). */
void gpio_set_input(uint8_t *direction, uint8_t pin)
{
    if (pin >= GPIO_PIN_COUNT)
    {
        printf("Error: invalid GPIO pin %u\n", pin);
        return;
    }

    *direction &= (uint8_t)~(1U << pin);
}

/* Write HIGH (1) or LOW (0) to an OUTPUT pin's latch. */
void gpio_write(const uint8_t *direction, uint8_t *output,
                uint8_t value, uint8_t pin)
{
    if (pin >= GPIO_PIN_COUNT)
    {
        printf("Error: invalid GPIO pin %u\n", pin);
        return;
    }

    if (value > 1)
    {
        printf("Error: write value must be 0 or 1\n");
        return;
    }

    if ((*direction & (1U << pin)) == 0)
    {
        printf("Error: pin %u is configured as INPUT\n", pin);
        return;
    }

    if (value == 1)
    {
        *output |= (uint8_t)(1U << pin);
    }
    else
    {
        *output &= (uint8_t)~(1U << pin);
    }
}

/* Toggle one OUTPUT pin using XOR. */
void gpio_toggle_bit(const uint8_t *direction, uint8_t *output,
                     uint8_t pin)
{
    if (pin >= GPIO_PIN_COUNT)
    {
        printf("Error: invalid GPIO pin %u\n", pin);
        return;
    }

    if ((*direction & (1U << pin)) == 0)
    {
        printf("Error: pin %u is configured as INPUT\n", pin);
        return;
    }

    *output ^= (uint8_t)(1U << pin);
}

/* Return 1 if the selected output-latch bit is HIGH, otherwise 0. */
uint8_t gpio_read_bit(const uint8_t *output, uint8_t pin)
{
    if (pin >= GPIO_PIN_COUNT)
    {
        printf("Error: invalid GPIO pin %u\n", pin);
        return 0;
    }

    return ((*output & (1U << pin)) != 0U) ? 1U : 0U;
}

/* Print the mode and output-latch state for all eight pins. */
void gpio_print_status(const uint8_t *direction, const uint8_t *output)
{
    for (uint8_t pin = 0; pin < GPIO_PIN_COUNT; pin++)
    {
        const char *mode =
            ((*direction & (1U << pin)) != 0U) ? "OUTPUT" : "INPUT";

        const char *latch =
            ((*output & (1U << pin)) != 0U) ? "HIGH" : "LOW";

        printf("Pin %u: %s mode, output latch %s\n", pin, mode, latch);
    }
}
