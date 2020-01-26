#pragma once

#include "GPTchannel.h"

// Timer definitions: ~/.platformio/packages/framework-arduinoststm32/system/Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f429xx.h
// HardwareTimer  wiki: https://github.com/stm32duino/wiki/wiki/HardwareTimer-library

namespace TeensyTimerTool
{
    template <uintptr_t timer_addr>
    class GPT_t
    {
     public:
        static ITimerChannel* getTimer();

     protected:
        static bool isInitialized;
        static callback_t callback;
    };

    template <uintptr_t timer_addr>
    ITimerChannel* GPT_t<timer_addr>::getTimer()
    {
        if (!isInitialized)
        {
            isInitialized = true;
            return new GptChannel((TIM_TypeDef*)timer_addr, &callback);
        }
        return nullptr;
    }

    template <uintptr_t timer_addr>
    bool GPT_t<timer_addr>::isInitialized = false;

    template <uintptr_t timer_addr>
    callback_t GPT_t<timer_addr>::callback = nullptr;

    constexpr TimerGenerator* GPT1 = GPT_t<TIM1_BASE>::getTimer;
    constexpr TimerGenerator* GPT2 = GPT_t<TIM2_BASE>::getTimer;
    constexpr TimerGenerator* GPT3 = GPT_t<TIM3_BASE>::getTimer;
    constexpr TimerGenerator* GPT4 = GPT_t<TIM4_BASE>::getTimer;
    constexpr TimerGenerator* GPT5 = GPT_t<TIM5_BASE>::getTimer;
    constexpr TimerGenerator* GPT6 = GPT_t<TIM6_BASE>::getTimer;
    constexpr TimerGenerator* GPT7 = GPT_t<TIM7_BASE>::getTimer;
    constexpr TimerGenerator* GPT8 = GPT_t<TIM8_BASE>::getTimer;
    constexpr TimerGenerator* GPT9 = GPT_t<TIM9_BASE>::getTimer;
    constexpr TimerGenerator* GPT10 = GPT_t<TIM10_BASE>::getTimer;
    constexpr TimerGenerator* GPT11 = GPT_t<TIM11_BASE>::getTimer;
    constexpr TimerGenerator* GPT12 = GPT_t<TIM12_BASE>::getTimer;
    constexpr TimerGenerator* GPT13 = GPT_t<TIM13_BASE>::getTimer;
    constexpr TimerGenerator* GPT14 = GPT_t<TIM14_BASE>::getTimer;

} // namespace TeensyTimerTool
