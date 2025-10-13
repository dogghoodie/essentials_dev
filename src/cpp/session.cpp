#include "session.h"
#include <ncurses.h>

Session::Session() {}
Session::~Session() { endwin(); }

void Session::initialize() {
  // ncurses session settings
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);
  start_color();
  use_default_colors();
  init_pair(1, COLOR_BLACK, COLOR_CYAN);
}
