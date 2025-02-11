#ifndef SCENES_SCENE_MANAGER_HPP_
#define SCENES_SCENE_MANAGER_HPP_

#include <unordered_map>

#include "scene_interface.hpp"

enum class Scene : uint8_t {
  Game,
  Menu,
  // Used to assert all scenes created with manager. Add new scenes above here.
  NUM_SCENES,
};

class SceneManager {
 private:
  std::unordered_map<Scene, SceneInterfaceUPtr> scenes_;
  SceneInterface* currScene_ = nullptr;
  Game& game_;

 public:
  explicit SceneManager(Game& game, Scene initialScene);

  void Update(SDL_Event* mouseEvent);

  void Draw();

  void SwitchScene(Scene scene);
};

#endif
