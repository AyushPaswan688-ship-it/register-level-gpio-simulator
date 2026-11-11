# Register-Level GPIO Logic Simulator

A beginner-friendly, software-based GPIO register simulator written in C.

This project models an 8-bit GPIO direction register and an 8-bit output register. It demonstrates how bit masks and bitwise operations can be used to configure individual pins and control their simulated output state.

## Features

- Configure an individual pin as OUTPUT.
- Configure an individual pin as INPUT.
- Write HIGH or LOW to a pin configured as OUTPUT.
- Prevent writes to pins configured as INPUT.
- Display the mode and simulated output-latch state of all 8 pins.

## Concepts Practised

- `uint8_t` and 8-bit registers
- Bit masks using left shift (`1U << pin`)
- Bitwise OR (`|`), AND (`&`) and NOT (`~`)
- Pointers for modifying simulated registers
- `const` pointers for read-only access
- Functions and basic input validation

## Project Structure

```
register-level-gpio-simulator/
└── main.c
```

## Build and Run

Using GCC:

**Linux / macOS**
```bash
gcc main.c -o gpio_simulator
./gpio_simulator
```

**Windows**
```bash
gcc main.c -o gpio_simulator.exe
.\gpio_simulator.exe
```

## Example Configuration

The current `main()` example configures:

| Pin | Mode | Output latch |
|---|---|---|
| 2 | OUTPUT | HIGH |
| 5 | OUTPUT | LOW |
| 7 | OUTPUT | HIGH |
| Others | INPUT | LOW (initial simulated register state) |

## Scope and Limitations

This is a **software simulation**, not a hardware GPIO driver. It does not access a real microcontroller's memory-mapped registers or measure physical pin voltage. For pins in INPUT mode, the displayed LOW/HIGH value is only the simulated output-register latch state.

The project is intended as a practice step toward understanding register-level programming on microcontrollers.

## Future Improvements

- Add a dedicated GPIO toggle function.
- Add simulated input-state handling.
- Add a simple menu so pin operations can be selected at runtime.
