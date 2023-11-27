#include "threepp/threepp.hpp"
#include "thread"
#include "include/game.hpp"
#include "include/Keylistner.hpp"
#include "include/CalculateTime.hpp"

int main() {
    // Create a canvas for rendering
    threepp::Canvas canvas("Tetris", {{"aa", 4}});
    canvas.setSize({1000, 900});

    // Initialize the renderer
    threepp::GLRenderer renderer(canvas.size());
    renderer.setClearColor(threepp::Color::blue);

    // Create a perspective camera
    auto camera = threepp::PerspectiveCamera::create(75, canvas.aspect(), 0.1f, 1000);
    camera->position.set(0, 0, 500);

    // Create a 3D scene
    auto scene = threepp::Scene::create();

    // Initialize the game
    Game game = Game();

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

            // Update the game state
            game.Update(*scene, deltaTime);

            // Draw the game scene
            game.Draw(*scene);
        }

        // Render the scene
        renderer.render(*scene,*camera);

        // Sleep to control the frame rate
        auto frameRenderTime = clock.getElapsedTime() - currentTime;
        auto sleepDuration = std::chrono::milliseconds(static_cast<int>((targetFrameTime - frameRenderTime) * 1000));
        std::this_thread::sleep_for(sleepDuration);
    });

    return 0;
}

