#include "threepp/threepp.hpp"
#include "thread"
#include "include/game.hpp"
#include "include/Keylistner.hpp"
#include "include/CalculateTime.hpp"

int main() {
    threepp::Canvas canvas("Tetris", {{"aa", 4}});
    canvas.setSize({900, 900});

    threepp::TextRenderer textRenderer;

    auto &scoreTextHandle = textRenderer.createHandle();
    scoreTextHandle.setPosition(canvas.size().width - 340, 100);
    scoreTextHandle.color = threepp::Color::white;
    scoreTextHandle.scale = 3;

    auto &gameOverTextHandle = textRenderer.createHandle();
    gameOverTextHandle.setPosition(canvas.size().width - 350, 600);
    gameOverTextHandle.color = threepp::Color::white;
    gameOverTextHandle.scale = 3;

    auto &nextTextHandle = textRenderer.createHandle("Next");
    nextTextHandle.setPosition(canvas.size().width - 300, 300);
    nextTextHandle.color = threepp::Color::white;
    nextTextHandle.scale = 3;

    Game game;

    threepp::GLRenderer renderer(canvas.size());
    renderer.setClearColor(threepp::Color::blue);

    auto camera = threepp::PerspectiveCamera::create(65, canvas.aspect(), 0.1f, 1000);
    camera->position.set(110, 0, 500);

    auto scene = threepp::Scene::create();

    const double targetFrameTime = 1.0 / 60.0;
    threepp::Clock clock;
    TimeUtils timeUtils;

    MyKeyListener kl{game};
    canvas.addKeyListener(&kl);

    double previousTime = clock.getElapsedTime();
    double lag = 0.0;

    Block block;

    // Move this outside the rendering loop
    Position whiteBoxPosition = Position(10, 14);
    float customWidth = 200.0f;
    float customHeight = 100.0f;
    float customDepth = 1.0f;


    canvas.animate([&] {
        double currentTime = clock.getElapsedTime();
        double elapsed = currentTime - previousTime;
        previousTime = currentTime;
        lag += elapsed;

        while (lag >= targetFrameTime) {
            lag -= targetFrameTime;
            float deltaTime = timeUtils.calculateDeltaTime();

            game.Update(*scene, deltaTime);
            game.Draw(*scene);

            if (!game.gameOver) {
                game.RedrawLockedBlocks(*scene);
            }

            if (game.gameOver) {
                gameOverTextHandle.setText("GAME OVER!");
            }

            if (!game.gameOver) {
                gameOverTextHandle.setText("");
            }

            scoreTextHandle.setText("Score: " + std::to_string(game.score));

            // Move these calculations inside the rendering loop
            Position whiteBoxPosition = Position(10, 14);
            float customWidth = 200.0f;
            float customHeight = 100.0f;
            float customDepth = 1.0f;

            // Create the white box inside the rendering loop
            block.CreateWhiteBox(*scene, whiteBoxPosition, customWidth, customHeight, customDepth);
        }

        renderer.render(*scene, *camera);

        renderer.resetState();
        textRenderer.render();

        auto frameRenderTime = clock.getElapsedTime() - currentTime;
        auto sleepDuration = std::chrono::milliseconds(static_cast<int>((targetFrameTime - frameRenderTime) * 1000));
        std::this_thread::sleep_for(sleepDuration);
    });
}