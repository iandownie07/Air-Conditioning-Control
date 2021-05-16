//
//  Main.cpp
//  main for air-conditioning control implemented in Raspberry Pi Pico with Arm M0+ processor
//
//  Created by Ian Downie on 13/03/21.
//

#include "AirCon.cpp"
#include "States.cpp"
#include "AirConState.cpp"
#include <iostream>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/gpio.h"

#define UART_ID uart0
#define BAUD_RATE 57600
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

// We are using pins 0 and 1 for UART communication
#define UART_TX_PIN 0
#define UART_RX_PIN 1

// Core 0 Main Code
int main()
{
    multicore_launch_core1(core1_entry); // Start core 1 of Raspberry Pi Pico
    while(true)
    {
        // allocate GPIOS
        stdio_init_all(); // Initialize all of the present standard stdio types that are linked into the binary
        
        // Set up our UART with a basic baud rate.
        uart_init(UART_ID, BAUD_RATE);
        
        // Set the TX and RX pins by using the function select on the GPIO
        // Set datasheet for more information on function select
        gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
        // Set UART flow control CTS/RTS, we don't want these, so turn them off
        uart_set_hw_flow(UART_ID, false, false);
        
        // Set our data format
        uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
        
        // Turn off FIFO's - we want to do this character by character
        uart_set_fifo_enabled(UART_ID, false);
        
        // Set up a RX interrupt
        // We need to set up the handler first
        // Select correct interrupt for the UART we are using
        int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
        
        // And set up and enable the interrupt handlers
        irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
        irq_set_enabled(UART_IRQ, true);
        
        // Now enable the UART to send interrupts - RX only
        uart_set_irq_enables(UART_ID, true, false);
        
        // Enable all the pins that will be used, besides the UART ones
        gpio_init(3);
        gpio_set_dir(3, GPIO_OUT);
        gpio_init(10);
        gpio_set_dir(10, GPIO_IN);
        gpio_init(12);
        gpio_set_dir(12, GPIO_OUT);
        gpio_init(15);
        gpio_set_dir(15, GPIO_IN);
        gpio_init(17);
        gpio_set_dir(17, GPIO_OUT);
        gpio_init(22);
        gpio_set_dir(22, GPIO_OUT);

        // Proxy signal for the existence of the door and window
        gpio_put(12,1); // set door out pin
        gpio_put(3,1); // set window out pin
        AirCon* p_air; // pointer to a Total object to initiate state ResetClock
        
        p_air = new AirCon(); // create pointer to an AirCon object to initiate state Idle. We thus enter the constructor of AirCon
        delete p_air;
    }
    return 0;
}
