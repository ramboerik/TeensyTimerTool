#pragma once

#include "boardDef.h"

//================================================
// Board specifics

#if defined(TLC)
    #include "TeensyTimer.h"
   #include "ErrorHandling/ErrorCodes.h"
    #include "Teensy/TCK/TCK.h"
#elif defined(T3_0)
    #include "TeensyTimer.h"
    #include "ErrorHandling/ErrorCodes.h"
    #include "Teensy/TCK/TCK.h"
    #include "Teensy/FTM/FTM.h"

#elif defined(T3_1) || defined (T3_2)
    #include "kinetis.h"
    #include "TeensyTimer.h"
    #include "ErrorHandling/ErrorCodes.h"
    #include "Teensy/TCK/TCK.h"
    #include "Teensy/FTM/FTM.h"

#elif defined (T3_5)
    #include "kinetis.h"
    #include "TeensyTimer.h"
    #include "ErrorHandling/ErrorCodes.h"
    #include "Teensy/TCK/TCK.h"
    #include "Teensy/FTM/FTM.h"

#elif defined (T3_6)
    #include "kinetis.h"
    #include "TeensyTimer.h"
   #include "ErrorHandling/ErrorCodes.h"
    #include "Teensy/TCK/TCK.h"
    #include "Teensy/FTM/FTM.h"

#elif defined(T4_0)
    #include <imxrt.h>
    #include "TeensyTimer.h"
    #include "ErrorHandling/ErrorCodes.h"
    #include "Teensy/TCK/TCK.h"
    #include "Teensy/GPT/GPT.h"
    #include "Teensy/TMR/TMR.h"

#elif defined(STM32F4xx)
    #include "TeensyTimer.h"
    #include "ErrorHandling/ErrorCodes.h"
    #include "STM32F4/TCK/TCK.h"
    #include "STM32F4/GPT/GPT.h"

#else
    #error "Board not supported"
#endif

#include "config.h"
