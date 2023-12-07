#ifndef EKSAMEN_2023_CALCULATETIME_HPP
#define EKSAMEN_2023_CALCULATETIME_HPP


class TimeUtils {
public:
    TimeUtils() : startTime(std::chrono::high_resolution_clock::now()) {}

    float calculateDeltaTime() {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - startTime);
        startTime = currentTime;
        return static_cast<float>(duration.count()) * 1e-6f;
    }

private:
    std::chrono::high_resolution_clock::time_point startTime;
};


#endif //EKSAMEN_2023_CALCULATETIME_HPP
