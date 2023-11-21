#ifndef EKSAMEN_2023_OBSERVER_HPP
#define EKSAMEN_2023_OBSERVER_HPP

#include "../include/Block.hpp"

class Observer {
public:
    virtual void onChanged(const Block& block) = 0;  // Add the parameter
};

#endif // EKSAMEN_2023_OBSERVER_HPP
