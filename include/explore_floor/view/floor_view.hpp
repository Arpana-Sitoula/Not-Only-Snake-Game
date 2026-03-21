#pragma once
#include "base_floor_view.hpp"
#include "sofa_view.hpp"
#include "wall_view.hpp"
#include "carpet_view.hpp"
#include "../model/base_floor_model.hpp"
#include "../model/sofa_model.hpp"
#include "../model/wall_model.hpp"
#include "../model/carpet_model.hpp"

/**
 * FLOOR VIEW (Composite)
 * Purpose: Orchestrates the drawing of all environment components.
 */
struct FloorView {
    BaseFloorView base_floor_view;
    SofaView sofa_view;
    WallView wall_view;
    CarpetView carpet_view;

    void draw(BaseFloorModel& base_floor, 
              SofaModel& sofa_model, 
              WallModel& wall_model, 
              CarpetModel& carpet_model, 
              Pipeline& pipeline, 
              Model& test_box) {
        
        // 1. Draw Base Floor
        base_floor_view.draw(base_floor, pipeline, test_box);

        // 2. Draw Carpets
        carpet_view.draw(carpet_model, pipeline, test_box);

        // 3. Draw Walls
        wall_view.draw(wall_model, pipeline, test_box);

        // 4. Draw Sofas
        sofa_view.draw(sofa_model, pipeline, test_box);
    }
};
