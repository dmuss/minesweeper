#ifndef SCENES_MENU_SCENE_HPP_
#define SCENES_MENU_SCENE_HPP_

#include <array>
#include <string>

#include "scene_interface.hpp"

class MenuScene final : public SceneInterface {
 private:
  static constexpr SDL_Point WINDOW_SIZE_{.x = 800, .y = 800};
  static constexpr SDL_Point BUTTON_SIZE_{.x = 546, .y = 75};
  static constexpr SDL_FRect TITLE_RECT_{
      .x = 127,
      .y = 100,
      .w = BUTTON_SIZE_.x,
      .h = BUTTON_SIZE_.y,
  };

  struct MenuButton {
    std::string label;
    bool isDown;
    SDL_FRect rect;
    SDL_Color color;
  };

  std::array<MenuButton, 4> buttons_{
      MenuButton{
          .label = "EASY",
          .isDown = false,
          .rect =
              {.x = 127, .y = 200, .w = BUTTON_SIZE_.x, .h = BUTTON_SIZE_.y},
          .color = {.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = SDL_ALPHA_OPAQUE}},
      MenuButton{
          .label = "MEDIUM",
          .isDown = false,
          .rect =
              {.x = 127, .y = 300, .w = BUTTON_SIZE_.x, .h = BUTTON_SIZE_.y},
          .color = {.r = 0xFF, .g = 0x0, .b = 0xFF, .a = SDL_ALPHA_OPAQUE}},
      MenuButton{
          .label = "HARD",
          .isDown = false,
          .rect =
              {.x = 127, .y = 400, .w = BUTTON_SIZE_.x, .h = BUTTON_SIZE_.y},
          .color = {.r = 0x0, .g = 0xFF, .b = 0xFF, .a = SDL_ALPHA_OPAQUE}},
      MenuButton{
          .label = "QUIT",
          .isDown = false,
          .rect =
              {.x = 127, .y = 500, .w = BUTTON_SIZE_.x, .h = BUTTON_SIZE_.y},
          .color = {.r = 0x0, .g = 0xFF, .b = 0x0, .a = SDL_ALPHA_OPAQUE}},
  };

  bool mouseInButton_(SDL_Point mousePos, const MenuButton& button);

 public:
  void OnEnter(Game& game) override;
  void Update(Game& game, MouseState mouseState) override;
  void Draw(Game& game) override;
  void OnLeave(Game& game) override;
};

#endif
