#include "ConfigReader.h"
#include "Exceptions.h"
#include "PhaseLockedClock.h"

int main(int argc, char* argv[])
{
    if (argc != 2 && argc != 3) {
        std::cerr << "usage: " << argv[0] << " config_file [duration]\n";
        return 1;
    }

    dex::PhaseLockedClock* clock = dex::PhaseLockedClockFromConfigFile(argv[1]);
    if (clock == NULL) {
        std::cerr << argv[0] << ": failed to get a clock.\n";
        return 1;
    }

    const auto fTerminate = argc == 3;
    auto runtime = fTerminate ? atof(argv[2]) : 0.0;

    while (true) {
        try {
            std::cout << "offset: " << clock->getOffset()
                      << "\ntime: " << dex::Timestamp::timestampToString(clock->getValue())
                      << std::endl;
            // endl flushes stdout, to show output even after Ctrl+C.
        }
        catch (dex::ClockException& e) {
            std::cout << "offset: OUT OF SYNC\n";
        }
        ost::Thread::sleep(100);  // msec
        if (fTerminate) {
            runtime -= 0.1;  // sec
            if (runtime <= 0.0) {
                clock->die();
                break;
            }
        }
    }
    return 0;
}
