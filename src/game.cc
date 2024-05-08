#include "game.h"

#include "scene.h"
#include "game_manager.h"

Game::Game() {
  delta_clock_.restart();
}

Game::Game(const Game &other) {
}

Game::~Game() {
}

void Game::init() {
  gmanager_ = &GameManager::instance();

  gmanager_->r_window_.create(sf::VideoMode(kWindowSizeX, kWindowSizeY), 
  "Game");
  gmanager_->r_window_.setFramerateLimit(kWindowFramerate);
  
  r_texture_.create(kWindowSizeX, kWindowSizeY);

  gmanager_->initImGui();
  gmanager_->scene_.init();
}

void Game::load() {

}

void Game::input() {
  while (gmanager_->r_window_.pollEvent(event_)) {

    ImGui::SFML::ProcessEvent(event_);

    if (event_.type == sf::Event::Closed) {
      gmanager_->r_window_.close();
    } 

    if (event_.type == sf::Event::MouseButtonReleased) {
      if (!gmanager_->start_imgui_) gmanager_->scene_.input();
    }

    if (event_.type == sf::Event::KeyReleased) {
      if (event_.key.code == sf::Keyboard::Tab) {
        gmanager_->start_imgui_ = !gmanager_->start_imgui_;
      }
    }

  }
}

void Game::loop() {
  sf::Clock imClock;
  delta_clock_.restart();


  while (gmanager_->r_window_.isOpen()) {
    input();
    
    if (gmanager_->start_imgui_) {
      gmanager_->updateImGui(r_texture_, imClock.restart());
      //ImGui::ShowDemoWindow();
    } else {
      gmanager_->scene_.update(delta_time_);
    }

    draw();

    // Time
    delta_time_ = ((float)delta_clock_.getElapsedTime().asMilliseconds()) * 0.001f;
    delta_clock_.restart();
  }
}

void Game::draw() {
  // Texture Drawing
  r_texture_.clear(sf::Color::Black);
  gmanager_->scene_.draw(r_texture_);
  r_texture_.display();

  // Texture to Sprite
  spr_.setTexture(r_texture_.getTexture());

  // Draw Sprite
  gmanager_->r_window_.clear();

  if (!gmanager_->start_imgui_) {
    gmanager_->r_window_.draw(spr_);
  }
  gmanager_->renderImGui();
  gmanager_->r_window_.display();
}

void Game::end() {
  gmanager_->texture_manager_.erase();
  gmanager_->scene_.end();
}