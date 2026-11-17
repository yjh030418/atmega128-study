#ifndef UART1_H_
#define UART1_H_

#include <avr/io.h>

// ========= UART1 송수신 (9600bps, 2배속 모드) ==========

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

#endif /* UART1_H_ */
