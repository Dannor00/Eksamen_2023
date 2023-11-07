#include "threepp/threepp.hpp"
#include "thread"
#include "game/game.h"

using namespace threepp;


int main() {

    Canvas canvas("Tetris", {{"aa", 4}});
    canvas.setSize({500, 500});

    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::blue);
    auto camera = PerspectiveCamera::create(75, canvas.aspect(),0.1f, 1000);
    camera->position.set(0, 0, 500);

    auto scene = Scene::create();
    OrbitControls controls(*camera, canvas);

    Game game = Game();




    /// Denne delen av koden er modifisert av chatgpt for å sette maksimum fps til 60
    const double targetFrameTime = 1.0 / 60.0; // Target time for 60 fps (in seconds)
    Clock clock;

    double previousTime = clock.getElapsedTime();
    double lag = 0.0;

    canvas.animate([&] {
        double currentTime = clock.getElapsedTime();
        double elapsed = currentTime - previousTime;
        previousTime = currentTime;
        lag += elapsed;

        while (lag >= targetFrameTime) {
            lag -= targetFrameTime;
        }
       game.Draw(scene.get());


        renderer.render(*scene, *camera);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));

        /// til hær
    });
}