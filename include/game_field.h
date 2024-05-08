#ifndef __GAME_FIELD_H__
#define __GAME_FIELD_H__ 1

#include "game_rectangle.h"

/**
 * @brief      This class describes a field.
 */
class Field : public Rectangle {
 public:

  /**
   * @brief      Constructs a new instance.
   */
  Field();
  
  /**
   * @brief      Destroys the object.
   */
  virtual ~Field();

  /**
   * @brief      Initializes the object.
   */
  void init() override;
  
  /**
   * @brief      Loads the information used by imgui.
   */
  void imgui() override;
  
  /**
   * @brief      Draw the object in the texture given.
   *
   * @param      texture  The texture
   */
  void draw(sf::RenderTexture& texture) override;

  /**
   * @brief      Sets the token sprite.
   *
   * @param[in]  filepath  The filepath
   */
  void set_token(const char *filepath);
  
  /**
   * @brief      Sets the value of the cell.
   *
   * @param[in]  value  The value
   */
  void set_value(int value);

  /**
   * @brief      Returns the value of the cell.
   *
   * @return     value of the cell.
   */
  int value();

 protected:
  Field(const Field &other);
 
 private:
  int value_;
  unsigned int texture_id_;
  
  sf::Sprite *token_;
};

#endif//__GAME_FIELD_H__