#pragma once
#include "mesh.hpp"
#include "transform.hpp"

// A Model combines: mesh (shape) + transform (position/scale)
// Simple building block for drawing - does NOT know about pipeline/colors
struct Model {
    Mesh mesh;
    Transform transform;
    
    void init() {
        mesh.init();
    }
    
    void destroy() {
        mesh.destroy();
    }
    
    // Set position in world space
    void set_position(float x, float y) {
        transform._position = glm::vec3(x, y, 0);
    }
    
    // Set size (uniform scale)
    void set_scale(float size) {
        transform._scale = glm::vec3(size, size, 1);
    }
    
    // Draw this model (caller must set color via pipeline first!)
    void draw() {
        transform.bind();
        mesh.bind();
        mesh.draw();
    }
};
