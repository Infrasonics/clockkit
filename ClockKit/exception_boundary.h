#pragma once

#include "PhaseLockedClock.h"
#include "Timestamp.h"

extern "C" {

    namespace boundary {
        enum Result {
            OK,
            ClockOutOfSync,
            ClockTimeout,
            ClockPacketError,
            IOError
        };

        Result phaseLockedClockFromConfig(dex::PhaseLockedClock* res, const char* filename);
        Result phaseLockedClockGetValue(const dex::PhaseLockedClock* clock, dex::timestamp_t& ts);
        Result phaseLockedClockGetOffset(const dex::PhaseLockedClock* clock, int& offset);
        bool phaseLockedClockIsSynchronized(const dex::PhaseLockedClock* clock);
    }
}
