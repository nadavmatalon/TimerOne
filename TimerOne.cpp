/*==============================================================================================================*
 
    @file     TimerOne.cpp
    @author   Nadav Matalon
    @license  MIT (c) 2016 Nadav Matalon

    Timer One

    Ver. 1.0.0 - First release (25.10.16)
 
 *==============================================================================================================*
    LICENSE
 *==============================================================================================================*
 
    The MIT License (MIT)
    Copyright (c) 2016 Nadav Matalon

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
    documentation files (the "Software"), to deal in the Software without restriction, including without
    limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
    the Software, and to permit persons to whom the Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial
    portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
    LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 *==============================================================================================================*/

#include "TimerOne.h"

TimerOne Timer1;                                                        // preinstatiate

void TimerOne::init(unsigned long uSec=1000000) {
    TCCR1B = _BV(WGM13);                                                // Phase and Frequency Correct PWM Mode
    TCCR1A = 0;                                                         // Clear Control Register A
    setPeriod(uSec);
}

void TimerOne::setPeriod(unsigned long uSec) {
    const unsigned long cycles = (F_CPU / 2000000) * uSec;
    if (cycles < TIMER1_RESOLUTION) {
        clockSelectBits = _BV(CS10);
        pwmPeriod = cycles;
    } else if (cycles < TIMER1_RESOLUTION * 8) {
        clockSelectBits = _BV(CS11);
        pwmPeriod = cycles / 8;
    } else if (cycles < TIMER1_RESOLUTION * 64) {
        clockSelectBits = _BV(CS11) | _BV(CS10);
        pwmPeriod = cycles / 64;
    } else if (cycles < TIMER1_RESOLUTION * 256) {
        clockSelectBits = _BV(CS12);
        pwmPeriod = cycles / 256;
    } else if (cycles < TIMER1_RESOLUTION * 1024) {
        clockSelectBits = _BV(CS12) | _BV(CS10);
        pwmPeriod = cycles / 1024;
    } else {
        clockSelectBits = _BV(CS12) | _BV(CS10);
        pwmPeriod = TIMER1_RESOLUTION - 1;
    }
    ICR1 = pwmPeriod;
    TCCR1B = _BV(WGM13) | clockSelectBits;
}

void TimerOne::start() {
    TCCR1B = 0;
    TCNT1 = 0;
    TCCR1B = _BV(WGM13) | clockSelectBits;
}

void TimerOne::stop() {
    TCCR1B = _BV(WGM13);
}

void TimerOne::setPwmDuty(char pin, unsigned int duty) {
    unsigned long dutyCycle = pwmPeriod;
    dutyCycle *= duty;
    dutyCycle >>= 10;
    if (pin == TIMER1_A_PIN) OCR1A = dutyCycle;
    #ifdef TIMER1_B_PIN
    else if (pin == TIMER1_B_PIN) OCR1B = dutyCycle;
    #endif
    #ifdef TIMER1_C_PIN
    else if (pin == TIMER1_C_PIN) OCR1C = dutyCycle;
    #endif
}

void TimerOne::pwm(char pin, unsigned int duty) {
    if (pin == TIMER1_A_PIN) {
        pinMode(TIMER1_A_PIN, OUTPUT);
        TCCR1A |= _BV(COM1A1);
    }
    #ifdef TIMER1_B_PIN
    else if (pin == TIMER1_B_PIN) {
        pinMode(TIMER1_B_PIN, OUTPUT);
        TCCR1A |= _BV(COM1B1);
    }
    #endif
    #ifdef TIMER1_C_PIN
    else if (pin == TIMER1_C_PIN) {
        pinMode(TIMER1_C_PIN, OUTPUT);
        TCCR1A |= _BV(COM1C1);
    }
    #endif
    setPwmDuty(pin, duty);
    TCCR1B = _BV(WGM13) | clockSelectBits;
}

void TimerOne::pwm(char pin, unsigned int duty, unsigned long uSec) {
    if (uSec > 0) setPeriod(uSec);
    pwm(pin, duty);
}

void TimerOne::disablePwm(char pin) {
    if (pin == TIMER1_A_PIN) TCCR1A &= ~_BV(COM1A1);
    #ifdef TIMER1_B_PIN
    else if (pin == TIMER1_B_PIN) TCCR1A &= ~_BV(COM1B1);
    #endif
    #ifdef TIMER1_C_PIN
    else if (pin == TIMER1_C_PIN) TCCR1A &= ~_BV(COM1C1);
    #endif
}

void TimerOne::attachInterrupt(void (*isr)()) {
    isrCallback = isr;
    TIMSK1 = _BV(TOIE1);
}

void TimerOne::attachInterrupt(void (*isr)(), unsigned long uSec) {
    if (uSec > 0) setPeriod(uSec);
    attachInterrupt(isr);
}

void TimerOne::detachInterrupt() {
    TIMSK1 = 0;
}

void (*TimerOne::isrCallback)() = TimerOne::isrDefaultUnused;

void TimerOne::isrDefaultUnused() {}

ISR(TIMER1_OVF_vect) {
    Timer1.isrCallback();
}

