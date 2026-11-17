#define F_CPU 16000000UL  // 16MHz 클럭 설정
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	
	DDRC = 0xFF;

	while (1) {
	
		PORTC = 0x0F;	//(0000 1111)
		_delay_ms(500); // 0.5초 대기

	
		PORTC = 0xF0;	//  (1111 0000)
		_delay_ms(500); // 0.5초 대기
	}

	return 0;
}
