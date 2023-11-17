#include "threepp/threepp.hpp"
#include "thread"
#include "include/game.hpp"
#include "include/keyobserver.hpp"

using namespace threepp;

int main() {
    // Create a canvas for rendering
    Canvas canvas("Tetris", {{"aa", 4}});
    canvas.setSize({500, 500});

    // Initialize the renderer
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::blue);

    // Create a perspective camera
    auto camera = PerspectiveCamera::create(75, canvas.aspect(), 0.1f, 1000);
    camera->position.set(0, 0, 500);

    // Create a 3D scene
    auto scene = Scene::create();



    // Initialize the game
    Game game = Game();

    // Set the target frame time for 60 fps
    const double targetFrameTime = 1.0 / 60.0; // Target time for 60 fps (in seconds)
    Clock clock;


    MyKeyListener kl{clock.elapsedTime};
    canvas.addKeyListener(&kl);

    double previousTime = clock.getElapsedTime();
    double lag = 0.0;

    // Start the rendering loop
    canvas.animate([&] {
        double currentTime = clock.getElapsedTime();
        double elapsed = currentTime - previousTime;
        previousTime = currentTime;
        lag += elapsed;

        // Process game logic and render in the same loop
        while (lag >= targetFrameTime) {
            lag -= targetFrameTime;

            // Update the game state
            // (You can add game logic directly here if you don't want a separate Update function)
            // For example, game.Move(), game.CheckCollision(), etc.

            // Draw the updated game state
            game.Draw(*scene);
        }

        // Render the scene
        renderer.render(*scene, *camera);

        // Sleep to limit the frame rate to 60 fps
        auto frameRenderTime = clock.getElapsedTime() - currentTime;
        auto sleepDuration = std::chrono::milliseconds(static_cast<int>((targetFrameTime - frameRenderTime) * 1000));
        std::this_thread::sleep_for(sleepDuration);


        // Continue rendering loop
    });
}