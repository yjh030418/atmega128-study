#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "UART1.h"

#define MotorForward() {PORTE |= (1<<PE0); PORTE &= ~(1<<PE2);}
#define MotorBackward() {PORTE &= ~(1<<PE0); PORTE |= (1<<PE2);}

#define MotorSpeed(s) OCR3B = s

void InitializeTimer3(void){
	TCCR3A |= (1<<WGM30);
	TCCR3B |= (1<<WGM32); // 8비트 고속 PWM모드
	//주파수가 높을수록 모터 회전이 부드러워짐
	
	TCCR3A |= (1<<COM3B1); //비반전
	
	TCCR3B |= (1<<CS31) | (1<< CS30); // 64분주 -> 250,000Hz
	// 250,000 / 256 -> 약 976Hz
	
	OCR3B = 0; // (0~255)
	
}

FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);


void ADC_init(unsigned char channel)
{
    ADMUX |= (1 << REFS0) ;
    ADCSRA = 0x07;
    ADCSRA |= (1 << ADEN) ;
    ADCSRA |= (1 << ADFR) ;
    ADMUX = ((ADMUX & 0xE0) | channel) ;
    ADCSRA |= (1 << ADSC);
}

int read_ADC (void)
{
    while(!(ADCSRA & (1 << ADIF))); //adc 변환 기다림
 
    return ADC;
}

int main(void){
   DDRE |= (1<<PE0) | (1<<PE2) | (1<<PE4);
	//출력 단자 설정 (pwm은 pe4)
	InitializeTimer3();
    MotorForward();
//=================================================   
    int read;
    stdout = &OUTPUT;
    stdin = &INPUT;
    UART1_init() ;
    ADC_init (0) ;
    while(1){
        read = read_ADC() ;
        MotorSpeed(read / 4);	//	Atmega128은 10비트(1024)해상도의 ADC를 가지고 있다.
        _delay_ms (100);
    }  
    return 0;
}
