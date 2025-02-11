#ifndef GAME_HPP_
#define GAME_HPP_

#include "scenes/scene_manager.hpp"
#include "sdl_helpers.hpp"

enum class GameDifficulty { Easy, Medium, Hard };

class Game {
 private:
  static bool isInit_;

  static constexpr uint8_t TARGET_FPS_ = 30;
  static constexpr uint8_t TARGET_FRAME_TIME_MS_ = 1000 / TARGET_FPS_;

  SDL3::WindowUPtr window_;
  SDL3::RendererUPtr renderer_;
  SDL3::TextureUPtr spritesheet_;

  bool running_;
  uint64_t currFrameMS_;
  uint64_t lastFrameMS_;
  uint64_t deltaMS_;
  GameDifficulty difficulty_;

  SceneManager sceneManager_;

 public:
  Game();

  /// Handles the provided SDL mouse button event.
  ///
  /// \param mouseEvent The current mouse button event to handle.
  void HandleMouseButtonEvent(SDL_Event* mouseEvent);

  /// Advances the game a single tick, including any updates and rendering.
  SDL_AppResult Tick();

  /// Returns the currently set difficulty.
  GameDifficulty Difficulty() const;

  /// Start a game with the provided difficulty.
  ///
  /// \param difficulty The requested difficulty to start the game with.
  void StartGame(GameDifficulty difficulty);

  /// Return to the main menu scene.
  void GoToMenu();

  /// Quits the game.
  void Quit();

  /// Sets the game's current window to the requested size.
  ///
  /// \param requestedSize The requested window dimensions.
  void SetWindowSize(SDL_Point requestedSize);

  /// Renders a sprite from the spritesheet at the provided destination.
  ///
  /// \param srcRect The source rectangle for the sprite to render.
  /// \param destRect The location on the window to render the sprite.
  void RenderSprite(const SDL_FRect& srcRect, const SDL_FRect& destRect);

  /// Sets the color modification value for rendering sprites.
  ///
  /// \param color The color to modify sprite rendering with.
  void SetTextureColorMod(SDL_Color color);
};

#endif
