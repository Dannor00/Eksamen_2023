
#ifndef LIVE_31_10_PERSON_HPP
#define LIVE_31_10_PERSON_HPP

#include <string>

class Person {

public:
    Person(const std::string &firstName, const std::string &lastName)
            : firstName_(firstName), lastName_(lastName) {}

    const std::string &getFirstName() const {
        return firstName_;
    }

    const std::string &getLastName() const {
        return lastName_;
    }

    std::string getFullName() const {

        return firstName_ + " " + lastName_;
    }

private:
    std::string firstName_;
    std::string lastName_;
};

#endif//LIVE_31_10_PERSON_HPP
