/*==============================================================================================================*
 
    @file     TimerOne.h
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

#if 1
__asm volatile ("nop");
#endif

#ifndef TimerOne_h
#define TimerOne_h

#if !defined(ARDUINO_ARCH_AVR)
#error “This library only supports AVR processors.”
#endif

#include <Arduino.h>
#include "utility/TimerOnePins.h"

namespace Timerone {
    
    const unsigned long TIMER1_RESOLUTION = 65536;
    
    class TimerOne {
    public:
        void init(unsigned long uSec = 1000000);
        void setPeriod(unsigned long uSec);
        void start();
        void stop();
        void setPwmDuty(char pin, unsigned int duty);
        void pwm(char pin, unsigned int duty);
        void pwm(char pin, unsigned int duty, unsigned long uSec);
        void disablePwm(char pin);
        void attachInterrupt(void (*isr)());
        void attachInterrupt(void (*isr)(), unsigned long uSec);
        void detachInterrupt();
        static void (*isrCallback)();
        static void isrDefaultUnused();
    private:
        unsigned short pwmPeriod;
        unsigned char  clockSelectBits;
    };
}

using namespace Timerone;

extern TimerOne Timer1;

#endif
