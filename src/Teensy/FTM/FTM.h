#pragma once
#include "FTM_Channel.h"
#include "FTM_Info.h"

namespace TeensyTimerTool
{
    template <unsigned moduleNr>
    class FTM_t
    {
     public:
        inline static ITimerChannel* getTimer();
        FTM_t() = delete;

     private:
        static bool isInitialized;
        inline static void isr() FASTRUN;

        static constexpr FTM_r_t* r = (FTM_r_t*)FTM_Info<moduleNr>::baseAdr;
        static constexpr unsigned maxChannel = FTM_Info<moduleNr>::nrOfChannels;
        static FTM_ChannelInfo channelInfo[maxChannel];

        static_assert(moduleNr < 4, "Module number < 4 required");
    };

    // IMPLEMENTATION ==================================================================

    template <unsigned moduleNr>
    ITimerChannel* FTM_t<moduleNr>::getTimer()
    {
        if (!isInitialized)
        {
            r->SC = FTM_SC_CLKS(0b00); // Disable clock
            r->MOD = 0xFFFF;           // Set full counter range
            r->CNT = 0;

            //Serial.printf("mode: %d\n",r->MODE);

            for (unsigned chNr = 0; chNr < maxChannel; chNr++)
            {
                channelInfo[chNr].isReserved = false;
                channelInfo[chNr].callback = nullptr;
                channelInfo[chNr].chRegs = &r->CH[chNr];

                r->CH[chNr].SC &= ~FTM_CSC_CHF;  // FTM requires to clear flag by setting bit to 0
                r->CH[chNr].SC &= ~FTM_CSC_CHIE; // Disable channel interupt
                r->CH[chNr].SC = FTM_CSC_MSA;
            }
            r->SC = FTM_SC_CLKS(0b01) | FTM_SC_PS(FTM_Info<moduleNr>::prescale); // Start clock
            attachInterruptVector(FTM_Info<moduleNr>::irqNumber, isr);           // prepare isr and nvic, don't yet enable interrupts
            NVIC_ENABLE_IRQ(FTM_Info<moduleNr>::irqNumber);
            isInitialized = true;
        }

        for (unsigned chNr = 0; chNr < maxChannel; chNr++)
        {
            if (!channelInfo[chNr].isReserved)
            {
                channelInfo[chNr].isReserved = true;
                return new FTM_Channel(r, &channelInfo[chNr]);
            }
        }
        return nullptr;
    }

    template <unsigned m>
    void FTM_t<m>::isr()
    {
        for (unsigned i = 0; i < maxChannel; i++)
        {
            FTM_ChannelInfo* ci = &channelInfo[i];  // pre resolving the references turns out to be slightly faster
            FTM_CH_t* cr = ci->chRegs;
            if ((cr->SC & (FTM_CSC_CHIE | FTM_CSC_CHF)) == (FTM_CSC_CHIE | FTM_CSC_CHF)) // only handle if channel is active (CHIE set) and overflowed (CHF set)
            {
                if (ci->isPeriodic)
                {
                    cr->SC &= ~FTM_CSC_CHF;       // clear channel flag
                    cr->CV = r->CNT + ci->reload; // set compare value to 'reload' counts ahead of counter
                } else
                {
                    cr->SC &= ~FTM_CSC_CHIE;      //disable interrupt in on shot mode
                }
                ci->callback();
            }
        }
    }

    template <unsigned m>
    FTM_ChannelInfo FTM_t<m>::channelInfo[maxChannel];

    template <unsigned m>
    bool FTM_t<m>::isInitialized = false;

#if defined(T3_0)
    constexpr TimerGenerator* FTM0 = FTM_t<0>::getTimer;
    constexpr TimerGenerator* FTM1 = FTM_t<1>::getTimer;
#elif defined(T3_1) || defined(T3_2)
    constexpr TimerGenerator* FTM0 = FTM_t<0>::getTimer;
    constexpr TimerGenerator* FTM1 = FTM_t<1>::getTimer;
    constexpr TimerGenerator* FTM2 = FTM_t<2>::getTimer;
#elif defined(T3_5)
    constexpr TimerGenerator* FTM0 = FTM_t<0>::getTimer;
    constexpr TimerGenerator* FTM1 = FTM_t<1>::getTimer;
    constexpr TimerGenerator* FTM2 = FTM_t<2>::getTimer;
    constexpr TimerGenerator* FTM3 = FTM_t<3>::getTimer;

#elif defined(T3_6)
    constexpr TimerGenerator* FTM0 = FTM_t<0>::getTimer;
    constexpr TimerGenerator* FTM1 = FTM_t<1>::getTimer;
    constexpr TimerGenerator* FTM2 = FTM_t<2>::getTimer;
    constexpr TimerGenerator* FTM3 = FTM_t<3>::getTimer;
    constexpr TimerGenerator* FTM4 = FTM_t<3>::getTimer;
#endif

} // namespace TeensyTimerTool
