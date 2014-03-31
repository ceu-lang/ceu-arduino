
#include <avr/io.h>

#define BAUD_HUMAN   9600
#define BAUD_USART   (((F_CPU / (BAUD_HUMAN * 16UL))) - 1)

void setup (void) {
    /* Set baud rate */
    UBRR0H = (unsigned char)(BAUD_USART>>8);
    UBRR0L = (unsigned char)BAUD_USART;

    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);

    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void loop (void) {
    /* Wait for data to be received */
    while (! (UCSR0A & (1<<RXC0)));
    /* Get and return received data from buffer */
    char v = UDR0;

    /* Put data into buffer, sends the data */
    while (! (UCSR0A & (1<<UDRE0)));
    UDR0 = v + 1;
    // Do nothing until transmission complete flag set
    //while ((UCSRA & (1 << TXC)) == 0) {};
}
