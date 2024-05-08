#include "game_manager.h"

#include "sqlite3.h"

#include "game_object.h"

GameManager::GameManager() {
  start_imgui_ = false;
  inspectable_ = nullptr;

}

GameManager::~GameManager() {
  delete &instance();
}

GameManager::GameManager(const GameManager& other) {}

GameManager& GameManager::instance() {
  static GameManager* instance_ = nullptr;

  if (nullptr == instance_) {
    instance_ = new GameManager();
  }

  return *instance_;
}

void GameManager::initImGui() {
  ImGui::SFML::Init(r_window_);
  inspectable_ = nullptr;
  viewport = ImGui::GetMainViewport();

    //allow docking in the ImGui editor
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    //window flags to dockNode
  dock_flg_ = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar;
  dock_flg_ |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  dock_flg_ |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
}

void GameManager::updateImGui(sf::RenderTexture& render, sf::Time dT) {
  if (start_imgui_) {
    int err_code;
    char *err_msg;
    ImGui::SFML::Update(r_window_, dT);

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::Begin("Editor", &w_open_, dock_flg_);
    dockspace_id_ = ImGui::GetID("MyDockSpace");

    ImGui::DockSpace(dockspace_id_, ImVec2(0.0f, 0.0f));

    if (ImGui::BeginMenuBar()) {
      if (ImGui::Button("Save")) {
        scene_.saveDB(db);
        texture_manager_.saveDB(db);
      }
      if (ImGui::Button("Load")) {
        texture_manager_.loadDB(db);
        scene_.loadDB(db);
      }
      ImGui::EndMenuBar();
    }

    ImGui::Begin("TextureManager", &w_open_, ImGuiWindowFlags_MenuBar);
    texture_manager_.imgui();
    ImGui::End();

    ImGui::Begin("Fields", &w_open_, ImGuiWindowFlags_MenuBar);
    scene_.fieldsImgui();
    ImGui::End();

    ImGui::Begin("Configuration", &w_open_, ImGuiWindowFlags_MenuBar);
    scene_.configImgui();
    ImGui::End();

    ImGui::Begin("Hierachy",&w_open_, ImGuiWindowFlags_MenuBar);
    scene_.imgui();
    ImGui::End();

    ImGui::Begin("Inspector");
    if(inspectable_ != nullptr) inspectable_->imgui();
    ImGui::End();

    ImGui::Begin("Render");
    sf::FloatRect texture_rect = sf::FloatRect(0, 0, render.getSize().x, 
      render.getSize().y);
    sf::Vector2f size = ImGui::GetContentRegionAvail();
    ImGui::Image(render, size, texture_rect);
    ImGui::End();

    ImGui::End();
  }
}

void GameManager::renderImGui() {
  if (start_imgui_) {
    ImGui::SFML::Render(r_window_);
  }
}