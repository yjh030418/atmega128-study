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
	
	char str[4];
	int count = 0;
	char temp;

	while (scanf(" %c", &temp) == 1) {
		str[count] = temp;
		count++;
		if (count == 3) {
			for (int i = 0; i < 3; i++) {
				printf("%c", str[i]);
			}

			count = 0;
			printf("\n\r");
		}
	}
	return 0;
}
