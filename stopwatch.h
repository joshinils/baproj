#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

/// based on an answer in
/// https://stackoverflow.com/questions/38977879/how-can-i-measure-the-execution-time-of-one-thread
class Stopwatch
{
public:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> last;
    std::string fromWhere = "";
    Stopwatch(std::string fromWhere = "")
        : start(std::chrono::high_resolution_clock::now())
        , last(std::chrono::high_resolution_clock::now())
        , fromWhere(fromWhere)
    {
        printTime("since it just started.");
    }

    ~Stopwatch() { printTime("and is now stopping."); }

    inline double elapsed()
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> thisTime =
        std::chrono::high_resolution_clock::now();
        double deltaTime = std::chrono::duration<double, std::milli>(thisTime - start).count();
        return deltaTime;
    }

    inline double elapsedLast()
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> thisTime =
        std::chrono::high_resolution_clock::now();
        double deltaTime = std::chrono::duration<double, std::milli>(thisTime - last).count();
        last             = thisTime;
        return deltaTime;
    }

    inline void printTime(std::string after = "")
    {
        std::stringstream s;
        s << "Time in thread " << std::this_thread::get_id() << " is at " << std::setw(8) << std::fixed
          << std::setprecision(2) << elapsed() << "ms, " << std::fixed << std::setw(8) << elapsedLast()
          << "ms since last stopping. \"" << fromWhere << "\" " << after << '\n';
        std::cout << s.str() << std::flush;
    }
};
