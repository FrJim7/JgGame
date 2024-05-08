#include "scene.h"

#include <cstring>
#include "sqlite3.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "game_field.h"
#include "game_label.h"
#include "game_sprite.h"
#include "game_manager.h"
#include "game_rectangle.h"
#include "game_background.h"

Scene::Scene() {
  turn_ = kPlayer1;
  score1_ = 0;
  score2_ = 0;
  snprintf(token1_, kBufferSize, "");
  snprintf(token2_, kBufferSize, "");
  snprintf(temp_string_, kBufferSize, "");
  snprintf(player1_name_, kBufferSize, "");
  snprintf(player2_name_, kBufferSize, "");
}

Scene::Scene(const Scene &n) {}

Scene::~Scene() {}

int Scene::loadCallbackObjects(void *data, int argc, char **argv, 
  char **azColName) {
  Scene *temp = (Scene*)data;
  
  bool enable = false;
  if (std::atoi(argv[2]) == 1) enable = true;

  temp->addObject(std::atoi(argv[0]), argv[1], enable, std::atoi(argv[3]), std::atoi(argv[4]), std::atof(argv[5]), std::atof(argv[6]), std::atof(argv[7]), std::atof(argv[8]), std::atof(argv[9]), std::atof(argv[10]), std::atof(argv[11]), std::atoi(argv[12]), std::atoi(argv[13]), std::atoi(argv[14]), std::atoi(argv[15]), std::atoi(argv[16]), std::atoi(argv[17]), std::atoi(argv[18]), std::atoi(argv[19]), std::atoi(argv[20]), argv[21], argv[22], std::atof(argv[23]), std::atof(argv[24]), std::atoi(argv[25]));

  return 0;
}


int Scene::loadCallbackConfig(void *data, int argc, char **argv, 
  char **azColName) {
  
  Scene *temp = (Scene*)data;
  
  temp->setConfig(std::atoi(argv[0]), std::atoi(argv[1]), std::atoi(argv[2]), argv[3], argv[4], argv[5], argv[6]);

  return 0;
}

void Scene::setConfig(int turn, int score1, int score2, const char *token1, const char *token2, const char *player1_name, const char *player2_name) {
  turn = turn;
  score1_ = score1;
  score2_ = score2;
  snprintf(token1_, kBufferSize, "%s", token1);
  snprintf(token2_, kBufferSize, "%s", token2);
  snprintf(player1_name_, kBufferSize, "%s", player1_name);
  snprintf(player2_name_, kBufferSize, "%s", player2_name);
}

void Scene::addObject(int type) {
  switch (type) {
    case kNone:
    break;
    case kLabel: scene_data_.push_back(new Label());
    break;
    case kSprite: scene_data_.push_back(new Sprite());
    break;
    case kRectangle: scene_data_.push_back(new Rectangle());
    break;
    case kBackground: scene_data_.push_back(new Background());
    break;
  }
}

// GUSTAVO: What the hell is this monstruous function with 25 parameters
// and no explanation??
void Scene::addObject(int id, const char *tag, bool enable, int type, int order,float px, float py, float angle, float scx, float scy, float sx, float sy, int cr, int cg, int cb, int ca, int fcr, int fcg, int fcb, int fca, int text_id, const char *text, const char *path, float vx, float vy, int value) {

  GameObject *temp = nullptr;

  switch (type) {
    case kNone:
    break;
    case kLabel: temp = new Label();
    break;
    case kSprite: temp = new Sprite();
    break;
    case kRectangle: temp = new Rectangle();
    break;
    case kBackground: temp = new Background();
    break;
    case kField: temp = new Field();
    break;
  }

  if (temp == nullptr) return;

  temp->set_tag(tag);
  temp->set_enable(enable);
  temp->set_order(order);
  temp->set_position(px, py);
  temp->set_rotation(angle);
  temp->set_scale(scx, scy);
  temp->set_size(sx, sy);
  temp->set_color(sf::Color(cr,cg,cb,ca));
  temp->set_outlinecolor(sf::Color(fcr,fcg,fcb,fca));
  temp->set_text(text);
  if (type == kLabel) {
    temp->set_path(path);
  } else {
    temp->set_texture(path);
  }
  temp->set_velocity(vx, vy);

  if (type == kField) {
    ((Field*)temp)->set_value(0);
    fields_.push_back(((Field*)temp));
  } else {
    scene_data_.push_back(temp);
  }

}

void Scene::delObject() {
  for (int i = 0; i < scene_data_.size(); i++) {
    if (GameManager::instance().inspectable_ != nullptr) {
      if (GameManager::instance().inspectable_->id() == scene_data_[i]->id()) {
        delete scene_data_[i];
        scene_data_.erase(scene_data_.begin() + i);
        GameManager::instance().inspectable_ = nullptr;
      }
    }
  }
}

void Scene::imgui() {
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("New")) {
      if (ImGui::Button("Text")) {
        addObject(kLabel);
      }
      if (ImGui::Button("Sprite")) {
        addObject(kSprite);
      }
      if (ImGui::Button("Rectangle")) {
        addObject(kRectangle);
      }
      if (ImGui::Button("Background")) {
        addObject(kBackground);
      }
      ImGui::EndMenu();
    }
    if (ImGui::Selectable("Delete")) {
      delObject();
    }
    ImGui::EndMenuBar();
  }

  for(int i = 0; i < scene_data_.size(); i++) {
    if (scene_data_[i] != nullptr) {
      if (ImGui::Selectable(scene_data_[i]->tag())) {
        GameManager::instance().inspectable_ = scene_data_[i];
      }
    }
  }
}


void Scene::fieldsImgui() {
  for(int i = 0; i < fields_.size(); i++) {
    if (fields_[i] != nullptr) {
      if (ImGui::Selectable(fields_[i]->tag())) {
        GameManager::instance().inspectable_ = fields_[i];
      }
    }
  }
}

void Scene::configImgui() {
  ImGui::Text("Player1 token");
  if (ImGui::CollapsingHeader(token1_, ImGuiTreeNodeFlags_None)) {
    GameManager::instance().texture_manager_.showTexturesImgui(token1_);
  }
  ImGui::Text("Player2 token");
  if (ImGui::CollapsingHeader(token2_, ImGuiTreeNodeFlags_None)) {
    GameManager::instance().texture_manager_.showTexturesImgui(token2_);
  }

  ImGui::InputText("Player 1 name", player1_name_, kBufferSize);
  ImGui::InputText("Player 2 name", player2_name_, kBufferSize);
}

void Scene::saveDB(sqlite3 *db) {
  int err_code;
  char *err_msg;
  char exec[kBufferSize];
  memset(exec, 0, kBufferSize);

  err_code = sqlite3_open("../data/Db/Jg_DB.db", &db);
  if (err_code != SQLITE_OK) {
    fprintf(stdout, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
  } else {
    fprintf(stdout, "Open DB successfully\n");
  }

  snprintf(exec, kBufferSize, "DELETE FROM Objects");
  err_code = sqlite3_exec(db, exec, NULL, 0, NULL);

  snprintf(exec, kBufferSize, "DELETE FROM Config");
  err_code = sqlite3_exec(db, exec, NULL, 0, NULL);

  char temp[kBufferSize];

  for (int i = 0; i < scene_data_.size(); ++i) {
    int enable = 0;
    if (scene_data_[i]->enable()) enable = 1;

    snprintf(exec, kBufferSize, "INSERT INTO Objects\n VALUES(%d, '%s', %d, %d, %d, %f, %f, %f,%f, %f, %f, %f, %d, %d, %d, %d, %d, %d, %d, %d, %d, '%s', '%s', %f, %f, %d)", scene_data_[i]->id(), scene_data_[i]->tag(), enable, scene_data_[i]->type(), scene_data_[i]->order(), scene_data_[i]->position().x, scene_data_[i]->position().y, scene_data_[i]->rotation(), scene_data_[i]->scale().x, scene_data_[i]->scale().y, scene_data_[i]->size().x, scene_data_[i]->size().y, scene_data_[i]->color().r, scene_data_[i]->color().g, scene_data_[i]->color().b, scene_data_[i]->color().a, scene_data_[i]->o_color().r, scene_data_[i]->o_color().g, scene_data_[i]-> o_color().b, scene_data_[i]->o_color().a, scene_data_[i]->texture_id(), scene_data_[i]->text(), scene_data_[i]->path(), scene_data_[i]->velocity().x, scene_data_[i]->velocity().y, 0);
    err_code = sqlite3_exec(db, exec, NULL, 0, &err_msg);
    if (err_code != SQLITE_OK) printf("%s\n", err_msg);
  }

  snprintf(exec, kBufferSize, "INSERT INTO Config\n VALUES(%d, %d, %d, '%s', '%s', '%s', '%s')", turn_, score1_, score2_, token1_, token2_, player1_name_, player2_name_);
  err_code = sqlite3_exec(db, exec, NULL, 0, &err_msg);

  for (int i = 0; i < fields_.size(); i++) {
    int enable = 0;
    if (fields_[i]->enable()) enable = 1;

    snprintf(exec, kBufferSize, "INSERT INTO Objects\n VALUES(%d, '%s', %d, %d, %d, %f, %f, %f,%f, %f, %f, %f, %d, %d, %d, %d, %d, %d, %d, %d, %d, '%s', '%s', %f, %f, %d)", fields_[i]->id(), fields_[i]->tag(), enable, fields_[i]->type(), fields_[i]->order(), fields_[i]->position().x, fields_[i]->position().y, fields_[i]->rotation(), fields_[i]->scale().x, fields_[i]->scale().y, fields_[i]->size().x, fields_[i]->size().y, fields_[i]->color().r, fields_[i]->color().g, fields_[i]->color().b, fields_[i]->color().a, fields_[i]->o_color().r, fields_[i]->o_color().g, fields_[i]-> o_color().b, fields_[i]->o_color().a, fields_[i]->texture_id(), fields_[i]->text(), fields_[i]->path(), fields_[i]->velocity().x, fields_[i]->velocity().y, fields_[i]->value());
    err_code = sqlite3_exec(db, exec, NULL, 0, &err_msg);
    if (err_code != SQLITE_OK) printf("%s\n", err_msg);
  }

  sqlite3_close(db);
}

void Scene::loadDB(sqlite3 *db) {
  int err_code;
  char *err_msg;
  char exec[kBufferSize];
  memset(exec, 0, kBufferSize);

  end();

  err_code = sqlite3_open("../data/Db/Jg_DB.db", &db);
  if (err_code != SQLITE_OK) {
    fprintf(stdout, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
  } else {
    fprintf(stdout, "Open DB successfully\n");
  }

  sprintf(exec, "SELECT * from Objects");
  err_code = sqlite3_exec(db, exec, loadCallbackObjects, this, &err_msg);

  sprintf(exec, "SELECT * from Config");
  err_code = sqlite3_exec(db, exec, loadCallbackConfig, this, &err_msg);

  sqlite3_close(db);
}


void Scene::init() {
  GameManager::instance().texture_manager_.addTexture(kGameTicPath);
  GameManager::instance().texture_manager_.addTexture(kGameTacPath);
  GameManager::instance().texture_manager_.addTexture(kGameToePath);
  GameManager::instance().texture_manager_.addTexture(kGameBackgroundPath);

  //---------------------------------------------------

  GameObject *toe = new Sprite();
  GameObject *back = new Background();

  toe->set_texture(kGameToePath);
  back->set_texture(kGameBackgroundPath);

  toe->set_order(2);

  toe->set_position(kWindowSizeX * 0.5f, kWindowSizeY * 0.5f);
  toe->set_scale(0.65f, 0.65f);

  back->set_velocity(0.0f, 2.0f);

  scene_data_.push_back(back);
  scene_data_.push_back(toe);

  //---------------------------------------------------

  float x = toe->position().x - 271.0f;
  float y = toe->position().y - 271.0f;

  char temp_tag[kBufferSize];

  for (int i = 0; i < kMaximumFields; i++) {
    for (int j = 0; j < kMaximumFields; j++) {
      Field *field = new Field();

      field->set_order(3);
      field->set_position(x, y);
      field->set_color(sf::Color::Transparent);

      fields_.push_back(field);
      x += 181.0f;
    }
    x = toe->position().x - 271.0f;
    y+= 182.f;
  }

  for (int i = 0; i < kMaximumFields * kMaximumFields; i++) {
    snprintf(temp_tag, kBufferSize, "field_%d", i);
    fields_[i]->set_tag(temp_tag);
  }
  
  snprintf(token1_, kBufferSize, "%s", kGameTicPath);
  snprintf(token2_, kBufferSize, "%s", kGameTacPath);

  //---------------------------------------------------

  reset_request_ = false;
  GameObject *reset_button_ = new Label();

  reset_button_->set_tag("reset_button");
  
  reset_button_->set_text("Draw");
  reset_button_->set_path(kDefaultFont);
  reset_button_->set_size(40.0f, 40.0f);
  reset_button_->set_position( (kWindowSizeX * 0.5f) - 
   (reset_button_->area().width * 0.5f), kWindowSizeY - 65.0f);

  scene_data_.push_back(reset_button_);

  //---------------------------------------------------
  snprintf(player1_name_, kBufferSize, "player 1");
  snprintf(player2_name_, kBufferSize, "player 2");

  GameObject *player1_score = new Label();
  GameObject *player2_score = new Label();
  
  snprintf(temp_string_, kBufferSize, "%s: %d", player1_name_, score1_);
  
  player1_score->set_tag("score1");

  player1_score->set_text(temp_string_);
  player1_score->set_size(25.0f, 0.0f);
  player1_score->set_position(180.0f, 25.0f);

  snprintf(temp_string_, kBufferSize, "%s: %d", player2_name_, score2_);  

  player2_score->set_tag("score2");

  player2_score->set_text(temp_string_);
  player2_score->set_size(25.0f, 0.0f);
  player2_score->set_position(kWindowSizeX - 
   (180.0f + player2_score->area().width), 25.0f); 

  scene_data_.push_back(player1_score);
  scene_data_.push_back(player2_score);
}

void Scene::load() {
}

void Scene::input() {
  sf::Vector2f m_position;
  m_position.x = sf::Mouse::getPosition(GameManager::instance().r_window_).x;
  m_position.y = sf::Mouse::getPosition(GameManager::instance().r_window_).y;

  for (int i = 0; i < fields_.size(); i++) {
    if (fields_[i]->area().contains(m_position) && fields_[i]->value() == 0) {
      switch (turn_) {
        case kPlayer1: fields_[i]->set_token(token1_); 
        fields_[i]->set_value(kPlayer1); 
        turn_ = kPlayer2;
        break;
        case kPlayer2: fields_[i]->set_token(token2_);
        fields_[i]->set_value(kPlayer2);
        turn_ = kPlayer1;
        break;
      }
    }
  }

  for (int i = 0; i < scene_data_.size(); i++) {
    if (strncmp(scene_data_[i]->tag(), "reset_button", kBufferSize) == 0) {
      if (scene_data_[i]->area().contains(m_position)) reset_request_ = true;
    }
  }
}

void Scene::check() {
  for (int i = 0; i < 8; i++) {
    results_[i] = 0;
  }

  for (int i = 0; i < kMaximumFields; i++) {
    for (int j = 0; j < kMaximumFields; j++) {
      if(fields_[j + (i * kMaximumFields)]->enable()) {
        if (i == 0) results_[0] += fields_[j + (i * kMaximumFields)]->value();
        if (i == 1) results_[1] += fields_[j + (i * kMaximumFields)]->value();
        if (i == 2) results_[2] += fields_[j + (i * kMaximumFields)]->value();

        if (j == 0) results_[3] += fields_[j + (i * kMaximumFields)]->value();
        if (j == 1) results_[4] += fields_[j + (i * kMaximumFields)]->value();
        if (j == 2) results_[5] += fields_[j + (i * kMaximumFields)]->value();
      
        if (i == j) results_[6] += fields_[j + (i * kMaximumFields)]->value();
        if (i == 2 - j) results_[7] += fields_[j + (i * kMaximumFields)]->value();
      } 
    } 
  }

  for (int i = 0; i < 8; i++) {
    if (results_[i] == kPlayer1 * 3) {
      score1_++;
      reset_request_ = true;
    }
    if (results_[i] == kPlayer2 * 3) {
      score2_++;
      reset_request_ = true;
    }
  }
}

void Scene::reset(bool r) {
  if (!r) return;

  for (int i = 0; i < fields_.size(); i++) {
    if(fields_[i] != nullptr) fields_[i]->init();
  }

  reset_request_ = false;
}

void Scene::update(float dt) {
  for (int i = 0; i < scene_data_.size(); i++) {
    if(scene_data_[i] != nullptr) scene_data_.at(i)->update(dt);

    if (strncmp(scene_data_[i]->tag(), "score1", kBufferSize) == 0) {
      snprintf(temp_string_, kBufferSize, "%s: %d", player1_name_, score1_);
      scene_data_[i]->set_text(temp_string_);
    }
    if (strncmp(scene_data_[i]->tag(), "score2", kBufferSize) == 0) {
      snprintf(temp_string_, kBufferSize, "%s: %d", player2_name_, score2_);
      scene_data_[i]->set_text(temp_string_);
    }
  }

  for (int i = 0; i < fields_.size(); i++) {
    if(fields_[i] != nullptr) fields_.at(i)->update(dt);
  }

  if (fields_.size() > 0) {
    reset(reset_request_);
    check();
  }
}

void Scene::draw(sf::RenderTexture& screen) {
  int i = 0;
  do {
    for (int j = 0; j < scene_data_.size(); j++) {
      if(scene_data_[j]->enable() && scene_data_[j]->order() == i) {
        scene_data_[j]->draw(screen);
      }  
    }
    for (int j = 0; j < fields_.size(); j++) {
      if(fields_[j]->enable() && fields_[j]->order() == i) {
        fields_[j]->draw(screen);
      }  
    }
    i++;
  } while (i < 17);
}

void Scene::end() {
  for (int i = 0; i < scene_data_.size(); i++) {
    delete scene_data_[i];
    scene_data_[i] = nullptr;
  }
  
  for (int i = 0; i < fields_.size(); i++) {
    delete fields_[i];
    fields_[i] = nullptr;
  }

  scene_data_.erase(scene_data_.begin(), scene_data_.end());
  fields_.erase(fields_.begin(), fields_.end());

  turn_ = kPlayer1;
  score1_ = 0;
  score2_ = 0;
  snprintf(token1_, kBufferSize, "");
  snprintf(token2_, kBufferSize, "");
  snprintf(temp_string_, kBufferSize, "");
  snprintf(player1_name_, kBufferSize, "");
  snprintf(player2_name_, kBufferSize, "");
}
