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

        callback_function_t isr = [this](void) {
            if(!isPeriodic){
                // stop after one interrupt if running in one shot mode.
                m_timer.pause();
            }
            callback_t callback = *(pCallback);
            callback();
        };

    public:
        GptChannel(TIM_TypeDef* timer, callback_t* cbStorage) : ITimerChannel(cbStorage), m_timer(timer){ }

        virtual ~GptChannel() {
            m_timer.detachInterrupt();
            setCallback(nullptr);
        }

        errorCode begin(callback_t cb, uint32_t micros, bool periodic) override {
            isPeriodic = periodic;
            setCallback(cb);
            m_timer.attachInterrupt(isr);

            if(!isPeriodic){
                // wait to start until trigger is called
                return errorCode::OK;
            }
            m_timer.pause();
            m_timer.setOverflow(micros, MICROSEC_FORMAT);
            m_timer.refresh();
            m_timer.resume();
            return errorCode::OK;
        }

        errorCode trigger(uint32_t micros) override { // not working, triggered immediately, something not reset with setOverflow?
            m_timer.pause();
            m_timer.setOverflow(micros, MICROSEC_FORMAT);
            m_timer.refresh();
            m_timer.resume();
            return errorCode::OK;
        }

        void setPeriod(uint32_t micros) override {
            // pause/resume needed?
            m_timer.setOverflow(micros, MICROSEC_FORMAT);
        }
    };
};