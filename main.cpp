#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"
#include "thread"
#include "Tetrominos/Block/blocks/blocks.cpp"
#include "grid.h"

using namespace threepp;


int main() {

    Canvas canvas("Tetris", {{"aa", 4}});
    canvas.setSize({300, 600});

    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::blue);
    auto camera = PerspectiveCamera::create(75, canvas.aspect(),0.1f, 1000);
    camera->position.set(0, 0, 500);

    auto scene = Scene::create();
    OrbitControls controls(*camera, canvas);

    Grid grid = Grid();
    grid.Print();

    TBlock block = TBlock();
    block.Draw(scene.get());


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
        grid.Draw(scene.get());


        renderer.render(*scene, *camera);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));

        /// til hær
    });
}