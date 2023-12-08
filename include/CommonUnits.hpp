

#ifndef EKSAMEN_2023_COMMONUNITS_HPP
#define EKSAMEN_2023_COMMONUNITS_HPP

#include "map"
#include "Position.hpp"
#include "colors.hpp"


class CommonUtils {
public:
    static void SetMeshPosition(const std::shared_ptr<threepp::Mesh> &mesh, float x, float y, float z) {
        mesh->position.x = x;
        mesh->position.y = y;
        mesh->position.z = z;
    }

    static void AddMeshToScene(threepp::Scene &scene, const std::shared_ptr<threepp::Mesh> &mesh) {
        scene.add(mesh);
    }

    static std::pair<float, float> CalculateCenter(float width, float height) {
        float centerX = -width / 2.0;
        float centerY = height / 2.0;
        return {centerX, centerY};
    }


};


#endif //EKSAMEN_2023_COMMONUNITS_HPP
