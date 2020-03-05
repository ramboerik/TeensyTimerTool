#pragma once

#include <Arduino.h>
#include "../../ITimerChannel.h"

using namespace std::placeholders;
namespace TeensyTimerTool
{
    class GptChannel : public ITimerChannel {
    private:
        HardwareTimer m_timer;
        bool isPeriodic;

    public:
        static inline void isr(HardwareTimer* timer) {
            if(timer == nullptr){
                return;
            }

            GptChannel* me = (GptChannel*)timer->getArg();
            if(me == nullptr){
                return;
            }

            if(!me->isPeriodic){
                // stop after one interrupt if running in one shot mode.
                timer->pause();
            }

            callback_t callback = *(me->pCallback);
            callback();
        }

        GptChannel(TIM_TypeDef* timer, callback_t* cbStorage) : ITimerChannel(cbStorage), m_timer(timer){}

        virtual ~GptChannel() {
            m_timer.detachInterrupt();
            setCallback(nullptr);
        }

        errorCode begin(callback_t cb, uint32_t micros, bool periodic) override {
            isPeriodic = periodic;
            setCallback(cb);
            m_timer.attachInterrupt(GptChannel::isr, (void*)this);

            if(!isPeriodic){
                // wait to start until trigger is called
                return errorCode::OK;
            }
            m_timer.setOverflow(micros, MICROSEC_FORMAT);
            m_timer.resume();
            return errorCode::OK;
        }

        errorCode trigger(uint32_t micros) override { // not working, triggered immediately, something not reset with setOverflow?
            m_timer.setOverflow(micros, MICROSEC_FORMAT);
            m_timer.resume();
            return errorCode::OK;
        }

        void setPeriod(uint32_t micros) override {
            // pause/resume needed?
            m_timer.setOverflow(micros, MICROSEC_FORMAT);
        }
    };
};