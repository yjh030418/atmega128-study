#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <string.h>


// ========= UART 송수신==========

void UART1_init(void);
void UART1_transmit(char data);
unsigned char UART1_receive(void);

void UART1_init(void){
	UBRR1H = 0x00;
	UBRR1L = 207; // 9600 보율 설정

	UCSR1A |= _BV(U2X1); //2배속 모드
	//비동기, 8비트 데이터, 패리티 없음, 1비트 정지 비트 모드
	UCSR1C |= 0x06;

	UCSR1B |= _BV(RXEN1); // 송수신 가능
	UCSR1B |= _BV(TXEN1);
}

void UART1_transmit(char data){
	while(!(UCSR1A & (1<<UDRE1)));
	UDR1 = data;
}

unsigned char UART1_receive(void){
	while(!(UCSR1A & (1<<RXC1)));
	return UDR1;
}

int main(void){
	UART1_init();

	while(1) UART1_transmit(UART1_receive());

	return 0;
}
