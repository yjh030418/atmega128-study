# 4주차: 타이머/카운터와 PWM

> 블로그: [빛돌 4주차 - 타이머, 카운터](https://blog.naver.com/homeless112/224176575197)

`_delay_ms()` 대신 하드웨어 타이머로 정확한 주기를 만들고, PWM으로 서보모터와 DC 모터를 제어했습니다.

| 파일 | 타이머 | 모드 | 내용 |
| --- | --- | --- | --- |
| `timer0_led_blink.c` | Timer0 (8-bit) | Normal, 오버플로 인터럽트 | 약 1초마다 LED 토글 |
| `timer1_ctc_led_blink.c` | Timer1 (16-bit) | CTC, 비교 일치 인터럽트 | 정확히 0.5초 단위로 LED 토글 |
| `timer1_servo_pwm.c` | Timer1 (16-bit) | Fast PWM (TOP = ICR1) | 서보모터 0° → 90° → 180° 반복 |
| `timer3_dc_motor_pwm.c` | Timer3 (16-bit) | 8-bit Fast PWM | 모터 드라이버로 DC 모터 속도 단계 제어 |

## 주기 계산

| 목적 | 계산 | 설정 |
| --- | --- | --- |
| Timer0 LED | 16 MHz / 1024 = 15,625 Hz → 64 µs, × 256 = 약 16 ms, × 64회 ≈ 1.02 s | `TCCR0 = CS02·CS01·CS00` (1024분주) |
| Timer1 CTC | 16 MHz / 256 = 62,500 Hz → 16 µs, × 31,250 = 0.5 s | `OCR1A = 31249` |
| 서보 PWM | 16 MHz / 8 = 2 MHz → 0.5 µs, 20 ms / 0.5 µs = 40,000 | `ICR1 = 39999`, 90°는 `OCR1A = 3000` (1.5 ms) |
| DC 모터 PWM | 16 MHz / 64 = 250 kHz, / 256 ≈ 976 Hz | `OCR3B = 0~255`로 듀티 조절 |

## 배운 점

- PWM은 펄스 폭(듀티 사이클)을 바꿔 평균 전압을 조절하는 방식입니다. 디지털 출력으로 아날로그처럼 제어한다는 점이 흥미로웠습니다.
- DC 모터는 노트북 5V로 테스트했지만, 실제로는 모터 드라이버에 외부 전원을 쓰는 것이 안전합니다.
