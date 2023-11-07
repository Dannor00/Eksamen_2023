#include "threepp/threepp.hpp"
#include "colors.h"

using namespace threepp;

const Color grey = Color::grey;
const Color green = Color::green;
const Color red = Color::red;
const Color orange = Color::orange;
const Color yellow = Color::yellow;
const Color purple = Color::purple;
const Color cyan = Color::cyan;
const Color blue = Color::blue;

const std::vector<Color> cellColors = {grey, green, red, orange, yellow, purple, cyan, blue};

std::vector<Color> GetCellColors() {
    return cellColors;
}


