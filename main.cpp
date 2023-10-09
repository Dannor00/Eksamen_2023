
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

namespace {

    auto createBox(const Vector3& pos, const Color& color) {
        auto geometry = BoxGeometry::create();
        auto material = MeshBasicMaterial::create();
        material->color.copy(color);
        auto mesh = Mesh::create(geometry, material);
        mesh->position.copy(pos);

        return mesh;
    }

}// namespace

int main() {

    Canvas canvas("Tetris", {{"aa", 4}});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::aliceblue);

    auto camera = PerspectiveCamera::create();
    camera->position.z = 5;

    OrbitControls controls{*camera, canvas};

    auto scene = Scene::create();

    auto group = Group::create();
    group->add(createBox({-1, 0, 0}, Color::green));
    group->add(createBox({1, 0, 0}, Color::blue));
    scene->add(group);

    renderer.enableTextRendering();
    int textYOffset = 30;
    auto& textHandle = renderer.textHandle("Level 1");
    textHandle.setPosition(0, canvas.size().height - textYOffset);
    textHandle.scale = 2;


    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.aspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
        textHandle.setPosition(0, size.height - textYOffset);
    });

    Clock clock;
    float rotationSpeed = 1;
    canvas.animate([&] {
        auto dt = clock.getDelta();
        group->rotation.y += rotationSpeed * dt;

        renderer.render(*scene, *camera);
    });
}
