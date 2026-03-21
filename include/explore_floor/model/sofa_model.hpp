#pragma once
#include <glm/glm.hpp>
#include <vector>

/**
 * SOFA MODEL
 * Purpose: Contains the data for a single sofa.
 */
struct Sofa {
    glm::vec3 position;
    float rotation;
    glm::vec4 color;
};

/**
 * SOFA COLLECTION MODEL
 * Purpose: Manages multiple sofas in the scene.
 */
struct SofaModel {
    std::vector<Sofa> sofas;

    void init() {
        // Sofa 1 (facing entrance)
        sofas.push_back({glm::vec3(0, 0, -6), 0, glm::vec4(0.5f, 0.25f, 0.15f, 1.0f)});
        // Sofa 2 (facing Sofa 1)
        sofas.push_back({glm::vec3(0, 0, 4), glm::radians(180.0f), glm::vec4(0.5f, 0.25f, 0.15f, 1.0f)});
    }
};
