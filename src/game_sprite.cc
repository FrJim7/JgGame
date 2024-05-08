#include "game_sprite.h"

#include <cstring>
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "game_defs.h"
#include "game_manager.h"

Sprite::Sprite() {
  transform_.setPosition(kDefaultPosition);
  transform_.setRotation(kDefaultRotation);
  transform_.setScale(kDefaultScale);

  texture_id_ = 0;

  snprintf(path_, kBufferSize, "%s", kDefaultPath);

  set_type(ObjectType::kSprite);
}

Sprite::Sprite(const Sprite& other) {
  transform_ = other.transform_;
}

Sprite::~Sprite() {
}

void Sprite::init() {
  transform_.setPosition(kDefaultPosition);
  transform_.setRotation(kDefaultRotation);
  transform_.setScale(kDefaultScale);

  texture_id_ = 0;

  snprintf(path_, kBufferSize, "%s", kDefaultPath);

  set_type(ObjectType::kSprite);
}

void Sprite::imgui() {
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

  int color_data[4] = {transform_.getColor().r, 
    transform_.getColor().g, 
    transform_.getColor().b, 
    transform_.getColor().a};
  
  if (ImGui::InputInt4("Fill Color", color_data)) {
    set_color(sf::Color(color_data[0], color_data[1], 
      color_data[2], color_data[3]));
  }

  if (ImGui::CollapsingHeader(path_, ImGuiTreeNodeFlags_None)) {
    GameManager::instance().texture_manager_.showTexturesImgui(path_);
    if (ImGui::Button("Update")) {
      set_texture(path_);
    }
  }
}

void Sprite::update(float dt) {
}

void Sprite::draw(sf::RenderTexture& texture) {
  texture.draw(transform_);
}

void Sprite::set_position(float px, float py) {
  transform_.setPosition(px, py);
}

void Sprite::set_rotation(float rotation) {
  transform_.setRotation(rotation);
}

void Sprite::set_scale(float scx, float scy) {
  transform_.setScale(scx, scy);
}

void Sprite::set_size(float sx, float sy) {
}

void Sprite::set_color(sf::Color color) {
  transform_.setColor(color);
}

void Sprite::set_outlinecolor(sf::Color o_color) {
}

void Sprite::set_text(const char *text) {
}

void Sprite::set_path(const char *path) {
}

void Sprite::set_velocity(float vx, float vy) {
}

void Sprite::set_texture(const char *filepath) {
  GameManager::instance().texture_manager_.getTexture(transform_, filepath, &texture_id_);

  sf::Vector2u size = transform_.getTexture()->getSize();
  snprintf(path_, kBufferSize, "%s", filepath);

  transform_.setOrigin(size.x * 0.5f, size.y * 0.5f);
}

float Sprite::rotation() {
  return transform_.getRotation();
}

sf::Vector2f Sprite::position() {
  return transform_.getPosition();
}

sf::Vector2f Sprite::scale() {
  return transform_.getScale();
}

sf::Vector2f Sprite::size() {
  return sf::Vector2f(0, 0);
}

sf::FloatRect Sprite::area() {
  return transform_.getGlobalBounds();
}

sf::Color Sprite::color() {
  return transform_.getColor();
}

sf::Color Sprite::o_color() {
  return sf::Color(kDefaultColor);
}

char* Sprite::text() {
  return NULL;
}

char* Sprite::path() {
  return path_;
}

sf::Vector2f Sprite::velocity() {
  return sf::Vector2f(0, 0);
}

unsigned int Sprite::texture_id() {
  return texture_id_;
}