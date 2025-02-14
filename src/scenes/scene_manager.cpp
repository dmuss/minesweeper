#include "scene_manager.hpp"

#include <SDL3/SDL_assert.h>

#include "game_scene.hpp"
#include "menu_scene.hpp"

SceneManager::SceneManager(Game& game, Scene initialScene) : game_(game) {
  scenes_.insert({Scene::Game, std::make_unique<GameScene>()});
  scenes_.insert({Scene::Menu, std::make_unique<MenuScene>()});
  SDL_assert(scenes_.size() == static_cast<size_t>(Scene::NUM_SCENES));

  currScene_ = scenes_.at(initialScene).get();
  currScene_->OnEnter(game_);
}

void SceneManager::Update(MouseState mouseState) {
  currScene_->Update(game_, mouseState);
}

void SceneManager::Draw() { currScene_->Draw(game_); }

void SceneManager::SwitchScene(Scene scene) {
  currScene_->OnLeave(game_);
  currScene_ = scenes_.at(scene).get();
  currScene_->OnEnter(game_);
}
