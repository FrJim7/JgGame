#include "game_field.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "game_sprite.h"
#include "game_manager.h"

Field::Field() {
  value_ = 0;
  texture_id_ = 0;

  token_ = nullptr;

  set_type(ObjectType::kField);
}

Field::~Field() {
  if (nullptr != token_) delete token_;
}

Field::Field(const Field &other) {
}

void Field::init() {
  value_ = 0;
  
  if (nullptr != token_) {
    GameManager::instance().texture_manager_.getTexture(*token_, kDefaultPath, &texture_id_);
    delete token_;
    token_ = nullptr;
    texture_id_ = 0;
  }
}

void Field::imgui() {
  Rectangle::imgui();
  ImGui::Text("%d", value_);
  if(ImGui::Button("Reset")) {
    init();
  }
}

void Field::draw(sf::RenderTexture& texture) {
  Rectangle::draw(texture);
  if (token_ != nullptr) texture.draw((*token_));
}

void Field::set_token(const char *filepath) {
  if (value_ == 0) {
    token_ = new sf::Sprite();
    GameManager::instance().texture_manager_.getTexture (*token_, filepath, &texture_id_);

    sf::Vector2u texture_size = token_->getTexture()->getSize();

    token_->setOrigin(texture_size.x * 0.5f, texture_size.y * 0.5f);
    token_->setPosition(position() + (size() * 0.5f));
  }
}

void Field::set_value(int value) {
  value_ = value;
}
 
int Field::value() {
  return value_;
}