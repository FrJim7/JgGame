#include "game_rectangle.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "game_defs.h"

Rectangle::Rectangle() {
  transform_.setPosition(kDefaultPosition);
  transform_.setRotation(kDefaultRotation);
  transform_.setScale(kDefaultScale);
  transform_.setSize(kDefaultSize);

  transform_.setFillColor(kDefaultColor);
  transform_.setOutlineColor(kDefaultColor);
  transform_.setOutlineThickness(1.0f);

  set_type(ObjectType::kRectangle);
}

Rectangle::Rectangle(const Rectangle& other) {
  transform_ = other.transform_;
}

Rectangle::~Rectangle() {
}

void Rectangle::init() {
  transform_.setPosition(kDefaultPosition);
  transform_.setRotation(kDefaultRotation);
  transform_.setScale(kDefaultScale);
  transform_.setSize(kDefaultSize);
  transform_.setOutlineThickness(1.0f);

  transform_.setFillColor(kDefaultColor);
  transform_.setOutlineColor(kDefaultColor);

  set_type(ObjectType::kRectangle);
}

void Rectangle::imgui() {
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
}

void Rectangle::update(float dt) {
}

void Rectangle::draw(sf::RenderTexture& texture) {
  texture.draw(transform_);
}

void Rectangle::set_position(float px, float py) {
  transform_.setPosition(px, py);
}

void Rectangle::set_rotation(float rotation) {
  transform_.setRotation(rotation);
}

void Rectangle::set_scale(float scx, float scy) {
  transform_.setScale(scx, scy);
}

void Rectangle::set_size(float sx, float sy) {
  transform_.setSize(sf::Vector2f(sx, sy));
}

void Rectangle::set_color(sf::Color color) {
  transform_.setFillColor(color);
}

void Rectangle::set_outlinecolor(sf::Color o_color) {
  transform_.setOutlineColor(o_color);
}

void Rectangle::set_text(const char *text) {
}

void Rectangle::set_path(const char *path) {
}

void Rectangle::set_velocity(float vx, float vy) {
}

void Rectangle::set_texture(const char *filepath) {
}

float Rectangle::rotation() {
  return transform_.getRotation();
}

sf::Vector2f Rectangle::position() {
  return transform_.getPosition();
}

sf::Vector2f Rectangle::scale() {
  return transform_.getScale();
}

sf::Vector2f Rectangle::size() {
  return transform_.getSize();
}

sf::FloatRect Rectangle::area() {
  return transform_.getGlobalBounds();
}

sf::Color Rectangle::color() {
  return transform_.getFillColor();
}

sf::Color Rectangle::o_color() {
  return transform_.getOutlineColor();
}

char* Rectangle::text() {
  return NULL;
}

char* Rectangle::path() {
  return NULL;
}

sf::Vector2f Rectangle::velocity() {
  return sf::Vector2f(0, 0);
}

unsigned int Rectangle::texture_id() {
  return 0;
}