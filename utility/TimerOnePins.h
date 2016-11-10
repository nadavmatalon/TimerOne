/*==============================================================================================================*
 
 @file     TimerOnePins.h
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

#ifndef TimerOnePins_h
#define TimerOnePins_h

    #if defined (__AVR_ATmega328P__)       //  Arduino Uno
        #define TIMER1_A_PIN   9
        #define TIMER1_B_PIN   10
        #define TIMER1_ICP_PIN 8
        #define TIMER1_CLK_PIN 5
      
    #elif defined(__AVR_ATmega32U4__)     // Arduino Leonardo
        #define TIMER1_A_PIN   9
        #define TIMER1_B_PIN   10
        #define TIMER1_C_PIN   11
        #define TIMER1_ICP_PIN 4
        #define TIMER1_CLK_PIN 12
        #define TIMER3_A_PIN   5
        #define TIMER3_ICP_PIN 
    
    #elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)    // Arduino Mega
        #define TIMER1_A_PIN   11
        #define TIMER1_B_PIN   12
        #define TIMER1_C_PIN   13
        #define TIMER3_A_PIN   5
        #define TIMER3_B_PIN   2
        #define TIMER3_C_PIN   3
        #define TIMER4_A_PIN   6
        #define TIMER4_B_PIN   7
        #define TIMER4_C_PIN   8
        #define TIMER4_ICP_PIN 49
        #define TIMER5_A_PIN   46
        #define TIMER5_B_PIN   45
        #define TIMER5_C_PIN   44
        #define TIMER3_ICP_PIN 48
        #define TIMER3_CLK_PIN 47
    
    #elif defined(__AVR_ATmega1284P__)
        #define TIMER1_A_PIN   12
        #define TIMER1_B_PIN   13
        #define TIMER1_ICP_PIN 14
        #define TIMER1_CLK_PIN 1
        #define TIMER3_A_PIN   6
        #define TIMER3_B_PIN   7
        #define TIMER3_ICP_PIN 5
        #define TIMER3_CLK_PIN 8
    
    #endif

#endif