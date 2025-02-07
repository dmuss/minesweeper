#include <cmath>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>

struct Context {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_AppResult result = SDL_APP_CONTINUE;
};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "Failed to initialize SDL! %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_Window *window = SDL_CreateWindow("minesweeper", 400, 400, 0);
  if (!window) {
    SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "Failed to create SDL window! %s",
                    SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) {
    SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "Failed to create SDL renderer! %s",
                    SDL_GetError());
    return SDL_APP_FAILURE;
  }

  *appstate = new Context{
      .window = window,
      .renderer = renderer,
  };

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  auto *app = static_cast<Context *>(appstate);

  if (event->type == SDL_EVENT_QUIT) {
    app->result = SDL_APP_SUCCESS;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  auto *app = static_cast<Context *>(appstate);

  auto time = SDL_GetTicks() / 1000.0f;
  auto r = (std::sin(time) + 1) / 2.0 * 255;
  auto g = (std::sin(time / 2) + 1) / 2.0 * 255;
  auto b = (std::sin(time * 2) + 1) / 2.0 * 255;

  SDL_SetRenderDrawColor(app->renderer, r, g, b, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(app->renderer);
  SDL_RenderPresent(app->renderer);

  return app->result;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  auto *app = static_cast<Context *>(appstate);
  SDL_DestroyWindow(app->window);
  delete app;

  SDL_Quit();
}
