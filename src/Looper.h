#include <map>
#include <functional>

#include <SDL2/SDL.h>


class Looper {
public:
  using Hook = std::function<void (const SDL_Event&)>;
  using Token = std::multimap<uint32_t, Hook>::iterator;

  Token add (uint32_t _event_type, Hook _hook);
  void remove (Token _delete_token);

  class QuitException : std::exception {
  };

  void run (void) const;

private:
  std::multimap<uint32_t, Hook> hooks;
};
