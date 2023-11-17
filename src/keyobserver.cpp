
#include "../include/keyobserver.hpp"
#include <iostream>

MyKeyListener::MyKeyListener(float& t) : t(t) {}

void MyKeyListener::onKeyPressed(KeyEvent evt) {
    if (evt.key == Key::W || evt.key == Key::A || evt.key == Key::S || evt.key == Key::D || evt.key == Key::SPACE) {
        std::cout << "onKeyPressed at t=" << t << " - Key: " << static_cast<int>(evt.key) << std::endl;
    }
}

void MyKeyListener::onKeyReleased(KeyEvent evt) {
    if (evt.key == Key::W || evt.key == Key::A || evt.key == Key::S || evt.key == Key::D || evt.key == Key::SPACE) {
        std::cout << "onKeyReleased at t=" << t << " - Key: " << static_cast<int>(evt.key) << std::endl;
    }
}

void MyKeyListener::onKeyRepeat(KeyEvent evt) {
    if (evt.key == Key::W || evt.key == Key::A || evt.key == Key::S || evt.key == Key::D || evt.key == Key::SPACE) {
        std::cout << "onKeyRepeat at t=" << t << " - Key: " << static_cast<int>(evt.key) << std::endl;
    }
}
