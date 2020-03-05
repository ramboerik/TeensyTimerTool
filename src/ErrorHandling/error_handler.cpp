#include <Arduino.h>
#include "error_handler.h"
#include "types.h"

namespace TeensyTimerTool
{
    ErrorHandler::ErrorHandler(Stream& s) : stream(s)
    {
        pinMode(LED_BUILTIN, OUTPUT);
    }

    void ErrorHandler::operator()(errorCode code) const
    {
        const char* txt;

        switch (code)
        {
            case errorCode::OK:
                txt = "OK";
                break;

            // warnings
            case errorCode::periodOverflow:
                txt = "Period overflow, set to maximum";
                break;

            // general errors
            case errorCode::reload:
                txt = "Period must not be zero";
                break;
            case errorCode::noFreeChannel:
                txt = "Timer module has no free channel";
                break;
            case errorCode::noFreeModule:
                txt = "Timer pool contains no free timer";
                break;
            case errorCode::notImplemented:
                txt = "Function not implemented";
                break;
            case errorCode::notInitialized:
                txt = "Timer not initialized or available";
                break;

            default:
                txt = "Unknown error";
                break;
        }

        if ((int)code < 0) // in case of warnings we return after printing
        {
            stream.print("W- ");
            stream.print((int)code);
            stream.print(": ");
            stream.println(txt);
            return;
        }
        stream.print("E- ");
        stream.print((int)code);
        stream.print(": ");
        stream.println(txt);
        while (true)
        {
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
            delay(50);
        }
    }

    errorFunc_t errFunc;

    errorCode postError(errorCode e)
    {
        if (errFunc != nullptr) errFunc(e);
        return e;
    }

    void attachErrFunc(errorFunc_t _errFunc)
    {
        errFunc = _errFunc;
    }

}