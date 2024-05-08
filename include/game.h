#ifndef __GAME_H__
#define __GAME_H__ 1

#include "SFML/Graphics.hpp"

#include "game_defs.h"

/**
 * @brief      This class describes a game manager.
 */
class GameManager;

/**
 * @brief      This class describes a game.
 */
class Game {
 public:
  /**
   * @brief      Constructs a new instance.
   */
  Game();
  /**
   * @brief      Destroys the object.
   */
  ~Game();

  /**
   * @brief      Initializes the object.
   */
  void init();
  /**
   * @brief      Load the game data.
   */
  void load();
  /**
   * @brief      Manage the game input.
   */
  void input();
  /**
   * @brief      Game main loop
   */
  void loop();
  /**
   * @brief      Game draw function
   */
  void draw();
  /**
   * @brief      End and release functions-
   */
  void end();

 protected:
  /**
   * @brief      Constructs a new instance.
   *
   * @param[in]  n     The object to copy.
   */
  Game(const Game &n);
 
 private:
  sf::RenderTexture r_texture_;

  sf::Sprite spr_;

  sf::Event event_;
  sf::Clock delta_clock_;
  
  GameManager* gmanager_;

  double delta_time_;
};

#endif//__GAME_H__