#include "game.h"

int main(int argc, char const **argv) {
  Game g;
  
  g.init();
  g.load();
  g.loop();
  g.end();

  return 0;
}