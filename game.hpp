#ifndef GAME_HPP_
#define GAME_HPP_

#include <string>

#include "input/mouse_manager.hpp"
#include "scenes/scene_manager.hpp"
#include "constants.hpp"
#include "sdl_helpers.hpp"

enum class GameDifficulty { Easy, Medium, Hard };

class Game {
 private:
  static bool isInit_;

  SDL3::WindowUPtr window_;
  SDL3::RendererUPtr renderer_;
  SDL3::TextureUPtr spritesheet_;

  static constexpr float DEFAULT_FONT_PT_SIZE_ = 40;
  SDL3::FontUPtr font_;
  std::unordered_map<std::string, SDL3::TextureUPtr> textTextures_;

  /// Create a texture for requested string.
  ///
  /// \param str The text to be rendered.
  /// \param color The color to render the text in.
  void createTextTexture_(const std::string& str, SDL_Color color);

  /// Get the destination rectangle that centers the provided string in the
  /// containing rectangle.
  ///
  /// \param str The text to be rendered.
  /// \param containinRect The rectangle to center the text within.
  /// \return The rectangle of the centered text.
  SDL_FRect getCenteredTextRect_(const std::string& str,
                                 SDL_FRect containingRect);

  static constexpr uint8_t TARGET_FPS_ = 30;
  static constexpr uint8_t TARGET_FRAME_TIME_MS_ = 1000 / TARGET_FPS_;
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
  void DrawSprite(SDL_FRect srcRect, SDL_FRect destRect);

  /// Renders a text string.
  ///
  /// \param str The string to render.
  /// \param rect The rectangle to center the text within.
  /// \param color The requested color of the text.
  /// \param alpha The alpha value to render the text at.
  /// \param ptSize The point size to render the text at.
  void DrawText(const std::string& str, SDL_FRect rect,
                SDL_Color color = Colors::Black,
                float ptSize = DEFAULT_FONT_PT_SIZE_);

  /// Renders a text string with alpha blending.
  ///
  /// \param str The string to render.
  /// \param rect The rectangle to center the text within.
  /// \param alpha The alpha value to blend the texture with.
  /// \param color The requested color of the text.
  /// \param alpha The alpha value to render the text at.
  /// \param ptSize The point size to render the text at.
  void DrawTextWithAlpha(const std::string& str, SDL_FRect rect, uint8_t alpha,
                         SDL_Color color = Colors::Black,
                         float ptSize = DEFAULT_FONT_PT_SIZE_);

  /// Sets the color modification value for rendering sprites.
  ///
  /// \param color The color to modify sprite rendering with.
  void SetSpriteTextureColorMod(SDL_Color color);
};

#endif
