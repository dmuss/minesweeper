#ifndef SCENES_MENU_SCENE_HPP_
#define SCENES_MENU_SCENE_HPP_

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_pixels.h>
#pragma GCC diagnostic pop

#include "../constants.hpp"
#include "scene_interface.hpp"

class MenuScene final : public SceneInterface {
  private:
#if defined(__EMSCRIPTEN__)
    static constexpr SDL_Point WINDOW_SIZE_{.x = 800, .y = 650};
#else
    static constexpr SDL_Point WINDOW_SIZE_{.x = 800, .y = 800};
#endif
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

    std::vector<MenuButton> buttons_{
        MenuButton{
            .label = "EASY",
            .isDown = false,
            .rect =
                {.x = 127, .y = 200, .w = BUTTON_SIZE_.x, .h = BUTTON_SIZE_.y},
            .color = Colors::Green,
        },
        MenuButton{
            .label = "MEDIUM",
            .isDown = false,
            .rect =
                {.x = 127, .y = 300, .w = BUTTON_SIZE_.x, .h = BUTTON_SIZE_.y},
            .color = Colors::Yellow,
        },
        MenuButton{
            .label = "HARD",
            .isDown = false,
            .rect =
                {.x = 127, .y = 400, .w = BUTTON_SIZE_.x, .h = BUTTON_SIZE_.y},
            .color = Colors::Orange,
        },
#if !defined(__EMSCRIPTEN__)
        MenuButton{
            .label = "QUIT",
            .isDown = false,
            .rect =
                {.x = 127, .y = 500, .w = BUTTON_SIZE_.x, .h = BUTTON_SIZE_.y},
            .color = Colors::Gray,
        },
#endif
    };

    bool mouseInButton_(SDL_Point mousePos, const MenuButton& button);

  public:
    void OnEnter(Game& game) override;
    void Update(Game& game, MouseState mouseState) override;
    void Draw(Game& game) override;
    void OnLeave(Game& game) override;
};

#endif
