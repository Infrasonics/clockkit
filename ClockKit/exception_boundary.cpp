#include <string>

#include "Common.h"
#include "exception_boundary.h"
#include "ConfigReader.h"
#include "Exceptions.h"


namespace boundary {
extern "C" {

inline boundary::Result phaseLockedClockFromConfig(dex::PhaseLockedClock* res, const char* filename) {

    try {
        res = dex::PhaseLockedClockFromConfigFile(std::string(filename));
    } catch (dex::ClockException &e) {
        return boundary::Result::ClockOutOfSync;
    } catch (dex::Exception &e) {
        return boundary::Result::IOError;
    }
    return boundary::Result::OK;
}


inline boundary::Result phaseLockedClockGetValue(const dex::PhaseLockedClock* clock, dex::timestamp_t& ts) {
    try {
        ts = const_cast<dex::PhaseLockedClock*>(clock)->getValue();
    } catch (dex::ClockException) {
        return boundary::Result::ClockOutOfSync;
    }

    return boundary::Result::OK;
}


inline boundary::Result phaseLockedClockGetOffset(const dex::PhaseLockedClock* clock, int& offset) {
    try {
        offset = const_cast<dex::PhaseLockedClock*>(clock)->getOffset();
    } catch (dex::ClockException) {
        return boundary::Result::ClockOutOfSync;
    }

    return boundary::Result::OK;
}


inline bool phaseLockedClockIsSynchronized(const dex::PhaseLockedClock* clock) {
    try {
        return const_cast<dex::PhaseLockedClock*>(clock)->isSynchronized();
    } catch (dex::ClockException) {
        return false;
    }
    return false;
}

} // extern "C"
} // ns boundary

