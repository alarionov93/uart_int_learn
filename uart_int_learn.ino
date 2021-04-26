#include <avr/interrupt.h>
//#include <avr/uart.h>
#define BUFFER_SIZE 8
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

//8 data bits
UCSR0C |= (1 << UCSZ01);
UCSR0C |= (1 << UCSZ00);
//enable recieve and transmit
UCSR0B |= (1 << RXEN0);
UCSR0B |= (1 << TXEN0);
//enable interrupt on recieving
UCSR0B |= (1 << RXCIE0);

UBRR0H = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
UBRR0L = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register

int cnt = 0;
char buf[8];

void setup() {
  // put your setup code here, to run once:
  memset(buf, '\0', 8);
}

void loop() {
  // put your main code here, to run repeatedly:
}

ISR(USART_RXC_vect)
{
  while ( !(UCSRA & (1<<RXC)) );
  if (cnt == BUFFER_SIZE)
  {
    cnt=0;
  }
  buf[cnt++] = UDR; // increment rxn and return new value.   
  rxFlag = 1; // notify main of receipt of data.
  
  #ifdef DEBUG
  
  #endif
}
