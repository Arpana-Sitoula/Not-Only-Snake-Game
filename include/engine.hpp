#pragma once
#include "graphics_render/time.hpp"
#include "graphics_render/input.hpp"
#include "graphics_render/window.hpp"
#include "graphics_render/camera.hpp"
#include "graphics_render/pipeline.hpp"
#include "snake_game.hpp"

// Engine: the main game loop
// Handles window, camera, pipeline, and runs the snake game
struct Engine {
    // Core systems
    Time time;
    Window window;
    Camera camera;
    Pipeline pipeline;
    
    // The game
    SnakeGame game;
    
    Engine() {
        time.init();
        window.init(1920, 1080);
        pipeline.init("default.vert", "vertcols.frag");
        game.init();
        
        // Fixed camera looking at the board
        camera._position = glm::vec3(0, 0, 10);
        camera._rotation = glm::vec3(0, 0, 0);
    }
    
    ~Engine() {
        game.destroy();
        pipeline.destroy();
        window.destroy();
    }

    auto handle_sdl_event(SDL_Event& event) -> SDL_AppResult {
        if (event.type == SDL_EventType::SDL_EVENT_QUIT) {
            return SDL_AppResult::SDL_APP_SUCCESS;
        }
        Input::register_event(event);
        return SDL_AppResult::SDL_APP_CONTINUE;
    }
    
    auto handle_sdl_frame() -> SDL_AppResult {
        time.update();
        
        // Clear screen
        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Disable depth testing for 2D game (draw order matters instead)
        glDisable(GL_DEPTH_TEST);
        
        // Game logic
        game.handle_input();
        game.update(time._delta);
        
        // Render
        pipeline.bind();
        camera.bind();
        game.draw(pipeline);
        
        // Present
        SDL_GL_SwapWindow(window._window_p);
        Input::flush();
        
        return SDL_AppResult::SDL_APP_CONTINUE;
    }
};