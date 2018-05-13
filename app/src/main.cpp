#include <iostream>
#include <memory>

#include <SDL2/SDL.h>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include <globjects/globjects.h>

#include "Scene.h"


// Utilities

void log_func_error(std::string _func, std::string _reason) {
  std::cerr << "Error in: " << _func << std::endl;
  std::cerr << "  Reason: " << _reason << std::endl;
}


// Main program

int main(int argc, char** argv) {

  // Initialize SDL library

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    log_func_error("SDL_Init", SDL_GetError());
    return EXIT_FAILURE;
  }

  // Create an application window with the following settings:
  SDL_Window* window = SDL_CreateWindow(
    "OpenGL SDL2 Demo",       // Window title.
    SDL_WINDOWPOS_UNDEFINED,  // Initial x position.
    SDL_WINDOWPOS_UNDEFINED,  // Initial y position.
    640,                      // Width, in pixels.
    480,                      // Height, in pixels.
    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (window == nullptr) {
    log_func_error("SDL_CreateWindow", SDL_GetError());
    return EXIT_FAILURE;
  }

  // Initialize OpenGL context.

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  SDL_GLContext context = SDL_GL_CreateContext(window);
  if (context == nullptr) {
    log_func_error("SDL_GL_CreateContext", SDL_GetError());
    return EXIT_FAILURE;
  }

  // Initialize GLBinding.
  glbinding::Binding::initialize(SDL_GL_GetProcAddress);
  globjects::init();

  // Initialize VSync.

  if (SDL_GL_SetSwapInterval(1) < 0) {
    log_func_error("SDL_GL_SetSwapInterval", SDL_GetError());
    std::cerr << "warning: Unable to use VSync. Performance will suffers."
              << std::endl;
  }

  // Begin program.

  {
    Scene scene;
    SDL_GetWindowSize(window, &scene.width, &scene.height);

    // Event loop.

    bool is_running = true;

    while (is_running) {
      SDL_Event event;

      while (SDL_PollEvent(&event)) {
        switch (event.type) {
          case SDL_QUIT:
            is_running = false;
            break;

          case SDL_WINDOWEVENT:
            switch (event.window.event) {
              case SDL_WINDOWEVENT_RESIZED:
                scene.resize(event.window.data1, event.window.data2);
                break;
            }
            break;
        }
      }

      scene.draw();
      SDL_GL_SwapWindow(window);
    }
  }

  // Remove everything.
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);

  return EXIT_SUCCESS;
}
