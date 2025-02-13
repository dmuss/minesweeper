#ifndef GAME_HPP_
#define GAME_HPP_

#include <string>

#include "input/mouse_manager.hpp"
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

  static constexpr float DEFAULT_FONT_PT_SIZE_ = 40;
  SDL3::FontUPtr font_;

  bool running_;
  uint64_t currFrameMS_;
  uint64_t lastFrameMS_;
  uint64_t deltaMS_;
  GameDifficulty difficulty_;

  MouseManager mouse_;
  SceneManager sceneManager_;

 public:
  Game();

  /// Handles mouse events.
  void HandleMouseEvent();

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
  void RenderSprite(SDL_FRect srcRect, SDL_FRect destRect);

  /// Renders a text string.
  ///
  /// \param str The string to render.
  /// \param rect The rectangle to center the text within.
  /// \param color The requested color of the text.
  void RenderText(
      const std::string& str, SDL_FRect rect,
      SDL_Color color = {.r = 0x0, .g = 0x0, .b = 0x0, .a = SDL_ALPHA_OPAQUE},
      float ptSize = DEFAULT_FONT_PT_SIZE_);

  /// Sets the color modification value for rendering sprites.
  ///
  /// \param color The color to modify sprite rendering with.
  void SetTextureColorMod(SDL_Color color);
};

#endif
