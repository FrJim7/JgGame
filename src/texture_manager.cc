#include "texture_manager.h"

#include <cstring>
#include "sqlite3.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"
#include "tinyfiledialogs.h"

TextureManager::TextureManager() {
  default_.texture_.loadFromFile(kDefaultPath);
  snprintf(default_.path_, kBufferSize, "%s", kDefaultPath);
  default_.count_ = 0;
}

TextureManager::~TextureManager() {
  for (int i = 0; i < data_.size(); i++) {
    free(data_[i]);
  }
  data_.clear();
}

TextureManager::TextureManager(const TextureManager& other) {
};

void TextureManager::parsePath(const char *path) {
  if (NULL == path) {
    return;
  }

  int aux_index = 0;
  int start_index = 0;
  int path_length = strlen(path);

  memset(parsed_path_, 0, kBufferSize);
  parsed_path_[0] = '.';
  parsed_path_[1] = '.';

  for(int x = 0; x < path_length; ++x) {
    if(path[x] == kGameRoot[aux_index]) {
      aux_index++;
    } else {
      aux_index = 0;
    }
    if(aux_index == kGameRootSize) {
      start_index = x + 1;
    }
  }

  aux_index = 2;

  for (int x = start_index; x < path_length; ++x) {
    parsed_path_[aux_index] = path[x];
    aux_index++;
  }
}

void TextureManager::imgui() {
  const char *kFilterPatterns[2] = { "*.jpg", "*.png" };
  char const *path = nullptr;

  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("New")) {
      ImGui::MenuItem("New Texture", NULL, false, false);
      ImGui::InputText("Path", temp_path_, kBufferSize);
      ImGui::SameLine();
      if (ImGui::Button("Open")){
        path = tinyfd_openFileDialog(NULL, NULL, 2, kFilterPatterns, NULL, 0);
        parsePath(path);
        snprintf(temp_path_, kBufferSize, "%s", parsed_path_);
      }
      if (ImGui::Button("Create")) {
        addTexture(temp_path_);
        snprintf(temp_path_, kBufferSize, "");
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }

  for (int i = 0; i < data_.size(); ++i) {
    ImGui::Selectable("Texture Id:");
      
    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
      ImGui::SetDragDropPayload("TEXTURE", &i, sizeof(int));
      ImGui::EndDragDropSource();
    }

    if (ImGui::IsItemHovered()) {
      ImGui::BeginTooltip();
      ImGui::Image(data_[i]->texture_, kDisplaySize);
      ImGui::EndTooltip();
    }
    ImGui::SameLine();
    ImGui::Text("%d  |", data_[i]->id_);
    
    ImGui::SameLine();
    ImGui::Text("Source: %s  |", data_[i]->path_);

    ImGui::SameLine();
    ImGui::Text("Size: %d x %d  |", data_[i]->texture_.getSize().x, 
      data_[i]->texture_.getSize().y);

    if (data_[i]->count_ < 1) {
      if (ImGui::Button("Delete")) {
        delTexture(i);
      }
    }
    ImGui::Separator();
  }
}

void TextureManager::showTexturesImgui(char *temp) {
  for (int i = 0; i < data_.size(); ++i) {
    if (ImGui::Selectable(data_[i]->path_)) {
      snprintf(temp, kBufferSize, "%s", data_[i]->path_);
    }
  }
}

void TextureManager::saveDB(sqlite3 *db) {
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

  snprintf(exec, kBufferSize, "DELETE FROM Textures");
  err_code = sqlite3_exec(db, exec, NULL, 0, NULL);

  for (int i = 0; i < data_.size(); ++i) {
    if (data_[i] != nullptr) {
      snprintf(exec, kBufferSize, "INSERT INTO Textures\n VALUES(%d, '%s')", i, data_[i]->path_);
      err_code = sqlite3_exec(db, exec, NULL, 0, NULL);
    } 
  }

  sqlite3_close(db);
}

int TextureManager::loadCallback(void *data, int argc, char **argv, 
  char **azColName) {
  TextureManager *temp_data = (TextureManager*) data;

  temp_data->addTexture(argv[1]);

  return 0;
}


void TextureManager::loadDB(sqlite3 *db) {
  int err_code;
  char *err_msg;
  char exec[kBufferSize];
  memset(exec, 0, kBufferSize);

  erase();

  err_code = sqlite3_open("../data/Db/Jg_DB.db", &db);
  if (err_code != SQLITE_OK) {
    fprintf(stdout, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
  } else {
    fprintf(stdout, "Open DB successfully\n");
  }

  sprintf(exec, "SELECT * from Textures");
  err_code = sqlite3_exec(db, exec, loadCallback, this, &err_msg);

  sqlite3_close(db);
}

void TextureManager::getTexture(sf::Sprite &spr, const char *filepath, unsigned int *last_id) {
  
  if (NULL == filepath) return;
  if (NULL == last_id) return;

  bool no_exist = true;

  for (int i = 0; i < data_.size(); i++) {
    if ((*last_id) == data_.at(i)->id_) {
      data_.at(i)->count_--;
    }
    if (strncmp(filepath, data_.at(i)->path_, kBufferSize) == 0) {
      spr.setTexture(data_.at(i)->texture_, true);
      data_[i]->count_++;
      (*last_id) = data_.at(i)->id_;
      no_exist = false;
    }
  }

  if (no_exist) {
    spr.setTexture(default_.texture_, true);
    for (int i = 0; i < data_.size(); i++) {
      if ((*last_id) == data_.at(i)->id_) {
        data_.at(i)->count_--;
      }
    }
  }
}

bool TextureManager::addTexture(const char *filepath) {
  if (NULL == filepath) return false;

   Texture *temp = (Texture*)malloc(sizeof(Texture));

  if (temp->texture_.loadFromFile(filepath)) {
    id_++;
    temp->id_ = id_;
    temp->count_ = 0;
    temp->texture_.setRepeated(true);
    snprintf(temp->path_, kBufferSize, "%s", filepath);

    data_.push_back(temp);
    return true;
  } else {
    // GUSTAVO: If you allocate with malloc(), you must use deallocate
    // with free() , not delete
    delete temp;
  }

  temp = nullptr;

  return false;
}

void TextureManager::delTexture(int position) {
  free(data_[position]);
  data_.erase(data_.begin() + position);
}

void TextureManager::erase() {
  for (int i = 0; i < data_.size(); i++) {
    free(data_[i]);
    data_[i] = NULL;
  }
  data_.erase(data_.begin(), data_.end());
  id_ = 1;
}
