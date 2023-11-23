
#ifndef EKSAMEN_2023_KEYLISTNER_HPP
#define EKSAMEN_2023_KEYLISTNER_HPP

#include "../include/game.hpp"

class MyKeyListener : public KeyListener {
public:
    explicit MyKeyListener(Game &game) : game(game) {}

    void onKeyPressed(KeyEvent evt) override {
        if (evt.key == threepp::Key::W) {
            game.RotateBlock();
        } else if (evt.key == threepp::Key::S) {
            game.moveCurrentBlock(1, 0);  // Example: Move down by increasing row
        } else if (evt.key == threepp::Key::D) {
            game.moveCurrentBlock(0, 1);  // Example: Move right by increasing column
        } else if (evt.key == threepp::Key::A) {
            game.moveCurrentBlock(0, -1); // Example: Move left by decreasing column
        }
    }

private:
    Game &game;
};

#endif //EKSAMEN_2023_KEYLISTNER_HPP
