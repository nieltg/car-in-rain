#include <SDL2/SDL.h>
#include <iostream>
#include <memory>


// Utilities

void log_func_error(std::string _func, std::string _reason) {
  std::cerr << "Error in: " << _func << std::endl;
  std::cerr << "  Reason: " << _reason << std::endl;
}


// Main program

SDL_Window* window;
SDL_GLContext context;


void event_loop(void) {
  while (true) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          return;

        case SDL_WINDOWEVENT:
          switch (event.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
              // resize(event.window.data1, event.window.data2);
              break;
          }
          break;
      }
    }

    // render();
    SDL_GL_SwapWindow(window);
  }
}


int main(int argc, char** argv) {

  // Initialize SDL library

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    log_func_error("SDL_Init", SDL_GetError());
    return EXIT_FAILURE;
  }

  // Create an application window with the following settings:
  window = SDL_CreateWindow(
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

  context = SDL_GL_CreateContext(window);
  if (context == nullptr) {
    log_func_error("SDL_GL_CreateContext", SDL_GetError());
    return EXIT_FAILURE;
  }

  if (SDL_GL_SetSwapInterval(1) < 0) {
    log_func_error("SDL_GL_SetSwapInterval", SDL_GetError());
    std::cerr << "warning: Unable to use VSync. Performance will suffers."
              << std::endl;
  }

  // Initialize program.

  // init();
  // resize(640, 480);

  event_loop();

  // Remove everything.

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);

  return EXIT_SUCCESS;
}
