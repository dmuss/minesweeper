#ifndef SCENES_SCENE_MANAGER_HPP_
#define SCENES_SCENE_MANAGER_HPP_

#include <memory>
#include <unordered_map>

#include "game_scene.hpp"
#include "scene_interface.hpp"

enum class Scene : uint8_t {
  Menu,
  Game,
};

class SceneManager {
 private:
  std::unordered_map<Scene, SceneInterfaceUPtr> scenes_;
  SceneInterface* currScene_ = nullptr;
  Game& game_;

 public:
  explicit SceneManager(Game& game, Scene initialScene) : game_(game) {
    scenes_.insert({Scene::Game, std::make_unique<GameScene>()});

    currScene_ = scenes_.at(initialScene).get();
    currScene_->OnEnter(game_);
  }

  void Update(SDL_Event* mouseEvent) { currScene_->Update(game_, mouseEvent); }

  void Draw() { currScene_->Draw(game_); }

  void SwitchScene(Scene scene) {
    currScene_->OnLeave(game_);
    currScene_ = scenes_.at(scene).get();
    currScene_->OnEnter(game_);
  }
};

#endif
