#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "UART1.h"


FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);

void ADC_init(unsigned char channel)
{
    ADMUX |= (1 << REFS0) ;	//	외부 AVCC를 기준 전압으로 설정(노이즈 감소)

    ADCSRA = 0x07;	//	분주비 설정 0000 0111 (128분주) ->125000Hz가 적당하다

    ADCSRA |= (1 << ADEN) ;		//	ADC 활성화
    ADCSRA |= (1 << ADFR) ;		//	프리 러닝 모드 (계속해서 A->D변환)
    ADMUX = ((ADMUX & 0xE0) | channel) ;	//	채널 선택 (1110 0000) -> 단일 입력 채널 0 사용 (AVCC 사용 했으니까)
    ADCSRA |= (1 << ADSC);		//	AD 변환 시작
}

int read_ADC (void)
{
    while( !(ADCSRA & (1 << ADIF))); 	//adc 변환 기다림 (adc 인터럽트 플래그)
    return ADC;		//	10비트 값을 변환 (0~1023)
}

int main(void){
    int read;

    stdout = &OUTPUT;
    stdin = &INPUT;

    UART1_init() ;
    ADC_init (0) ;


    while(1){
        read = read_ADC() ;
        printf ("%d\r\n", read);
        _delay_ms (1000);
    }  
    return 0;
}
