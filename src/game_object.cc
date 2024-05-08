#include "game_object.h"

#include <cstdio>
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

GameObject::GameObject() {
  static unsigned int internal_id = 0;

  id_ = internal_id;
  order_ = 1;
  type_ = ObjectType::kNone;

  snprintf(tag_, kBufferSize, "default_tag %d", id_);
  enable_ = true;

  internal_id++;
}

GameObject::GameObject(const GameObject &n) {
  id_ = n.id_;

  snprintf(tag_, kBufferSize, "%s", n.tag_);
}

GameObject::~GameObject() {

}

void GameObject::imgui() {
  ImGui::Text("Object id: %d", id_);
  ImGui::Checkbox("Enable", &enable_);
  ImGui::InputText("Tag", tag_, kBufferSize);
  ImGui::SliderInt("Order", &order_, 0, 16);
  switch(type()) {
    case kNone:
    break;
    case kLabel: ImGui::Text("Object type: Label");
    break;
    case kSprite: ImGui::Text("Object type: Sprite");
    break;
    case kRectangle: ImGui::Text("Object type: Rectangle");
    break;
    case kBackground: ImGui::Text("Object type: Background");
    break;
    case kField: ImGui::Text("Object type: Field");
    break;
  }
}

unsigned int GameObject::id() {
  return id_;
}

void GameObject::set_type(ObjectType type) {
  type_ = type;
}

ObjectType GameObject::type() {
  return type_;
}

void GameObject::set_tag(const char* tag) {
  snprintf(tag_, kBufferSize, "%s", tag);
}

char* GameObject::tag() {
  return tag_;
}

void GameObject::set_enable(bool enable) {
  enable_ = enable;
}

bool GameObject::enable() {
  return enable_;
}

void GameObject::set_order(int order) {
  order_ = order;
}

int GameObject::order() {
  return order_;
}
