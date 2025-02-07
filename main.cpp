#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#pragma GCC diagnostic pop

#include "game.hpp"

SDL_AppResult SDL_AppInit(void** appstate, [[maybe_unused]] int argc,
                          [[maybe_unused]] char* argv[]) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "Failed to initialize SDL! %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  *appstate = new Game();

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
  auto* app = static_cast<Game*>(appstate);

  switch (event->type) {
    case SDL_EVENT_QUIT: {
      return SDL_APP_SUCCESS;
    }
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP: {
      app->HandleMouseButtonEvent(event);
      break;
    }
    default:
      break;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
  return static_cast<Game*>(appstate)->Tick();
}

void SDL_AppQuit(void* appstate, [[maybe_unused]] SDL_AppResult result) {
  auto* app = static_cast<Game*>(appstate);
  delete app;

  SDL_Quit();
}
