#include "ErrorHandler.h"
#include <Arduino.h>

namespace TeensyTimerTool
{
    Stream* stream;

    void vHandler(errorCode code)
    {
        const char* txt;

        switch (code)
        {
            case errorCode::OK:             txt = "OK"; break;

            // warnings
            case errorCode::periodOverflow: txt = "Timer period too long, will be clamped to max"; break;

            // general errors
            case errorCode::reload:         txt = "Period must not be zero"; break;
            case errorCode::noFreeChannel:  txt = "Timer module has no free channel"; break;
            case errorCode::noFreeModule:   txt = "Timer pool contains no free timer"; break;

            default:
                txt = "Unknown error";
                break;
        }

        int int_code = static_cast<int>(code);
        if (int_code < 0)
        {
            stream->print("Warning: ");
            stream->print(int_code);
            stream->println(txt);
            return;
        }
        stream->print("Error: ");
        stream->print(int_code);
        stream->println(txt);

        while (true)
        {
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
            delay(50);
        }
    }

    errorFunc_t verboseErrorHandler(Stream& s)
    {
        stream = &s;
        return vHandler;
    }

    // errorFunc_t* ErrorHandler::callback = nullptr;

} // namespace