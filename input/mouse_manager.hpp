#ifndef INPUT_MOUSE_MANAGER_HPP_
#define INPUT_MOUSE_MANAGER_HPP_

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_mouse.h>
#pragma GCC diagnostic pop

struct MouseState {
  float x;
  float y;
  bool leftDown;
  bool leftClicked;
  bool rightDown;
  bool rightClicked;
};

/// Updates and maintains the current state of the mouse every frame.
class MouseManager {
 private:
  MouseState oldState_;
  MouseState currState_;

 public:
  void Update() {
    oldState_ = currState_;

    auto buttons = SDL_GetMouseState(&currState_.x, &currState_.y);

    currState_.leftDown = buttons & SDL_BUTTON_LMASK;
    currState_.leftClicked = !currState_.leftDown && oldState_.leftDown;

    currState_.rightDown = buttons & SDL_BUTTON_RMASK;
    currState_.rightClicked = !currState_.rightDown && oldState_.rightDown;
  }

  MouseState State() const { return currState_; }
};

#endif
