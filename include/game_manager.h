#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__ 1

#include "texture_manager.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include "scene.h"

/**
 * @brief      This class describes a sqlite 3.
 */
class sqlite3;

/**
 * @brief      This class describes a game object.
 */
class GameObject;

/**
 * @brief      This class describes a game manager.
 */
class GameManager {
 public:
  
  /**
   * @brief      Creates an static instance of the GameManager class, only one can be created at any time,
   * 
   *
   * @return     The GameManager
   */
  static GameManager& instance();

  /**
   * @brief      Initializes the im graphical user interface.
   */
  void initImGui();
  
  /**
   * @brief      Updtae the im graphical user interface.
   *
   * @param      render  The render
   * @param[in]  dT      The Delta time
   */
  void updateImGui(sf::RenderTexture& render, sf::Time dT);
  /**
   * @brief      Render the im graphical user interface.
   */
  void renderImGui();

  bool start_imgui_;
  
  Scene scene_;
  GameObject *inspectable_;

  sf::RenderWindow r_window_;
  TextureManager texture_manager_;
 protected:
  /**
   * @brief      Constructs a new instance.
   *
   * @param[in]  other  The other
   */
  GameManager(const GameManager& other);

  sqlite3 *db;

  ImGuiID dockspace_id_;
  ImGuiViewport* viewport;

  ImGuiWindowFlags dock_flg_;
  ImGuiWindowFlags render_flg_;

  bool w_open_;

 private:
  /**
   * @brief      Constructs a new instance.
   */
  GameManager();
  /**
   * @brief      Destroys the object.
   */
  ~GameManager();

};

#endif//__GAME_MANAGER_H__