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

void MenuScene::Update([[maybe_unused]] Game& game, MouseState mouseState) {
  SDL_Point mousePos{.x = static_cast<int>(mouseState.x),
                     .y = static_cast<int>(mouseState.y)};
  for (auto& button : buttons_) {
    if (mouseInButton_(mousePos, button)) {
      if (mouseState.leftDown) { button.isDown = true; }

      if (mouseState.leftClicked) {
        // TODO: Can this be cleaned up?
        if (button.label == "EASY") {
          game.StartGame(GameDifficulty::Easy);
        } else if (button.label == "MEDIUM") {
          game.StartGame(GameDifficulty::Medium);
        } else if (button.label == "HARD") {
          game.StartGame(GameDifficulty::Hard);
        } else {
          game.Quit();
        }
      }
    } else {
      button.isDown = false;
    }
  }
}

void MenuScene::Draw(Game& game) {
  game.RenderText("MINESWEEPER", TITLE_RECT_, Colors::White, 72);

  for (const auto& button : buttons_) {
    game.SetTextureColorMod(button.color);

    const auto buttonSpriteRect =
        button.isDown ? Sprites::ButtonDown : Sprites::ButtonUp;

    game.RenderSprite(buttonSpriteRect, button.rect);

    button.isDown ? game.RenderTextWithAlpha(button.label, button.rect, 200)
                  : game.RenderText(button.label, button.rect);
  }

  game.SetTextureColorMod(Colors::White);
}

void MenuScene::OnLeave([[maybe_unused]] Game& game) {}
