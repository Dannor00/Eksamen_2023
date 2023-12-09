
#ifndef EKSAMEN_2023_KEYLISTNER_HPP
#define EKSAMEN_2023_KEYLISTNER_HPP


class MyKeyListener : public threepp::KeyListener {
public:
    explicit MyKeyListener(Game &game) : game(game) {}

    void onKeyPressed(threepp::KeyEvent evt) override {
        if (game.gameOver && evt.key == threepp::Key::R) {
            game.gameOver = false;
            game.Reset();
        } else if (evt.key == threepp::Key::W) {
            game.RotateBlock();
        } else if (evt.key == threepp::Key::S) {
            game.MoveBlock(1, 0);  // Example: Move down by increasing row
            game.UpdateScore(0, 1);
        } else if (evt.key == threepp::Key::D) {
            game.MoveBlock(0, 1);  // Example: Move right by increasing column
        } else if (evt.key == threepp::Key::A) {
            game.MoveBlock(0, -1); // Example: Move left by decreasing column
        }
    }

private:
    Game &game;
};

#endif //EKSAMEN_2023_KEYLISTNER_HPP
