#include "Looper.h"


Looper::Token Looper::add (uint32_t _event_type, Looper::Hook _hook) {
  return hooks.insert(std::make_pair(_event_type, _hook));
}

void Looper::remove (Looper::Token _delete_token) {
  hooks.erase(_delete_token);
}

void Looper::run (void) const try {
  while (true) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      auto range = hooks.equal_range(event.type);

      for (auto it = range.first; it != range.second; ++it)
        it->second(event);
    }
  }
} catch (Looper::QuitException _e) {
}
