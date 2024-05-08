#ifndef __GAME_SPRITE_H__
#define __GAME_SPRITE_H__ 1

#include "SFML/Graphics.hpp"

#include "game_object.h"

class Sprite : public GameObject {
 public:
  Sprite();
  virtual ~Sprite() override;

  /**
   * @brief      Initializes the object.
   */
  void init() override;
  
  /**
   * @brief      Loads the information used by imgui.
   */
  void imgui() override;

  /**
   * @brief      Updates the object using the given dt.
   *
   * @param[in]  dt    Delta time.
   */
  void update(float dt) override;

  /**
   * @brief      Draws the object in the texture given.
   *
   * @param      texture  The texture
   */
  void draw(sf::RenderTexture& texture) override;

  /**
   * @brief      Takes an absolute path and makes it relative to the bin carpet in the folder. The texture must
   *             be in the Game folder and outside the bin folder.
   *
   * @param[in]  path  The path to parse
   */
  //void parsePath(const char *path);

  /**
   * @brief      Sets the position.
   *
   * @param[in]  px    The new value
   * @param[in]  py    The new value
   */
  void set_position(float px, float py) override;
  
  /**
   * @brief      Sets the rotation.
   *
   * @param[in]  rotation  The rotation
   */
  void set_rotation(float rotation) override;
  
  /**
   * @brief      Sets the scale.
   *
   * @param[in]  scx   The new value
   * @param[in]  scy   The new value
   */
  void set_scale(float scx, float scy) override;
  
  /**
   * @brief      Sets the size.
   *
   * @param[in]  sx    The new value
   * @param[in]  sy    The new value
   */
  void set_size(float sx, float sy) override;

  /**
   * @brief      Sets the color.
   *
   * @param[in]  color  The color
   */
  void set_color(sf::Color color) override;
  
  /**
   * @brief      Sets the outlinecolor.
   *
   * @param[in]  o_color  The o color
   */
  void set_outlinecolor(sf::Color o_color) override;

  /**
   * @brief      Sets the text.
   *
   * @param[in]  text  The text
   */
  void set_text(const char *text) override;
  
  /**
   * @brief      Sets the path.
   *
   * @param[in]  path  The path
   */
  void set_path(const char *path) override; 
  
  /**
   * @brief      Sets the velocity.
   *
   * @param[in]  vx    The new value
   * @param[in]  vy    The new value
   */
  void set_velocity(float vx, float vy) override;

  /**
   * @brief      Sets the texture.
   *
   * @param[in]  filepath  The filepath
   */
  void set_texture(const char *filepath) override;

  /**
   * @brief      Returns rotation
   *
   * @return     The rotation.
   */
  float rotation() override;
  /**
   * @brief      Returns the position
   *
   * @return     The position.
   */
  sf::Vector2f position() override;
  /**
   * @brief      Returns the scale
   *
   * @return     The scale.
   */
  sf::Vector2f scale() override;
  /**
   * @brief      Returns the size
   *
   * @return     The size.
   */
  sf::Vector2f size() override;
  /**
   * @brief      Returns the area of the object
   *
   * @return     The area.
   */
  sf::FloatRect area() override;

  /**
   * @brief      Returns the fill color
   *
   * @return     The color.
   */
  sf::Color color() override;
  /**
   * @brief      Returns the outline color
   *
   * @return     The color.
   */
  sf::Color o_color() override;

  /**
   * @brief      Returns the text.
   *
   * @return     The text.
   */
  char* text() override;
  /**
   * @brief      Returns the path of the loaded file.
   *
   * @return     The path.
   */
  char* path() override;
  /**
   * @brief      Return the velocity.
   *
   * @return     The velocity.
   */
  sf::Vector2f velocity() override;
  /**
   * @brief      Returns the last texture used id.
   *
   * @return     The id.
   */
  unsigned int texture_id() override;

  Sprite(const Sprite &n);

 private:
  sf::Sprite transform_;
  char path_[kBufferSize];
  unsigned int texture_id_;
};

#endif//__GAME_SPRITE_H__