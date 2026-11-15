#include <stdio.h>
#include <stdint.h>

/*

 -> Register-Level GPIO Simulator
 -> This program models the basic logic of an 8-bit GPIO port.
 -> A direction bit of 1 means OUTPUT; 0 means INPUT.
 -> The output variable represents the output latch, not the physical voltage present on a real microcontroller pin.
 
 */

// Function declarations
void gpio_set_output(uint8_t *direction, uint8_t pin);
void gpio_set_input(uint8_t *direction, uint8_t pin);
void gpio_write(const uint8_t *direction, uint8_t *output, uint8_t value, uint8_t pin);
void gpio_print_status(const uint8_t *direction, const uint8_t *output);
void gpio_toggle_bit(const uint8_t *direction, uint8_t *output, uint8_t pin);
uint8_t gpio_read_bit(const uint8_t *output,uint8_t pin);

int main(void)
{
    uint8_t direction = 0;
    uint8_t output = 0;
    // Configure pins 2, 5, and 7 as outputs.
    gpio_set_output(&direction, 2);
    gpio_set_output(&direction, 5);
    gpio_set_output(&direction, 7);
    // Write initial output-latch values
    gpio_write(&direction, &output, 1, 2);
    gpio_write(&direction, &output, 0, 5);
    gpio_write(&direction, &output, 1, 7);
    // reading selected pins
    gpio_read_bit(&output,2);
    gpio_read_bit(&output,5);
    gpio_read_bit(&output,7);
    // Toggle selected pins 
    gpio_toggle_bit(&direction,&output,2); // pin-2 become 1 to 0
    gpio_toggle_bit(&direction,&output,5); // pin-5 become 0 to 1
    gpio_toggle_bit(&direction,&output,7); // pin-7 become 1 to 0
    printf("after toggle bits\n");
    // reading selected pins after toggle
    gpio_read_bit(&output,2);
    gpio_read_bit(&output,5);
    gpio_read_bit(&output,7);
    // print the status os all gpio pins
    gpio_print_status(&direction, &output);

    return 0;
}


// definitions of functions

void gpio_set_output(uint8_t *direction, uint8_t pin) // configure selected pin as output (direction = 1)
{
    *direction |= (1U << pin);
}

void gpio_set_input(uint8_t *direction, uint8_t pin) // configure selected pin as input (direction = 0)
{
    *direction &= ~(1U << pin);
}

//Write HIGH (1) or LOW (0) to an OUTPUT pin's latch.
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
// toggle the bit:
void gpio_toggle_bit(const uint8_t *direction, uint8_t *output, uint8_t pin)
{
    if((*direction&(1U<<pin))==0)
    {
        printf("error : this pin is in input mode\n ");
        return;
    }
    else
    {
       *output^=(1U<<pin); 
    }
}
// raed the slected pin's status
uint8_t gpio_read_bit(const uint8_t *output,uint8_t pin)
{
    if((*output&(1U<<pin))==0)
    {
        printf("pin %u bit is LOW\n",pin);
        return 0;
    }
    else 
    {
        printf("pin %u bit is HIGH\n",pin);
        return 1;
    }
}
