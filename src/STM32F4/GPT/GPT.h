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

} // namespace TeensyTimerTool
