#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__ 1

#include "SFML/Graphics.hpp"

#include "scene.h"
#include "game_defs.h"

/**
 * @brief      Object types
 */
enum ObjectType
{
  kNone = 0,
  kLabel = 1,
  kSprite = 2,
  kRectangle = 3,
  kBackground = 4,
  kField = 5
};

/**
 * @brief      This class describes a game object.
 */
class GameObject {
 public:

  /**
   * @brief      Constructs a new instance.
   */
  GameObject();
  
  /**
   * @brief      Destroys the object.
   */
  virtual ~GameObject();

  /**
   * @brief      Loads the information used by imgui.
   */
  virtual void imgui();

  /**
   * @brief      Sets the tag.
   *
   * @param[in]  tag   The new value
   */
  void set_tag(const char *tag);
  
  /**
   * @brief      Sets the enable.
   *
   * @param[in]  enable  The enable
   */
  void set_enable(bool enable);
  
  /**
   * @brief      Sets the type.
   *
   * @param[in]  type  The type
   */
  void set_type(ObjectType type);
  
  /**
   * @brief      Sets the order.
   *
   * @param[in]  order  The order
   */
  void set_order(int order);

  /**
   * @brief      Return the object id.
   *
   * @return     The id.
   */
  unsigned int id();
  /**
   * @brief      Return the order of draw.
   *
   * @return     The order.
   */
  int order();

  /**
   * @brief      Return the type of object
   *
   * @return     The object type.
   */
  ObjectType type();

  /**
   * @brief      Return the tag
   *
   * @return     The tag
   */
  char* tag();
  /**
   * @brief      Return if the object is enable
   *
   * @return     The enable.
   */
  bool enable();

  /**
   * @brief      Initializes the object.
   */
  virtual void init() = 0;

  /**
   * @brief      Updates the object using the given dt.
   *
   * @param[in]  dt    Delta time.
   */
  virtual void update(float dt) = 0;

  /**
   * @brief      Draws the object in the texture given.
   *
   * @param      texture  The texture
   */
  virtual void draw(sf::RenderTexture& texture) = 0;

  /**
   * @brief      Takes an absolute path and makes it relative to the bin carpet in the folder. The texture must
   *             be in the Game folder and outside the bin folder.
   *
   * @param[in]  path  The path to parse
   */
  //virtual void parsePath(const char *path);

  /**
   * @brief      Sets the position.
   *
   * @param[in]  px    The new value
   * @param[in]  py    The new value
   */
  virtual void set_position(float px, float py) = 0;
  
  /**
   * @brief      Sets the rotation.
   *
   * @param[in]  rotation  The rotation
   */
  virtual void set_rotation(float rotation) = 0;
  
  /**
   * @brief      Sets the scale.
   *
   * @param[in]  scx   The new value
   * @param[in]  scy   The new value
   */
  virtual void set_scale(float scx, float scy) = 0;
  
  /**
   * @brief      Sets the size.
   *
   * @param[in]  sx    The new value
   * @param[in]  sy    The new value
   */
  virtual void set_size(float sx, float sy) = 0;

  /**
   * @brief      Sets the color.
   *
   * @param[in]  color  The color
   */
  virtual void set_color(sf::Color color) = 0;
  
  /**
   * @brief      Sets the outlinecolor.
   *
   * @param[in]  o_color  The o color
   */
  virtual void set_outlinecolor(sf::Color o_color) = 0;

  /**
   * @brief      Sets the text.
   *
   * @param[in]  text  The text
   */
  virtual void set_text(const char *text) = 0;
  
  /**
   * @brief      Sets the path.
   *
   * @param[in]  path  The path
   */
  virtual void set_path(const char *path) = 0; 
  
  /**
   * @brief      Sets the velocity.
   *
   * @param[in]  vx    The new value
   * @param[in]  vy    The new value
   */
  virtual void set_velocity(float vx, float vy) = 0;

  /**
   * @brief      Sets the texture.
   *
   * @param[in]  filepath  The filepath
   */
  virtual void set_texture(const char *filepath) = 0;

  /**
   * @brief      Returns rotation
   *
   * @return     The rotation.
   */
  virtual float rotation() = 0;
  /**
   * @brief      Returns the position
   *
   * @return     The position.
   */
  virtual sf::Vector2f position() = 0;
  /**
   * @brief      Returns the scale
   *
   * @return     The scale.
   */
  virtual sf::Vector2f scale() = 0;
  /**
   * @brief      Returns the size
   *
   * @return     The size.
   */
  virtual sf::Vector2f size() = 0;
  /**
   * @brief      Returns the area of the object
   *
   * @return     The area.
   */
  virtual sf::FloatRect area() = 0;

  /**
   * @brief      Returns the fill color
   *
   * @return     The color.
   */
  virtual sf::Color color() = 0;
  /**
   * @brief      Returns the outline color
   *
   * @return     The color.
   */
  virtual sf::Color o_color() = 0;

  /**
   * @brief      Returns the text.
   *
   * @return     The text.
   */
  virtual char* text() = 0;
  /**
   * @brief      Returns the path of the loaded file.
   *
   * @return     The path.
   */
  virtual char* path() = 0;
  /**
   * @brief      Return the velocity.
   *
   * @return     The velocity.
   */
  virtual sf::Vector2f velocity() = 0;
  /**
   * @brief      Returns the last texture used id.
   *
   * @return     The id.
   */
  virtual unsigned int texture_id() = 0;

 protected:
  /**
   * @brief      Constructs a new instance.
   *
   * @param[in]  n     Copy object.
   */
  GameObject(const GameObject &n);

 private:
  int order_;
  unsigned int id_;
  ObjectType type_;

  char tag_[kBufferSize];
  bool enable_;
};

#endif//__GAME_OBJECT_H__