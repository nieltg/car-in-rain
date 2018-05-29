#include <iostream>
#include <memory>

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include <globjects/globjects.h>

#include "Mesh.h"
#include "Rain.h"
#include "Exhaust.h"

// How many frames time values to keep
// The higher the value the smoother the result is...
// Don't make it 0 or less :)
#define FRAME_VALUES 10

// An array to store frame times:
Uint32 frametimes[FRAME_VALUES];

// Last calculated SDL_GetTicks
Uint32 frametimelast;

// total frames rendered
Uint32 framecount;

// the value you want
float framespersecond;

// This function gets called once on startup.
void fpsinit() {

        // Set all frame times to 0ms.
        memset(frametimes, 0, sizeof(frametimes));
        framecount = 0;
        framespersecond = 0;
        frametimelast = SDL_GetTicks();

}

void fpsthink() {

        Uint32 frametimesindex;
        Uint32 getticks;
        Uint32 count;
        Uint32 i;

        // frametimesindex is the position in the array. It ranges from 0 to FRAME_VALUES.
        // This value rotates back to 0 after it hits FRAME_VALUES.
        frametimesindex = framecount % FRAME_VALUES;

        // store the current time
        getticks = SDL_GetTicks();

        // save the frame time value
        frametimes[frametimesindex] = getticks - frametimelast;

        // save the last frame time for the next fpsthink
        frametimelast = getticks;

        // increment the frame count
        framecount++;

        // Work out the current framerate

        // The code below could be moved into another function if you don't need the value every frame.

        // I've included a test to see if the whole array has been written to or not. This will stop
        // strange values on the first few (FRAME_VALUES) frames.
        if (framecount < FRAME_VALUES) {

                count = framecount;

        } else {

                count = FRAME_VALUES;

        }

        // add up all the values and divide to get the average frame time.
        framespersecond = 0;
        for (i = 0; i < count; i++) {

                framespersecond += frametimes[i];

        }

        framespersecond /= count;

        // now to make it an actual frames per second value...
        framespersecond = 1000.f / framespersecond;

}

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
    "IF3260 Grafika Komputer",    // Window title.
    SDL_WINDOWPOS_UNDEFINED,      // Initial x position.
    SDL_WINDOWPOS_UNDEFINED,      // Initial y position.
    640,                          // Width, in pixels.
    480,                          // Height, in pixels.
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
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    fpsinit();

    Mesh mesh;
    Rain rain;
    Exhaust smoke;

    gl::glEnable(gl::GL_BLEND);
    gl::glEnable(gl::GL_DEPTH_TEST);
    gl::glBlendFunc(gl::GL_SRC_ALPHA, gl::GL_ONE_MINUS_SRC_ALPHA);

    // Event loop.

    bool is_running = true;
    float yaw = 0;
    float pitch = 0;

    Uint32 fps_lasttime = SDL_GetTicks(); //the last recorded time.
    Uint32 fps_current; //the current FPS.
    Uint32 fps_frames = 0; //frames passed since the last recorded fps.

    // you would initalise these in a main method, really.

    bool is_anim = false;

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
                width = event.window.data1;
                height = event.window.data2;
                gl::glViewport(0, 0, width, height);
                break;
            }
            break;

          case SDL_MOUSEMOTION:
            if (event.motion.state & SDL_BUTTON_LMASK) {
              yaw += (float)event.motion.xrel;
              pitch += (float)event.motion.yrel;
            }
            break;

          case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_a) {
              is_anim = !is_anim;
            }
            break;
        }
      }

      // Draw.
      gl::glClearColor(0.2, 0.2, 0.2, 1.0);
      gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);

      glm::mat4 view = glm::lookAt(
        glm::vec3(0.0, 2.0, 0.0),
        glm::vec3(0.0, 0.0, -4.0),
        glm::vec3(0.0, 1.0, 0.0));
      view = glm::translate(view, glm::vec3(0.0, 0.0, -4.0))
        * glm::rotate(glm::mat4(1.0f), pitch*0.05f, glm::vec3(1, 0, 0))
        * glm::rotate(glm::mat4(1.0f), yaw*0.05f, glm::vec3(0, 1, 0));

      float angle = SDL_GetTicks() / 1000.0 * glm::radians(15.0);
      glm::mat4 anim =
        glm::rotate(glm::mat4(1.0f), angle*3.0f, glm::vec3(1, 0, 0)) *  // X axis
        glm::rotate(glm::mat4(1.0f), angle*2.0f, glm::vec3(0, 1, 0)) *  // Y axis
        glm::rotate(glm::mat4(1.0f), angle*4.0f, glm::vec3(0, 0, 1));   // Z axis

      if (is_anim) {
        view *= anim;
      }

      glm::mat4 projection = glm::perspective(
        45.0f, 1.0f * width / height, 0.1f, 10.0f);

      mesh.draw(view, projection);

      gl::glDepthMask(gl::GL_FALSE);
      rain.draw(view, projection);
      smoke.draw(view, projection);
      gl::glDepthMask(gl::GL_TRUE);

      SDL_GL_SwapWindow(window);

      fpsthink();
      std::cout << framespersecond << " fps" << std::endl;
    }
  }

  // Remove everything.
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);

  return EXIT_SUCCESS;
}
