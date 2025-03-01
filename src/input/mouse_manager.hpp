#ifndef INPUT_MOUSE_MANAGER_HPP_
#define INPUT_MOUSE_MANAGER_HPP_

/// Stores the position of and state of the left and right buttons of the mouse.
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
  /// Update the mouse state for this frame.
  void Update();

  /// Returns the current state of the mouse.
  MouseState State() const;
};

#endif
