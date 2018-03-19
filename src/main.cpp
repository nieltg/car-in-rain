#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <iostream>
#include <memory>

#include "gl.h"

int main (int argc, char** argv) try {
    // Initialize SDL library
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Create an application window with the following settings:
    SDL2pp::Window window(
        "OpenGL SDL2 Demo", // Window title.
        SDL_WINDOWPOS_UNDEFINED,// Initial x position.
        SDL_WINDOWPOS_UNDEFINED,// Initial y position.
        640,// Width, in pixels.
        480,// Height, in pixels.
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    // Create OpenGL context.
    class GLContext {
        SDL_GLContext context;

        public:
            GLContext (const SDL2pp::Window& _window) {
                context = SDL_GL_CreateContext(_window.Get());

                if (context == nullptr)
                    throw SDL2pp::Exception("SDL_GL_CreateContext");
            }

            ~GLContext (void) {
                SDL_GL_DeleteContext(context);
            }
    } context(window);

    int status = SDL_GL_SetSwapInterval(1);
    if (status < 0) {
        std::cerr << "warning: Unable to use VSync: " << SDL_GetError()
        << std::endl;
    }

    // Initialize program.
    init();
    resize(window.GetWidth(), window.GetHeight());

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    return 0;

                case SDL_WINDOWEVENT:
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        resize(event.window.data1, event.window.data2);
                    break;
                }
                break;
            }
        }

        render();
        SDL_GL_SwapWindow(window.Get());
    }

} catch (const SDL2pp::Exception& e) {
    std::cerr << "Error in: " << e.GetSDLFunction() << std::endl;
    std::cerr << "Reason: " << e.GetSDLError() << std::endl;
} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
}
