#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "UART1.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);	//	표준 입출력 스트림 설정 메크로

int main(void){
	stdout = &OUTPUT;
	stdin = &INPUT;	//	표준 입출력 사용

	UART1_init() ;

	char str[100];
	unsigned char temp;
	int i=0;

	while(1){
		temp = UART1_receive();
		str[i] = temp;
		UART1_transmit(temp);	//	에코 기능

		if( str[i] == '\r'){	//	엔터키 감지
			str[i+1]='\0';	//	문자열 끝 처리
			printf("\r\n");
			printf("%s",str);
			i=0;
		}
		else i++;
	}
	return 0;
}
