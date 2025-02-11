#ifndef GAME_HPP_
#define GAME_HPP_

#include "scenes/game_scene.hpp"
#include "sdl_helpers.hpp"

class Game {
 private:
  static bool isInit_;

  static constexpr uint8_t TARGET_FPS_ = 30;
  static constexpr uint8_t TARGET_FRAME_TIME_MS_ = 1000 / TARGET_FPS_;

  bool running_;
  uint64_t currFrameMS_;
  uint64_t lastFrameMS_;
  uint64_t deltaMS_;

  // TODO: TEMP
  GameScene gameScene_;

  SDL3::WindowUPtr window_;
  SDL3::RendererUPtr renderer_;
  SDL3::TextureUPtr spritesheet_;

 public:
  Game();

  /// Handles the provided SDL mouse button event.
  ///
  /// \param mouseEvent The current mouse button event to handle.
  void HandleMouseButtonEvent(SDL_Event* mouseEvent);

  /// Advances the game a single tick, including any updates and rendering.
  SDL_AppResult Tick();

  /// Sets the game's current window to the requested size.
  ///
  /// \param requestedSize The requested window dimensions.
  void SetWindowSize(SDL_Point requestedSize);

  /// Renders a sprite from the spritesheet at the provided destination.
  ///
  /// \param srcRect The source rectangle for the sprite to render.
  /// \param destRect The location on the window to render the sprite.
  void RenderSprite(const SDL_FRect& srcRect, const SDL_FRect& destRect);
};

#endif
