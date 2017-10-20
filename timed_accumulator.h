#pragma once

#include <chrono>

using namespace std::chrono;

template<typename T>
class TimedAccumulator
{
    static_assert(std::is_arithmetic<T>::value,
                  "TimedAccumulator will only work with arithmetic types");

public:
    template<typename Rep, typename Period>
    TimedAccumulator(duration<Rep, Period> time_interval)
        : accumulator(),
          before(system_clock::now()),
          time_interval(duration_cast<seconds>(time_interval))
    {}

    void accumulate(T value, std::function<void(T)> func)
    {
        accumulator += value;

        seconds elapsed = duration_cast<seconds>(system_clock::now() - before);
        if(elapsed >= time_interval)
        {
            func(accumulator);

            before = system_clock::now();
            accumulator = T();
        }
    }

private:
    T accumulator;
    system_clock::time_point before;
    seconds time_interval;
};
