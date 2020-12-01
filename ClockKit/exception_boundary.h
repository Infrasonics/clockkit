#ifndef __EXCEPTION_BOUNDARY
#define __EXCEPTION_BOUNDARY

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

    Result PhaseLockedClockFromConfig(dex::PhaseLockedClock* res, const char* filename);
    Result PhaseLockedClock_GetValue(dex::PhaseLockedClock* clock, dex::timestamp_t& ts);
    Result PhaseLockedClock_GetOffset(dex::PhaseLockedClock* clock, int& offset);
    bool PhaseLockedClock_isSynchronized(dex::PhaseLockedClock* clock);
    }
}

#endif
