# ATmega128 Study: 빛돌(BITDOL) 신입생 교육과정

> 경북대학교 전자공학부 학술 동아리 **빛돌(BITDOL)** 신입생 교육과정(2026.01~02) 실습 기록
> 16진 카운터 회로부터 ATmega128의 GPIO, 인터럽트, 타이머/PWM, UART, ADC까지 **레지스터를 직접 설정**하며 구현했습니다.

## 목차

| 주차 | 주제 | 핵심 내용 | 코드 | 블로그 |
| --- | --- | --- | --- | --- |
| 1 | 16진 카운터 회로 | 555 타이머, JK 플립플롭, MUX, 디코더, 만능기판 납땜 | [week1](week1_hex-counter) | [글](https://blog.naver.com/homeless112/224164960120) |
| 2 | GPIO로 LED 제어 | DDRx/PORTx, Active Low, 비트 연산 | [week2](week2_gpio-led) | [글](https://blog.naver.com/homeless112/224166430914) |
| 3 | 외부 인터럽트 | INT4, 내부 풀업, EICRB 트리거 설정, 소프트웨어 디바운싱 | [week3](week3_interrupt) | [글](https://blog.naver.com/homeless112/224166478344) |
| 4 | 타이머/카운터, PWM | Timer0 오버플로, Timer1 CTC, Fast PWM 서보·DC 모터 제어 | [week4](week4_timer-pwm) | [글](https://blog.naver.com/homeless112/224176575197) |
| 5 | UART 통신, ADC | USART1 9600bps, printf/scanf 스트림, 10-bit ADC, ADC→PWM 모터 속도 제어 | [week5](week5_uart-adc) | [글](https://blog.naver.com/homeless112/224177789198) |

## 배운 점

- **하드웨어 디버깅은 눈에 안 보인다.** 16진 카운터 납땜은 3시간이었지만 쇼트와 오배선을 잡는 데 2일이 걸렸습니다. 2주차에는 칩을 하나 태우고 64핀을 다시 납땜했습니다.
- **비트 연산과 Active Low.** LED 출력이 Active Low라서 `~((1 << i) | stack)`처럼 OR로 쌓고 전체를 반전하는 방식에 익숙해졌습니다.
- **디바운싱은 필수.** 디바운싱 없이 짠 인터럽트 코드는 거의 동작하지 않았습니다. ISR에서 20 ms 대기 후 핀 상태를 다시 확인해 입력을 확정했습니다.
- **분주비와 주기를 직접 계산.** 16 MHz / 1024 → 64 µs 틱, 8분주 + ICR1 = 39999 → 20 ms(50 Hz) 서보 PWM처럼 데이터시트를 보고 레지스터 값을 정했습니다.

## 개발 환경

`ATmega128 @ 16 MHz` `C (avr-gcc)` `Microchip Studio` `PuTTY`

## 이후

이 교육과정에서 익힌 레지스터 수준 제어를 바탕으로 [ATmega128 자동 침수 방지 시스템](https://github.com/yjh030418/atmega128-flood-defense-system)(2026 COSS 차세대반도체 MCU 응용 경진대회)을 만들었습니다.
