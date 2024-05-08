#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__ 1

#include "game_defs.h"

#include <vector>
#include "SFML/Graphics.hpp"

/**
 * @brief      This class describes a sqlite 3.
 */
class sqlite3;

/**
 * @brief      This structure is used to load Texture data in the Manager.
 */
struct Texture {
  sf::Texture texture_;
  
  unsigned int id_;
  unsigned int count_;
  
  char path_[kBufferSize];
};

/**
 * @brief      This class describes a texture manager.
 */
class TextureManager {
 public:
  /**
   * @brief      Constructs a new instance.
   */
  TextureManager();
  /**
   * @brief      Destroys the object.
   */
  ~TextureManager();

  /**
   * @brief      Loads the information used by imgui.
   */
  void imgui();
  /**
   * @brief      Shows the textures in imgui editor.
   *
   * @param      temp  The temporary
   */
  void showTexturesImgui(char *temp);

  /**
   * @brief      Adds a texture.
   *
   * @param[in]  filepath  The filepath
   *
   * @return     True if added, false otherwise
   */
  bool addTexture(const char *filepath);
  /**
   * @brief      Deletes a texture unused
   *
   * @param[in]  position  The position
   */
  void delTexture(int position);

  /**
   * @brief      Takes an absolute path and makes it relative to the bin carpet in the folder. The texture must
   *             be in the Game folder and outside the bin folder.
   *
   * @param[in]  path  The path to parse
   */
  void parsePath(const char *path);

  /**
   * @brief      Saves the texture data in the db.
   *
   * @param      db    The database
   */
  void saveDB(sqlite3 *db);
  
  /**
   * @brief      Loads the texture data in the db.
   *
   * @param      db    The database
   */
  void loadDB(sqlite3 *db);

  /**
   * @brief      Callback use to db queries.
   *
   * @param      data       The data
   * @param[in]  argc       The count of arguments
   * @param      argv       The arguments array
   * @param      azColName  The az col name
   *
   * @return     { description_of_the_return_value }
   */
  static int loadCallback(void *data, int argc, char **argv, 
  char **azColName);

  /**
   * @brief      Gets the texture and applies to the sprite.
   *
   * @param      spr       The sprire
   * @param[in]  filepath  The filepath
   * @param      last_id   The last identifier
   */
  void getTexture(sf::Sprite &spr, const char *filepath, unsigned int *last_id);

  /**
   * @brief      Release the textures stored.
   */
  void erase();

 protected:
  /**
   * @brief      Constructs a new instance.
   *
   * @param[in]  other  The other
   */
  TextureManager(const TextureManager& other);

 private:
  Texture default_;
  std::vector<Texture*> data_; 

  char temp_path_[kBufferSize];
  char parsed_path_[kBufferSize];
};

// internal id used when adding textures.

static unsigned int id_ = 1;

#endif//__TEXTURE_MANAGER_H__