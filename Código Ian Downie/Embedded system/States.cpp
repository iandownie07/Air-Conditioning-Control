//
//  States.cpp
//
//
//  Created by Ian Downie on 13/03/21.
//

#include "States.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/irq.h"
#include "hardware/gpio.h"
#include "CreateString.cpp"
#include "queue.cpp"
#include "ClockTime.cpp"


#define UART_ID uart0
#define BAUD_RATE 57600
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define DOOR_VAL 1
#define WINDOW_VAL 1

#define DOOR_PIN 12
#define WINDOW_PIN 8


#define FIRST_GPIO 2

Queue queue1;

string output; // string for queue


static volatile bool connect_flag = true;
//gpio_put(DOOR_PIN,DOOR_VAL); // set door out pin
//gpio_put(WINDOW_PIN, WINDOW_VAL); // set window out pin
int eventtype_flag;
int state_flag;

// define the initial time
ClockHour ti;
ClockDate d;

/*
 // RX interrupt handler (core 0)
 void on_uart_rx() {
 while (uart_is_readable(UART_ID)) {
 char ch = uart_getc(UART_ID);
 auto output1 = (const unsigned char *)output.c_str();
 if (uart_is_writable(UART_ID) && ch == '1')
 {
 uart_write_blocking(UART_ID, output1, 20);
 }
 chars_rxed++;
 }
 }*/
// RX interrupt handler (core 0)
void on_uart_rx() {
    
    while (uart_is_readable(UART_ID)) // check is readable
    {
        char ch = uart_getc(UART_ID); // wait for signal to start transfer
        
        if (uart_is_writable(UART_ID) && ch == '1') // start transfer
        {
            string queue_str;   // to accept string from queue
            //INSERT DEQUEUE HERE
            while(queue1.isEmpty() == 0) // wait till queue is empty
            {
                queue_str = *(string*)queue1.remove(); // remove item from queue
                //convert to format accepted in UART
                auto queue_str_buf = (const char *)queue_str.c_str();
                // send item
                uart_puts(UART_ID, queue_str_buf); // 20 with 'e'
            }
            uart_putc(UART_ID, 'f'); // signal end of transmission/end of queue
        }
    }
}


// Core 1 interrupt Handler
void core1_interrupt_handler(uint gpio, uint32_t events)
{
    
    //while (true)
    {
        if (GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL)
            
        {
            if(state_flag == 1) // so as only capture button presses in idle
            {
            // create button-press event for log
            Packet pack;
            int h = ti.hr; int m = ti.min; int s = ti.seg;
            int dy = d.day; int mn = d.mo; int y = d.yr;
            string output;
            eventtype_flag = 2; // event 2 is a button press
            pack.setEvent(eventtype_flag);
            pack.setEventTime(h, m, s, dy, mn, y);
            pack.makePacket();
            output = pack.getPacket();
            queue1.insert(new string(output));
            }
            if(gpio_get(15) && gpio_get(10))
                connect_flag = true;
            //cout << "The interrupt flag in button is " << connect_flag << endl;
            gpio_put(18,0);
            
        }
        
    }
}

// Core 1 Main Code
void core1_entry()
{
    cout << "We're in the second core" << endl;
    // Configure Core 1 Interrupt
    multicore_fifo_clear_irq(); // clear the interrupt flag, in case it got set by a chance
    gpio_init(18);
    gpio_pull_up(18);
    gpio_set_irq_enabled_with_callback(18, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &core1_interrupt_handler); // (GPIO number, events that trigger interrupt, bool enabled, user function to call on GPIO irq)
    
    // Infinte While Loop to wait for interrupt
    ti.setHr(16);
    ti.setMin(30);
    ti.setSeg(30);
    d.setDay(25);
    d.setMo(05);
    d.setYr(16);
    //cout << t << " " << d << endl;
    while (1) {
        sleep_ms(1000); // sleep for 1 second
        system("clear"); // clear screen
        
        if (ti.seg == 59 && ti.min == 59 && ti.hr == 23)
        {
            ++d;
        }
        ++ti;
       // cout << ti << " " << d << endl;
    }
}

AirConState& Idle::getInstance()
{
    static Idle singleton;
    return singleton;
}

void Idle::enter(AirCon* p_air)
{
    state_flag = 1;
    // create disconnect event for log
    if(connect_flag == false)
    { // so as not to create event when system starts
    Packet pack;
    int h = ti.hr; int m = ti.min; int s = ti.seg;
    int dy = d.day; int mn = d.mo; int y = d.yr;
    string output;
    eventtype_flag = 1; // event 1 is a disconnection
    pack.setEvent(eventtype_flag);
    pack.setEventTime(h, m, s, dy, mn, y);
    pack.makePacket();
    output = pack.getPacket();
    queue1.insert(new string(output));
    }
    while (!gpio_get(15) || !gpio_get(10) || connect_flag == false)
    {
        if(!gpio_get(15) || !gpio_get(10))
            gpio_put(17, 1); // set LED
        else
            gpio_put(17, 0); // disconnect LED when window & door are closed
        // tight_loop_contents();
        /*
        //cout << "We're in idle" << endl;
        if(gpio_get(15))
            cout << "door is closed" << endl;
        if(gpio_get(10))
            cout << "window is closed" << endl;
        if(gpio_get(12))
            cout << "door is transmitting" << endl;
        if(gpio_get(3))
            cout << "window is transmitting" << endl;
        if(gpio_get(17))
            cout << "LED is on" << endl;
        cout << "Connect flag is " << connect_flag << endl;*/
        sleep_ms(3000);
        
    } // we leave infinite loop if door & window are closed &
    p_air->toggle();
}

void Idle::toggle(AirCon* p_air)
{
    
    cout << "We're in idle toggle" << endl;
    // read window & door pins
    if(gpio_get(15) && gpio_get(10) && connect_flag)
        // we will start cooling if the door and window are closed and the button has been pressed
        p_air->setState(Cooling::getInstance());
    else
        p_air->setState(Idle::getInstance());
}

void Idle::exit(AirCon* p_air)
{
    
}

AirConState& Cooling::getInstance()
{
    static Cooling singleton;
    return singleton;
}

void Cooling::enter(AirCon* p_air)
{
    state_flag = 2;
    gpio_put(17, 0);
    gpio_put(22, 1); // turn on relay
    //cout << "We're cooling" << endl;
    //cout << "The interrupt flag in Cooling is " << connect_flag << endl;
    if(gpio_get(15) && gpio_get(10))
    {
        // create cooling-start event for log
        //cout << "We're creating a cooling event" << endl;
        Packet pack;
        int h = ti.hr; int m = ti.min; int s = ti.seg;
        int dy = d.day; int mn = d.mo; int y = d.yr;
        string output;
        eventtype_flag = 3; // event 3 is a cooling start
        pack.setEvent(eventtype_flag);
        pack.setEventTime(h, m, s, dy, mn, y);
        pack.makePacket();
        output = pack.getPacket();
        queue1.insert(new string(output));
        cout << output << endl;
    }
    while (gpio_get(15) && gpio_get(10)) {
        //  tight_loop_contents(); // while door and window are closed, keep cooling
      /*  if(gpio_get(15))
            cout << "door is closed" << endl;
        if(gpio_get(10))
            cout << "window is closed" << endl;*/
        sleep_ms(3000);
    }
    gpio_put(22, 0); // turn off relay
    connect_flag = false;
    p_air->toggle();
    
}

void Cooling::toggle(AirCon* p_air)
{
    p_air->setState(Idle::getInstance());
}

void Cooling::exit(AirCon* p_air)
{
    
}


