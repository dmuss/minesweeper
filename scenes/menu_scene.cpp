#include "menu_scene.hpp"

#include "../game.hpp"
#include "../sprites.hpp"

bool MenuScene::mouseInButton_(SDL_Point mousePos, const MenuButton& button) {
  auto mouseX = static_cast<float>(mousePos.x);
  auto mouseY = static_cast<float>(mousePos.y);

  auto x = button.rect.x;
  auto y = button.rect.y;
  auto right = button.rect.x + button.rect.w;
  auto bottom = button.rect.y + button.rect.h;

  return (mouseX > x && mouseX < right) && (mouseY > y && mouseY < bottom);
}

void MenuScene::OnEnter(Game& game) { game.SetWindowSize(WINDOW_SIZE_); }

void MenuScene::Update([[maybe_unused]] Game& game,
                       [[maybe_unused]] SDL_Event* mouseEvent) {
  bool leftClicked = (mouseEvent->button.button == SDL_BUTTON_LEFT) &&
                     !mouseEvent->button.down && mouseEvent->button.clicks > 0;

  SDL_Point mousePos{.x = static_cast<int>(mouseEvent->button.x),
                     .y = static_cast<int>(mouseEvent->button.y)};
  for (auto& button : buttons_) {
    if (mouseInButton_(mousePos, button)) {
      if (leftClicked) {
        // TODO: start game with difficulty
        if (button.label == "EASY") {
          SDL_Log("go to easy game");
        } else if (button.label == "MEDIUM") {
          SDL_Log("go to medium game");
        } else if (button.label == "HARD") {
          SDL_Log("go to hard game");
        } else {
          SDL_Log("quit request");
        }
      } else {
        button.isDown = false;
      }
    }
  }
}

void MenuScene::Draw(Game& game) {
  for (const auto& button : buttons_) {
    game.SetTextureColorMod(button.color);

    const auto buttonSpriteRect =
        button.isDown ? Sprites::ButtonDown : Sprites::ButtonUp;

    game.RenderSprite(buttonSpriteRect, button.rect);
  }

  game.SetTextureColorMod(
      {.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = SDL_ALPHA_OPAQUE});
}

void MenuScene::OnLeave([[maybe_unused]] Game& game) {}
