#ifndef INTERFACE_H
#define INTERFACE_H

#include "scripts.h"
#include <ncurses.h>
#include <string>
#include <vector>

class Interface {
public:
  Interface();
  ~Interface();

  void main_menu(Scripts &scripts);

  // NOTE : There may be a better place for this
  std::string home = std::getenv("HOME");
  std::string script_dir = home + "/.scripts/essentials/";

private:
  void print_banner();
  void draw_menu();
  void handle_input(Scripts &scripts, int ch);

  WINDOW *menuwin;
  int highlight;
  int width, height, startx, starty;

  std::vector<std::string> list_scripts;
};

#endif
