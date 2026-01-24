#pragma once
#include "game_logic/board.hpp"
#include "game_logic/snake.hpp"
#include "game_logic/food.hpp"
#include "graphics_render/model.hpp"
#include "graphics_render/input.hpp"

// Forward declare Pipeline (we only use it as a reference parameter)
struct Pipeline;

// SnakeGame: manages all snake game logic and rendering
struct SnakeGame {
    Board board;
    Snake snake;
    Food food;
    Model cell_model;  // reused to draw all cells
    
    void init() {
        cell_model.init();
        snake.init(board.width / 4, board.height / 2);
        food.spawn(board, snake);
    }
    
    void destroy() {
        cell_model.destroy();
    }
    
    // Handle keyboard input
    void handle_input() {
        if (Keys::pressed(SDLK_W) || Keys::pressed(SDLK_UP))    snake.set_direction(Snake::Direction::UP);
        if (Keys::pressed(SDLK_S) || Keys::pressed(SDLK_DOWN))  snake.set_direction(Snake::Direction::DOWN);
        if (Keys::pressed(SDLK_A) || Keys::pressed(SDLK_LEFT))  snake.set_direction(Snake::Direction::LEFT);
        if (Keys::pressed(SDLK_D) || Keys::pressed(SDLK_RIGHT)) snake.set_direction(Snake::Direction::RIGHT);
        
        if (Keys::pressed(SDLK_R)) {
            snake.init(board.width / 4, board.height / 2);
            food.spawn(board, snake);
        }
    }
    
    // Update game state
    void update(float delta) {
        snake.update(delta, board);
        
        if (food.check_eaten(snake)) {
            snake.grow();
            food.spawn(board, snake);
        }
    }
    
    // Draw everything (pipeline is passed from engine, colors set via pipeline)
    void draw(Pipeline& pipeline) {
        float cell_scale = board.cell_size * 0.9f;
        
        // 1. Draw board
        for (int x = 0; x < board.width; x++) {
            for (int y = 0; y < board.height; y++) {
                glm::vec3 pos = board.grid_to_world(x, y);
                cell_model.set_position(pos.x, pos.y);
                cell_model.set_scale(cell_scale);
                
                bool dark = (x + y) % 2 == 0;
                pipeline.set_color(dark ? glm::vec4(0.15f, 0.15f, 0.2f, 1.0f) 
                                        : glm::vec4(0.2f, 0.2f, 0.25f, 1.0f));
                cell_model.draw();
            }
        }
        
        // 2. Draw snake
        int i = 0;
        for (const auto& seg : snake.body) {
            glm::vec3 pos = board.grid_to_world(seg.x, seg.y);
            cell_model.set_position(pos.x, pos.y);
            cell_model.set_scale(cell_scale);
            
            if (i == 0) {
                pipeline.set_color(snake.alive ? glm::vec4(0.2f, 0.9f, 0.3f, 1.0f) 
                                               : glm::vec4(0.7f, 0.2f, 0.2f, 1.0f));
            } else {
                pipeline.set_color(snake.alive ? glm::vec4(0.1f, 0.7f, 0.2f, 1.0f) 
                                               : glm::vec4(0.5f, 0.15f, 0.15f, 1.0f));
            }
            cell_model.draw();
            i++;
        }
        
        // 3. Draw food
        glm::vec3 food_pos = board.grid_to_world(food.position.x, food.position.y);
        cell_model.set_position(food_pos.x, food_pos.y);
        cell_model.set_scale(cell_scale * 0.8f);
        pipeline.set_color(glm::vec4(0.9f, 0.2f, 0.2f, 1.0f));
        cell_model.draw();
    }
};
