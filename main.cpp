#include "threepp/threepp.hpp"
#include "thread"
#include "include/game.hpp"
#include "include/Keylistner.hpp"
#include "include/CalculateTime.hpp"

int main() {
    // Create a canvas for rendering
    threepp::Canvas canvas("Tetris", {{"aa", 4}});
    canvas.setSize({900, 900});

    TextRenderer textRenderer;

    // Create the score handle once
    auto &scoreHandle = textRenderer.createHandle();
    scoreHandle.setPosition(canvas.size().width - 280, 0);
    scoreHandle.color = Color::white;
    scoreHandle.scale = 3;

    auto &handle2 = textRenderer.createHandle("Next");
    handle2.setPosition(canvas.size().width - 240, +210);
    handle2.color = Color::white;
    handle2.scale = 3;

    // Initialize the game
    Game game;

    // Initialize the renderer
    threepp::GLRenderer renderer(canvas.size());
    renderer.setClearColor(threepp::Color::blue);

    // Create a perspective camera
    auto camera = threepp::PerspectiveCamera::create(65, canvas.aspect(), 0.1f, 1000);
    camera->position.set(110, 0, 500);

    // Create a 3D scene
    auto scene = threepp::Scene::create();

    // Set the target frame time for 60 fps
    const double targetFrameTime = 1.0 / 60.0; // Target time for 60 fps (in seconds)
    threepp::Clock clock;

    // Create an instance of TimeUtils
    TimeUtils timeUtils;

    // MyKeyListener initialization and registration
    MyKeyListener kl{game};
    canvas.addKeyListener(&kl);

    double previousTime = clock.getElapsedTime();
    double lag = 0.0;

    // Create an instance of the Block class
    Block block;

    // Start the rendering loop
    canvas.animate([&] {
        double currentTime = clock.getElapsedTime();
        double elapsed = currentTime - previousTime;
        previousTime = currentTime;
        lag += elapsed;

        // Process game logic in a separate update function
        while (lag >= targetFrameTime) {
            lag -= targetFrameTime;
            float deltaTime = timeUtils.calculateDeltaTime();

            game.Update(*scene, deltaTime);
            game.Draw(*scene);

            // Redraw locked blocks every frame
            if (!game.gameOver) {
                game.RedrawLockedBlocks(*scene);
            }

            // Check for game over
            if (game.gameOver) {
                auto &handle3 = textRenderer.createHandle("GAME OVER!");
                handle3.setPosition(canvas.size().width - 300, +610);
                handle3.color = Color::white;
                handle3.scale = 3;
            }

            // Update the "Score" text handle
            scoreHandle.setText("Score: " + std::to_string(game.score));


            // Draw the white box continuously
            Position whiteBoxPosition = Position(7, 15);
            float customWidth = 150.0f;  // Replace with your desired width
            float customHeight = 90.0f; // Replace with your desired height
            float customDepth = 2.0f;   // Replace with your desired depth
            block.CreateWhiteBox(*scene, whiteBoxPosition, customWidth, customHeight, customDepth);

        }

        // Render the scene
        renderer.render(*scene, *camera);

        renderer.resetState();
        textRenderer.render();

        // Sleep to control the frame rate
        auto frameRenderTime = clock.getElapsedTime() - currentTime;
        auto sleepDuration = std::chrono::milliseconds(static_cast<int>((targetFrameTime - frameRenderTime) * 1000));
        std::this_thread::sleep_for(sleepDuration);
    });
}
