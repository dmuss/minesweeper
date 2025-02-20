#ifndef SCENES_SCENE_INTERFACE_HPP_
#define SCENES_SCENE_INTERFACE_HPP_

#include <memory>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <SDL3/SDL_events.h>
#pragma GCC diagnostic pop

#include "../input/mouse_manager.hpp"

class Game;

class SceneInterface {
  public:
    virtual ~SceneInterface() = default;

    /// Called when a scene is entered.
    virtual void OnEnter(Game& game) = 0;

    /// Updates the scene based on the provided mouse event.
    virtual void Update(Game& game, MouseState mouseState) = 0;

    /// Draws the scene.
    virtual void Draw(Game& game) = 0;

    /// Called when a scene is left.
    virtual void OnLeave(Game& game) = 0;
};

using SceneInterfaceUPtr = std::unique_ptr<SceneInterface>;

#endif
