#include "interface.h"
#include "scripts.h"
#include <iostream>

Interface::Interface()
    : menuwin(nullptr), highlight(0), width(50), height(0), startx(0),
      starty(0) {}

Interface::~Interface() {
  // ensure menuwin is deleted upon shutdown
  if (menuwin) {
    delwin(menuwin);
    std::cerr << "menuwin outliving exit." << std::endl;
  }
}

void Interface::print_banner() {
  const std::vector<std::string> banner = {
      "                           __  .__       .__",
      "   ____   ______ ______ ____   _____/  |_|__|____  |  |   ______",
      " _/ __ \\ /  ___//  ___// __ \\ /    \\   __\\  \\__  \\ |  |  /  ___/",
      "\\  ___/ \\___ \\ \\___ \\\\  ___/|   |  \\  | |  |/ __ \\|  |__\\___ "
      "\\",
      "  \\___  >____  >____  >\\___  >___|  /__| |__(____  /____/____  >",
      "     \\/     \\/     \\/     \\/     \\/             \\/          \\/"};
  int lines = banner.size();
  int starty = (LINES / 2) - (lines + 8);

  for (int i = 0; i < lines; ++i) {
    int startx = (COLS - banner[i].size()) / 2;
    mvprintw(starty + i, startx, "%s", banner[i].c_str());
  }
}

void Interface::main_menu(Scripts &scripts) {
  // TODO : Maybe move these bash commands and
  // clean up the menuwin variables

  // ensure these files exist and are executable on launch
  system("bash -c 'mkdir -p $HOME/.scripts/essentials/ '");
  system("bash -c 'chmod +x $HOME/.scripts/essentials/*.sh '");

  // load ~/.scripts/essentials/ into script_dir
  this->list_scripts = scripts.load_scripts(script_dir);

  // initialize menuwin
  height = list_scripts.size() + 4;
  starty = (LINES - height) / 2 + 4;
  startx = (COLS - width) / 2;
  menuwin = newwin(height, width, starty, startx);
  keypad(menuwin, TRUE);

  // menu run loop
  while (true) {
    clear();
    print_banner();
    draw_menu();
    refresh();
    wrefresh(menuwin);
    int ch = wgetch(menuwin);
    handle_input(scripts, ch);
  }
}

void Interface::handle_input(Scripts &scripts, int ch) {
  // controls switch
  switch (ch) {
  case KEY_UP:
  case 'k':
  case 'K':
    highlight = (highlight - 1 + list_scripts.size()) % list_scripts.size();
    break;
  case KEY_DOWN:
  case 'j':
  case 'J':
    highlight = (highlight + 1) % list_scripts.size();
    break;
  case '\n':
    scripts.run_script(script_dir, list_scripts[highlight]);
    // reinitialize ncurses after running script
    // TODO : Maybe clean up with session functions
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    menuwin = newwin(height, width, starty, startx);
    keypad(menuwin, TRUE);
    break;
  case 'q':
    delwin(menuwin);
    endwin();
    exit(0);
  }
}

void Interface::draw_menu() {

  int quit_icony = (getmaxy(menuwin) - 1);
  int quit_iconx = 40;
  werase(menuwin);
  box(menuwin, 0, 0);
  mvwprintw(menuwin, 0, 2, " Scripts ");
  mvwprintw(menuwin, quit_icony, quit_iconx, " q ");

  for (size_t i = 0; i < list_scripts.size(); ++i) {
    if ((int)i == highlight) {
      wattron(menuwin, A_BOLD | COLOR_PAIR(1));
      mvwprintw(menuwin, i + 2, 2, "%-46s", list_scripts[i].c_str());
      wattroff(menuwin, A_BOLD | COLOR_PAIR(1));
    } else {
      mvwprintw(menuwin, i + 2, 2, "%-46s", list_scripts[i].c_str());
    }
  }
}
