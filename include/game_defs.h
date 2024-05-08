/**
 * @defgroup   GAME_DEFS game defs
 *
 * @brief      This file implements game defs.
 *
 * @author     Paco
 * @date       2019
 */
#ifndef __GAME_DEFS_H__
#define __GAME_DEFS_H__ 1

#include "SFML/Graphics.hpp"

const char kGameRoot[] = "JgGame_v2";
const unsigned int kGameRootSize = 9;

const unsigned int kSmallBuffer = 64;
const unsigned int kBufferSize = 256;
const unsigned int kBufferSizeLarge = 512;

const unsigned int kWindowSizeX = 1280;
const unsigned int kWindowSizeY = 720;
const unsigned int kWindowFramerate = 60;

const unsigned int kMaximumFields = 3;

const sf::Vector2f kDisplaySize = sf::Vector2f(200.0f, 200.0f);

const sf::Vector2f kDefaultPosition = sf::Vector2f(200.0f, 200.0f);
const sf::Vector2f kDefaultScale = sf::Vector2f(1.0f, 1.0f);
const sf::Vector2f kDefaultSize = sf::Vector2f(180.0f, 180.0f);

const unsigned int kDefaultCharSize = 10;
const float kDefaultRotation = 0.0f;

const sf::Color kDefaultColor = sf::Color::White;

// GUSTAVO: Please do not hardcode paths or values when you can use the
// database or a config file.
const char kDefaultText[] = "Welcome to JgGame";
const char kDefaultFont[] = "../data/default/default.ttf";
const char kDefaultPath[] = "../data/default/default.png";


const char kGameBackgroundPath[] = "../data/starfield.jpg";
const char kGameTicPath[] = "../data/tic.png";
const char kGameTacPath[] = "../data/tac.png";
const char kGameToePath[] = "../data/toe.png";

#endif//__GAME_DEFS_H__
