#include "game_label.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"
#include "tinyfiledialogs.h"

#include "game_defs.h"
#include "game_manager.h"

Label::Label() {
  transform_.setPosition(kDefaultPosition);
  transform_.setRotation(kDefaultRotation);
  transform_.setScale(kDefaultScale);
  transform_.setCharacterSize(kDefaultCharSize);

  transform_.setFillColor(kDefaultColor);
  transform_.setOutlineColor(kDefaultColor);
  transform_.setOutlineThickness(1.0f);

  if (text_font_.loadFromFile(kDefaultFont))
    transform_.setFont(text_font_);
  
  transform_.setString(kDefaultText);

  snprintf(path_, kBufferSize, "%s", kDefaultFont);
  snprintf(text_, kBufferSize, "%s", kDefaultText);

  set_type(ObjectType::kLabel);
}

Label::Label(const Label& other) {
  transform_ = other.transform_;
}

Label::~Label() {
}

void Label::init() {
  transform_.setPosition(kDefaultPosition);
  transform_.setRotation(kDefaultRotation);
  transform_.setScale(kDefaultScale);
  transform_.setCharacterSize(kDefaultCharSize);
  transform_.setOutlineThickness(1.0f);

  transform_.setFillColor(kDefaultColor);
  transform_.setOutlineColor(kDefaultColor);

  text_font_.loadFromFile(kDefaultFont);

  if (text_font_.loadFromFile(kDefaultFont))
    transform_.setFont(text_font_);
  
  transform_.setString(kDefaultText);

  snprintf(path_, kBufferSize, "%s", kDefaultFont);
  snprintf(text_, kBufferSize, "%s", kDefaultText);

  set_type(ObjectType::kLabel);
}

void Label::parsePath(const char *path) {
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

void Label::imgui() {
  GameObject::imgui();

  ImGui::Separator();

  float data[2] = {transform_.getPosition().x, transform_.getPosition().y};
  if (ImGui::InputFloat2("Position", data)) {
    set_position(data[0], data[1]);
  }
  float rotation = transform_.getRotation();
  if (ImGui::InputFloat("Rotation", &rotation)) {
    set_rotation(rotation);
  }
  data[0] = transform_.getScale().x;
  data[1] = transform_.getScale().y;
  if (ImGui::InputFloat2("Scale", data)) {
    set_scale(data[0], data[1]);
  }
  data[0] = size().x;
  if (ImGui::InputFloat("Size", data)) {
    set_size(data[0], 0.0f);
  }

  int color_data[4] = {transform_.getFillColor().r, 
    transform_.getFillColor().g, 
    transform_.getFillColor().b, 
    transform_.getFillColor().a};
  if (ImGui::InputInt4("Fill Color", color_data)) {
    set_color(sf::Color(color_data[0], color_data[1], 
      color_data[2], color_data[3]));
  }

  int color_data2[4];
  color_data2[0] = transform_.getOutlineColor().r;
  color_data2[1] = transform_.getOutlineColor().g;
  color_data2[2] = transform_.getOutlineColor().b;
  color_data2[3] = transform_.getOutlineColor().a;
  if (ImGui::InputInt4("Outline Color", color_data2)) {
    set_outlinecolor(sf::Color(color_data2[0], color_data2[1], 
      color_data2[2], color_data2[3]));
  }

  if (ImGui::InputText("String", text_, kBufferSize)) {
    set_text(text_);
  }

  const char *kFilterPatterns[2] = { "*.ttf" };
  char const *path = nullptr;

  ImGui::Text("Path: %s", path_);

  if (ImGui::Button("...")){
    path = tinyfd_openFileDialog(NULL, NULL, 1, kFilterPatterns, NULL, 0);
    if(path != NULL) {
      parsePath(path);
      snprintf(path_, kBufferSize, "%s", parsed_path_);
      set_path(path_);
    }
  }
}

void Label::update(float dt) {
}

void Label::draw(sf::RenderTexture& texture) {
  texture.draw(transform_);
}

void Label::set_position(float px, float py) {
  transform_.setPosition(px, py);
}

void Label::set_rotation(float rotation) {
  transform_.setRotation(rotation);
}

void Label::set_scale(float scx, float scy) {
  transform_.setScale(scx, scy);
}

void Label::set_size(float sx, float sy) {
  transform_.setCharacterSize((unsigned int)sx);
}

void Label::set_color(sf::Color color) {
  transform_.setFillColor(color);
}

void Label::set_outlinecolor(sf::Color o_color) {
  transform_.setOutlineColor(o_color);
}

void Label::set_text(const char *text) {
  transform_.setString(text);
  snprintf(text_, kBufferSize, "%s", text);
}

void Label::set_path(const char *path) {
  if (text_font_.loadFromFile(path)) {
    transform_.setFont(text_font_);
    snprintf(path_, kBufferSize, "%s", path);
  }
}

void Label::set_velocity(float vx, float vy) {
}

void Label::set_texture(const char *filepath) {
}

float Label::rotation() {
  return transform_.getRotation();
}

sf::Vector2f Label::position() {
  return transform_.getPosition();
}

sf::Vector2f Label::scale() {
  return transform_.getScale();
}

sf::Vector2f Label::size() {
  return sf::Vector2f((float)transform_.getCharacterSize(), 0.0f);
}

sf::FloatRect Label::area() {
  return transform_.getGlobalBounds();
}

sf::Color Label::color() {
  return transform_.getFillColor();
}

sf::Color Label::o_color() {
  return transform_.getOutlineColor();
}

char* Label::text() {
  return text_;
}

char* Label::path() {
  return path_;
}

sf::Vector2f Label::velocity() {
  return sf::Vector2f(0, 0);
}

unsigned int Label::texture_id() {
  return 0;
}