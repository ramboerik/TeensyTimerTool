#pragma once

#include "TeensyTimerTool.h"

namespace TeensyTimerTool
{

#if defined(T4_0)
    constexpr TimerGenerator* timerPool[] = {GPT1, GPT2, TMR1, TMR2, TMR3, TMR4, TCK};

#elif defined(T3_6)
    constexpr TimerGenerator* timerPool[] = {FTM0, FTM1, FTM2, FTM3, FTM4, TCK};

#elif defined(T3_5)
     constexpr TimerGenerator* timerPool[] = {FTM0, FTM1, FTM2, FTM3, TCK};

#elif defined(T3_2)
    constexpr TimerGenerator* timerPool[] = {FTM0, FTM1, FTM2, TCK};

#elif defined(T3_0)
    constexpr TimerGenerator* timerPool[] = {FTM0, FTM1, TCK};

#elif defined(TLC)
    constexpr TimerGenerator* timerPool[] = {TCK};

#elif defined(STM32F4xx)
    constexpr TimerGenerator* timerPool[] = {GPT1, GPT2, GPT3, GPT4, GPT5, GPT6, GPT7, GPT8, GPT9, GPT10, GPT11, GPT12, GPT13, GPT14, TCK};

#elif defined(ESP32)
    constexpr TimerGenerator* timerPool[] = {TCK};

#elif defined(UNO)
    constexpr TimerGenerator* timerPool[] = {TCK};
#endif

    constexpr unsigned timerCnt = sizeof(timerPool) / sizeof(timerPool[0]);

}

#include "types.h"
