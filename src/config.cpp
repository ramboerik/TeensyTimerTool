#include "config.h"
#include "boardDef.h"

#if defined(T4_0)
    #include "Teensy/TMR/TMR.h"
    #include "Teensy/GPT/GPT.h"
    #include "Teensy/TCK/TCK.h"

    namespace TeensyTimerTool
    {
        TimerGenerator* const TMR1 = TMR_t<0>::getTimer;
        TimerGenerator* const TMR2 = TMR_t<1>::getTimer;
        TimerGenerator* const TMR3 = TMR_t<2>::getTimer;
        TimerGenerator* const TMR4 = TMR_t<3>::getTimer;

        TimerGenerator* const GPT1 = GPT_t<0>::getTimer;
        TimerGenerator* const GPT2 = GPT_t<1>::getTimer;

        TimerGenerator* const TCK = TCK_t::getTimer;
    }

#elif defined (T3_6) || defined (T3_5)
    #include "Teensy/FTM/FTM.h"
    #include "Teensy/TCK/TCK.h"

    namespace TeensyTimerTool
    {
        TimerGenerator* const TCK = TCK_t::getTimer;

        TimerGenerator* const FTM0 = FTM_t<0>::getTimer;
        TimerGenerator* const FTM1 = FTM_t<1>::getTimer;
        TimerGenerator* const FTM2 = FTM_t<2>::getTimer;
        TimerGenerator* const FTM3 = FTM_t<3>::getTimer;
        TimerGenerator* const FTM4 = FTM_t<3>::getTimer;

    }
#elif defined(T3_2)
    #include "Teensy/FTM/FTM.h"
    #include "Teensy/TCK/TCK.h"

    namespace TeensyTimerTool
    {
        TimerGenerator* const TCK = TCK_t::getTimer;

        TimerGenerator* const FTM0 = FTM_t<0>::getTimer;
        TimerGenerator* const FTM1 = FTM_t<1>::getTimer;
        TimerGenerator* const FTM2 = FTM_t<2>::getTimer;
    }

#elif defined(T3_0)
    #include "Teensy/FTM/FTM.h"
    #include "Teensy/TCK/TCK.h"

    namespace TeensyTimerTool
    {
        TimerGenerator* const TCK = TCK_t::getTimer;

        TimerGenerator* const FTM0 = FTM_t<0>::getTimer;
        TimerGenerator* const FTM1 = FTM_t<1>::getTimer;
    }

#elif defined(TLC)
    //#include "Teensy/FTM/FTM.h"
    #include "Teensy/TCK/TCK.h"

    namespace TeensyTimerTool
    {
        TimerGenerator* const TCK = TCK_t::getTimer;

        // TimerGenerator* const FTM0 = FTM_t<0>::getTimer;
        // TimerGenerator* const FTM1 = FTM_t<1>::getTimer;
    }

#elif defined(STM32F4xx)
    #include "STM32F4/TCK/TCK.h"
    #include "STM32F4/GPT/GPT.h"

    namespace TeensyTimerTool {
        TimerGenerator* const GPT1 = GPT_t<TIM1_BASE>::getTimer;
        TimerGenerator* const GPT2 = GPT_t<TIM2_BASE>::getTimer;
        TimerGenerator* const GPT3 = GPT_t<TIM3_BASE>::getTimer;
        TimerGenerator* const GPT4 = GPT_t<TIM4_BASE>::getTimer;
        TimerGenerator* const GPT5 = GPT_t<TIM5_BASE>::getTimer;
        TimerGenerator* const GPT6 = GPT_t<TIM6_BASE>::getTimer;
        TimerGenerator* const GPT7 = GPT_t<TIM7_BASE>::getTimer;
        TimerGenerator* const GPT8 = GPT_t<TIM8_BASE>::getTimer;
        TimerGenerator* const GPT9 = GPT_t<TIM9_BASE>::getTimer;
        TimerGenerator* const GPT10 = GPT_t<TIM10_BASE>::getTimer;
        TimerGenerator* const GPT11 = GPT_t<TIM11_BASE>::getTimer;
        TimerGenerator* const GPT12 = GPT_t<TIM12_BASE>::getTimer;
        TimerGenerator* const GPT13 = GPT_t<TIM13_BASE>::getTimer;
        TimerGenerator* const GPT14 = GPT_t<TIM14_BASE>::getTimer;
        TimerGenerator* const TCK = TCK_t::getTimer;
    }

#endif
