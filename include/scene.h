#ifndef __SCENE_H__
#define __SCENE_H__ 1

#include <vector>
#include "SFML/Graphics.hpp"

#include "game_defs.h"

/**
 * @brief      This class describes a field.
 */
class Field;
/**
 * @brief      This class describes a sqlite 3.
 */
class sqlite3;
/**
 * @brief      This class describes a game object.
 */
class GameObject;

/**
 * @brief      Game values for game rules.
 */
enum kPlayerValues {
  kNoPlayer = 0,
  kPlayer1 = 1,
  kPlayer2 = 11,
  kPlayer1Max = 3,
  kPlayer2Max = 33,
};

/**
 * @brief      This class describes a scene.
 */
class Scene {
 public:
  /**
   * @brief      Constructs a new instance.
   */
  Scene();

  /**
   * @brief      Destroys the object.
   */
  ~Scene();

  /**
   * @brief      Initializes the object.
   */
  void init();
  /**
   * @brief      Loads the scene information and data from the Data Base.
   */
  void load();
  /**
   * @brief      Manage the imput of the scene
   */
  void input();
  /**
   * @brief      Checks the game fields following the rules to determine a winner.
   */
  void check();
  /**
   * @brief      Resets the game cells.
   *
   * @param[in]  r     Reset request.
   */
  void reset(bool r);
  /**
   * @brief      Updates the scene with the given dt.
   *
   * @param[in]  dt    Delta Time
   */
  void update(float dt);
  /**
   * @brief      Draw the scene objects in the Texture given
   *
   * @param      screen  The screen
   */
  void draw(sf::RenderTexture& screen);
  /**
   * @brief      Release the scene data
   */
  void end();

  /**
   * @brief      Load callback function for objects.
   *
   * @param      data       The data
   * @param[in]  argc       The count of arguments
   * @param      argv       The arguments array
   * @param      azColName  The az col name
   *
   * @return     { description_of_the_return_value }
   */
  static int loadCallbackObjects(void *data, int argc, char **argv, 
  char **azColName);

  /**
   * @brief      Load callback function for configuration.
   *
   * @param      data       The data
   * @param[in]  argc       The count of arguments
   * @param      argv       The arguments array
   * @param      azColName  The az col name
   *
   * @return     { description_of_the_return_value }
   */
  static int loadCallbackConfig(void *data, int argc, char **argv, 
  char **azColName);

  /**
   * @brief      Saves the scene data in the db.
   *
   * @param      db    The database
   */
  void saveDB(sqlite3 *db);
  /**
   * @brief      Loads the scene data form the db.
   *
   * @param      db    The database
   */
  void loadDB(sqlite3 *db);

  /**
   * @brief      Adds an object to the scene data, it is used in imgui editor.
   *
   * @param[in]  type  The type
   */
  void addObject(int type);
  
  /**
   * @brief      Function used in the callback function for Objects, using the
   *             data collected form the db.
   *
   * @param[in]  id       The identifier
   * @param[in]  tag      The tag
   * @param[in]  enable   The enable
   * @param[in]  type     The type
   * @param[in]  order    The order
   * @param[in]  px       Position x
   * @param[in]  py       Position y
   * @param[in]  angle    The angle
   * @param[in]  scx      Scale x
   * @param[in]  scy      Scale y
   * @param[in]  sx       Size x
   * @param[in]  sy       Size y
   * @param[in]  cr       Red color value
   * @param[in]  cg       Green color value
   * @param[in]  cb       Blue color value
   * @param[in]  ca       Alpha value
   * @param[in]  fcr      Outline red value
   * @param[in]  fcg      Outline green value
   * @param[in]  fcb      Outline blue value
   * @param[in]  fca      Outline alpha value
   * @param[in]  text_id  The texture identifier
   * @param[in]  text     The text
   * @param[in]  path     The path
   * @param[in]  vx       Velocity x
   * @param[in]  vy       Velocity t
   * @param[in]  value    The value
   */
  void addObject(int id, const char *tag, bool enable, int type, int order,float px, float py, float angle, float scx, float scy, float sx, float sy, int cr, int cg, int cb, int ca, int fcr, int fcg, int fcb, int fca, int text_id, const char *text, const char *path, float vx, float vy, int value);
  /**
   * @brief      Sets the configuration with the data loaded from the Data Base.
   *
   * @param[in]  turn          The turn
   * @param[in]  score1        The score 1
   * @param[in]  score2        The score 2
   * @param[in]  token1        The token 1
   * @param[in]  token2        The token 2
   * @param[in]  player1_name  The player 1 name
   * @param[in]  player2_name  The player 2 name
   */
  void setConfig(int turn, int score1, int score2, const char *token1, const char *token2, const char *player1_name, const char *player2_name);
  /**
   * @brief      Deletes the selected object
   */
  void delObject();

  /**
   * @brief      Show the editor information from the scene.
   */
  void imgui();
  /**
   * @brief      Show the fields window in the editor
   */
  void fieldsImgui();
  /**
   * @brief      Shows the configuration window in the editor
   */
  void configImgui();

 protected:
  /**
   * @brief      Constructs a new instance.
   *
   * @param[in]  n     Scene to copy
   */       
  Scene(const Scene &n);
 
 private:
  std::vector<Field*> fields_;
  std::vector<GameObject*> scene_data_;

  int turn_;
  int score1_;
  int score2_;
  int results_[8];

  char token1_[kBufferSize];
  char token2_[kBufferSize];
  char temp_string_[kBufferSize];
  char player1_name_[kBufferSize];
  char player2_name_[kBufferSize];
  
  bool reset_request_;
};

#endif//__SCENE_H__