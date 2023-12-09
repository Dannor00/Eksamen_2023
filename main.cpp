#include <memory>
#include <iostream>
#include "thread"
#include "include/game.hpp"
#include "include/Keylistner.hpp"
#include "include/CalculateTime.hpp"

constexpr int kCanvasWidth = 900;
constexpr int kCanvasHeight = 900;
constexpr int kScoreTextX = 340;
constexpr int kScoreTextY = 100;
constexpr int kGameOverTextX = 350;
constexpr int kGameOverTextY = 600;
constexpr int kNextTextX = 300;
constexpr int kNextTextY = 300;
constexpr int kTargetFrameRate = 60;

void SetupTextHandles(threepp::TextRenderer &textRenderer, std::reference_wrapper<threepp::TextHandle> scoreTextHandle,
                      std::reference_wrapper<threepp::TextHandle> gameOverTextHandle) {
    scoreTextHandle = textRenderer.createHandle();
    scoreTextHandle.get().color = threepp::Color::white;
    scoreTextHandle.get().scale = 3;

    gameOverTextHandle = textRenderer.createHandle();
    gameOverTextHandle.get().color = threepp::Color::white;
    gameOverTextHandle.get().scale = 3;

    auto &nextTextHandle = textRenderer.createHandle("Next");
    nextTextHandle.setPosition(kCanvasWidth - kNextTextX, kNextTextY);
    nextTextHandle.color = threepp::Color::white;
    nextTextHandle.scale = 3;
}

void UpdateTextHandles(threepp::TextHandle &scoreTextHandle, threepp::TextHandle &gameOverTextHandle, Game &game) {
    scoreTextHandle.setPosition(kCanvasWidth - kScoreTextX, kScoreTextY);
    scoreTextHandle.setText("Score: " + std::to_string(game.score));
    scoreTextHandle.scale = 3;  // Adjust the scale for the score text

    gameOverTextHandle.setPosition(kCanvasWidth - kGameOverTextX, kGameOverTextY);

    if (game.gameOver) {
        gameOverTextHandle.setText("GAME OVER!");
        gameOverTextHandle.scale = 3;  // Adjust the scale for the game over text
    } else {
        gameOverTextHandle.setText("");
    }
}

int main() {
    auto canvas = std::make_shared<threepp::Canvas>("Tetris");
    canvas->setSize({kCanvasWidth, kCanvasHeight});

    threepp::TextRenderer textRenderer;
    std::reference_wrapper<threepp::TextHandle> scoreTextHandle = textRenderer.createHandle();
    std::reference_wrapper<threepp::TextHandle> gameOverTextHandle = textRenderer.createHandle();

    SetupTextHandles(textRenderer, scoreTextHandle, gameOverTextHandle);

    auto game = std::make_unique<Game>();
    auto renderer = std::make_unique<threepp::GLRenderer>(canvas->size());
    renderer->setClearColor(threepp::Color::blue);

    auto camera = std::make_unique<threepp::PerspectiveCamera>(65, canvas->aspect(), 0.1f, 1000);
    camera->position.set(110, 0, 500);

    auto scene = std::make_unique<threepp::Scene>();

    const double targetFrameTime = 1.0 / kTargetFrameRate;
    threepp::Clock clock;
    TimeUtils timeUtils;

    MyKeyListener kl{*game};
    canvas->addKeyListener(&kl);

    double previousTime = clock.getElapsedTime();
    double lag = 0.0;

    auto block = std::make_unique<Block>();

    canvas->animate([&] {
        double currentTime = clock.getElapsedTime();
        double elapsed = currentTime - previousTime;
        previousTime = currentTime;
        lag += elapsed;

        while (lag >= targetFrameTime) {
            lag -= targetFrameTime;
            float deltaTime = timeUtils.calculateDeltaTime();

            game->Update(*scene, deltaTime);

            if (!game->gameOver) {
                game->RedrawLockedBlocks(*scene);
            }

            Position whiteBoxPosition = Position(10, 14);
            float customWidth = 200.0f;
            float customHeight = 100.0f;
            float customDepth = 1.0f;

            // Create the white box inside the rendering loop
            block->CreateWhiteBox(*scene, whiteBoxPosition, customWidth, customHeight, customDepth);
        }

        // Update text handles after the game has been updated
        UpdateTextHandles(scoreTextHandle, gameOverTextHandle, *game);

        renderer->render(*scene, *camera);

        renderer->resetState();
        textRenderer.render();

        auto frameRenderTime = clock.getElapsedTime() - currentTime;
        auto sleepDuration = std::chrono::milliseconds(static_cast<int>((targetFrameTime - frameRenderTime) * 1000));
        std::this_thread::sleep_for(sleepDuration);
    });

    return 0;
}
