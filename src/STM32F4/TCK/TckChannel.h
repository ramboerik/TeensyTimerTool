#pragma once

#include "../../ITimerChannel.h"

namespace TeensyTimerTool
{
    class TCK_t;

    class TckChannel : public ITimerChannel
    {
     public:
        inline TckChannel() { triggered = false; }
        inline virtual ~TckChannel(){};

        inline errorCode begin(callback_t cb, uint32_t period, bool periodic) override
        {
            triggered = false;
            this->periodic = periodic;
            this->period = period * (F_CPU / 1'000'000);
            this->callback = cb;

            startCNT = dwt_getCycles();
            return errorCode::OK;
        }

        inline void start() override
        {
            this->startCNT = dwt_getCycles();
            this->triggered = true;
        }

        inline errorCode stop() override
        {
            this->triggered = false;
            return errorCode::OK;
        }

        inline void setPeriod(uint32_t microSeconds) override;
        inline uint32_t getPeriod(void) override;

        inline errorCode trigger(uint32_t delay) override// µs
        {
            this->startCNT = dwt_getCycles();
            this->period = delay * (F_CPU / 1'000'000) - 68;
            this->triggered = true;
            return errorCode::OK;
        }

     protected:
        uint32_t startCNT, period;
        callback_t callback;
        bool triggered;
        bool periodic;

        inline void tick();
        bool block = false;

        friend TCK_t;
    };

    // IMPLEMENTATION ==============================================

    void TckChannel::tick()
    {
        static bool lock = false;

        if (!lock && period != 0 && triggered && (dwt_getCycles() - startCNT) >= period)
        {
            lock = true;
            startCNT = dwt_getCycles();
            triggered = periodic; // i.e., stays triggerd if periodic, stops if oneShot
            callback();
            lock = false;
        }
    }

    void TckChannel::setPeriod(uint32_t microSeconds)
    {
        period = microSeconds * (F_CPU / 1'000'000) ;
    }
    uint32_t TckChannel::getPeriod()
    {
        return period * (1'000'000.0f / F_CPU);
    }

} // namespace TeensyTimerTool
