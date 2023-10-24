//
// Created by Danie on 24.10.2023.
//
#include "threepp/threepp.hpp"
#include "colors.h"

using namespace threepp;

const threepp::Color grey = Color(grey);
const threepp::Color green = Color::green;
const threepp::Color red = Color::red;
const threepp::Color orange = Color::orange;
const threepp::Color yellow = Color::yellow;
const threepp::Color purple = Color::purple;
const threepp::Color cyan = Color::cyan;
const threepp::Color blue = Color::blue;

[[maybe_unused]] std::vector<threepp::Color> GetCellColors() {
    return {grey, green, red, orange, yellow, purple, cyan, blue};
}

