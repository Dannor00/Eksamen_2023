#pragma once

#include "threepp/threepp.hpp"

using namespace threepp;

struct MyKeyListener : KeyListener {
    float& t;

    explicit MyKeyListener(float& t);

    void onKeyPressed(KeyEvent evt) override;
    void onKeyReleased(KeyEvent evt) override;
    void onKeyRepeat(KeyEvent evt) override;
};
