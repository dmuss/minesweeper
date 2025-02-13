#include "mouse_manager.hpp"

void MouseManager::Update() {
  oldState_ = currState_;

  auto buttons = SDL_GetMouseState(&currState_.x, &currState_.y);

  currState_.leftDown = buttons & SDL_BUTTON_LMASK;
  currState_.leftClicked = !currState_.leftDown && oldState_.leftDown;

  currState_.rightDown = buttons & SDL_BUTTON_RMASK;
  currState_.rightClicked = !currState_.rightDown && oldState_.rightDown;
}

MouseState MouseManager::State() const { return currState_; }
