#pragma once

#include "GPTchannel.h"

namespace TeensyTimerTool
{
template <unsigned moduleNr>
class GPT_t
{
public:
    static ITimerChannel *getTimer();

protected:
    static bool isInitialized;
    static void isr();
    static callback_t callback;
    static GptChannel *channel;

    // the following is calculated at compile time
    static constexpr IRQ_NUMBER_t irq = moduleNr == 0 ? IRQ_GPT1 : IRQ_GPT2;
    static constexpr IMXRT_GPT_t *pGPT = (IMXRT_GPT_t *)(moduleNr == 0 ? &IMXRT_GPT1 : &IMXRT_GPT2);
    static_assert(moduleNr < 2, "Wrong GPT Number");
};

// IMPLEMENTATION ===========================================================================

template <unsigned moduleNr>
ITimerChannel *GPT_t<moduleNr>::getTimer()
{
    if (!isInitialized)
    {
        isInitialized = true;

        if (moduleNr == 0) // clock settings
            CCM_CCGR1 |= CCM_CCGR1_GPT1_BUS(CCM_CCGR_ON) | CCM_CCGR1_GPT1_SERIAL(CCM_CCGR_ON);
        else
            CCM_CCGR0 |= CCM_CCGR0_GPT2_BUS(CCM_CCGR_ON) | CCM_CCGR0_GPT2_SERIAL(CCM_CCGR_ON);

        pGPT->CR = GPT_CR_CLKSRC(0x001) | GPT_CR_ENMOD; // stopped, restart mode and peripheral clock

        attachInterruptVector(irq, isr);
        NVIC_ENABLE_IRQ(irq);

        channel = new GptChannel(pGPT, &callback);
        return channel;
    }
    return nullptr;
}

template <unsigned tmoduleNr>
void GPT_t<tmoduleNr>::isr()
{
    if (!channel->isPeriodic)
        pGPT->CR &= ~GPT_CR_EN; // stop timer in one shot mode

    callback();                 // we only enabled the OF1 interrupt-> no need to find out which interrupt was actually called
    pGPT->SR = 0x3F;            // reset all interrupt flags
    asm volatile("dsb");        // wait until cache is empty
}

template <unsigned m>
bool GPT_t<m>::isInitialized = false;

template <unsigned m>
callback_t GPT_t<m>::callback = nullptr;

template <unsigned m>
GptChannel* GPT_t<m>::channel = nullptr;

constexpr TimerGenerator *GPT1 = GPT_t<0>::getTimer;
constexpr TimerGenerator *GPT2 = GPT_t<1>::getTimer;

} // namespace TeensyTimerTool
