#include <avr/io.h>
#define USART_BAUDRATE 9600
#define UBRR_VALUE ((F_CPU / 4 / USART_BAUDRATE - 1) / 2)

void USART0Init(void)
{
    // Set baud rate
    UBRR0H = (uint8_t)(UBRR_VALUE>>8);
    UBRR0L = (uint8_t)UBRR_VALUE;
    // Set frame format to 8 data bits, no parity, 1 stop bit
    UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
    //enable transmission and reception
    UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
}

void USART0SendByte(uint8_t u8Data)
{
    //wait while previous byte is completed
    while(!(UCSR0A&(1<<UDRE0))){};
    // Transmit data
    UDR0 = u8Data;
}

uint8_t USART0ReceiveByte()
{
    // Wait for byte to be received
    while(!(UCSR0A&(1<<RXC0))){};
    // Return received data
    return UDR0;
}

void setup (void)
{
    uint8_t u8TempData;
    //Initialize USART0
    USART0Init();
    while(1)
    {
        // Receive data
        u8TempData = USART0ReceiveByte();
        // Increment received data
        u8TempData++;
        //Send back to terminal
        USART0SendByte(u8TempData);
    }
}

void loop () {
}
