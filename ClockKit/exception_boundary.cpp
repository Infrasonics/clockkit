#include <string>

#include "Common.h"
#include "exception_boundary.h"
#include "ConfigReader.h"
#include "Exceptions.h"


namespace boundary {
extern "C" {

    boundary::Result PhaseLockedClockFromConfig(dex::PhaseLockedClock* res, const char* filename) {

    try {
        res = dex::PhaseLockedClockFromConfigFile(std::string(filename));
    } catch (dex::ClockException &e) {
        return boundary::Result::ClockOutOfSync;
    } catch (dex::Exception &e) {
        return boundary::Result::IOError;
    }
    return boundary::Result::OK;
}


boundary::Result PhaseLockedClock_GetValue(dex::PhaseLockedClock* clock, dex::timestamp_t& ts) {
    try {
        ts = clock->getValue();
    } catch (dex::ClockException) {
        return boundary::Result::ClockOutOfSync;
    }

    return boundary::Result::OK;
}


boundary::Result PhaseLockedClock_GetOffset(dex::PhaseLockedClock* clock, int& offset) {
    try {
        offset = clock->getOffset();
    } catch (dex::ClockException) {
        return boundary::Result::ClockOutOfSync;
    }

    return boundary::Result::OK;
}


bool PhaseLockedClock_isSynchronized(dex::PhaseLockedClock* clock) {
    try {
        return clock->isSynchronized();
    } catch (dex::ClockException) {
        return false;
    }
    return false;
}

} // extern "C"
} // ns boundary

