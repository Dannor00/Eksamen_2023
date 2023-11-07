#include "threepp/threepp.hpp"
#include "thread"
#include "game/game.h"

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

    // Initialize orbit controls for camera manipulation
    OrbitControls controls(*camera, canvas);

    // Initialize the game
    Game game = Game();

    // Set the target frame time for 60 fps
    const double targetFrameTime = 1.0 / 60.0; // Target time for 60 fps (in seconds)
    Clock clock;

    double previousTime = clock.getElapsedTime();
    double lag = 0.0;

    // Start the rendering loop
    canvas.animate([&] {
        double currentTime = clock.getElapsedTime();
        double elapsed = currentTime - previousTime;
        previousTime = currentTime;
        lag += elapsed;

        // Process game logic in fixed time steps
        while (lag >= targetFrameTime) {
            lag -= targetFrameTime;
            game.Draw(scene.get()); // Update the game state
        }

        // Render the scene
        renderer.render(*scene, *camera);

        // Sleep to limit the frame rate to 60 fps
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));

        // Continue rendering loop
    });
}
