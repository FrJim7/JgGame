#include "game_background.h"

#include <cstring>
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "game_defs.h"
#include "game_manager.h"

Background::Background() {
  transform_.setPosition(0.0f, 0.0f);
  transform_.setRotation(kDefaultRotation);
  transform_.setScale(kDefaultScale);

  transform_.setSize(sf::Vector2f(kWindowSizeX, kWindowSizeY));
  transform_.setTextureRect(sf::IntRect(0, 0, kWindowSizeX, kWindowSizeY));

  texture_id_ = 0;
  snprintf(path_, kBufferSize, "%s", kDefaultPath);

  velocity_ = sf::Vector2f(0.0f, 0.0f);
  set_type(ObjectType::kBackground);
}

Background::Background(const Background& other) {
  transform_ = other.transform_;
}

Background::~Background() {
}

void Background::init() {
  transform_.setPosition(0.0f, 0.0f);
  transform_.setRotation(kDefaultRotation);
  transform_.setScale(kDefaultScale);

  transform_.setSize(sf::Vector2f(kWindowSizeX, kWindowSizeY));
  transform_.setTextureRect(sf::IntRect(0, 0, kWindowSizeX, kWindowSizeY));
  
  snprintf(path_, kBufferSize, "%s", kDefaultPath);

  velocity_ = sf::Vector2f(0.0f, 0.0f);
  set_type(ObjectType::kBackground);
}

void Background::imgui() {
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

  data[0] = transform_.getSize().x;
  data[1] = transform_.getSize().y;
  if (ImGui::InputFloat2("Size", data)) {
    set_size(data[0], data[1]);
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

  data[0] = velocity_.x;
  data[1] = velocity_.y;
  if (ImGui::InputFloat2("Velocity", data)) {
    set_velocity(data[0], data[1]);
  }

  if (ImGui::CollapsingHeader(path_, ImGuiTreeNodeFlags_None)) {
    GameManager::instance().texture_manager_.showTexturesImgui(path_);
    if (ImGui::Button("Update")) {
      set_texture(path_);
    }
  }
}

void Background::update(float dt) {
  sf::IntRect temp = transform_.getTextureRect();
  temp.top += (int)(velocity_.y);
  temp.left += (int)(velocity_.x);
  transform_.setTextureRect(temp);
}

void Background::draw(sf::RenderTexture& texture) {
  texture.draw(transform_);
}

void Background::set_position(float px, float py) {
  transform_.setPosition(px, py);
}

void Background::set_rotation(float rotation) {
  transform_.setRotation(rotation);
}

void Background::set_scale(float scx, float scy) {
  transform_.setScale(scx, scy);
}

void Background::set_size(float sx, float sy) {
  transform_.setSize({sx, sy});
}

void Background::set_color(sf::Color color) {
  transform_.setFillColor(color);
  texture_.setColor(color);
}

void Background::set_outlinecolor(sf::Color o_color) {
  transform_.setOutlineColor(o_color);
}

void Background::set_text(const char *text) {
}

void Background::set_path(const char *path) {
}

void Background::set_texture(const char *filepath) {
  GameManager::instance().texture_manager_.getTexture(texture_, filepath, &texture_id_);

  snprintf(path_, kBufferSize, "%s", filepath);

  transform_.setTexture(texture_.getTexture(), true);
}

void Background::set_velocity(float vx, float vy) {
  velocity_.x = vx;
  velocity_.y = vy;
}

float Background::rotation() {
  return transform_.getRotation();
}

sf::Vector2f Background::position() {
  return transform_.getPosition();
}

sf::Vector2f Background::scale() {
  return transform_.getScale();
}

sf::Vector2f Background::size() {
  return transform_.getSize();
}

sf::FloatRect Background::area() {
  return transform_.getGlobalBounds();
}

sf::Color Background::color() {
  return transform_.getFillColor();
}

sf::Color Background::o_color() {
  return transform_.getOutlineColor();
}

char* Background::text() {
  return NULL;
}

char* Background::path() {
  return path_;
}


sf::Vector2f Background::velocity() {
  return velocity_;
}

unsigned int Background::texture_id() {
  return texture_id_;
}