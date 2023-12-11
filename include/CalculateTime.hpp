#ifndef EKSAMEN_2023_CALCULATETIME_HPP
#define EKSAMEN_2023_CALCULATETIME_HPP

#include <chrono>

// modifisert av Ai
class TimeUtils {
public:
    static TimeUtils &getInstance() {
        static TimeUtils instance;
        return instance;
    }

    static float calculateDeltaTime() {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - getInstance().startTime);
        getInstance().startTime = currentTime;
        return static_cast<float>(duration.count()) * 1e-6f;
    }

    TimeUtils() = default;

    ~TimeUtils() = default;

    std::chrono::high_resolution_clock::time_point startTime{};
};

#endif // EKSAMEN_2023_CALCULATETIME_HPP
