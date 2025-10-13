#include "interface.h"
#include "scripts.h"
#include "session.h"
#include <cstdlib>
#include <ncurses.h>

int main() {

  // NOTE :Is there a better naming scheme?

  Session session;
  session.initialize();

  Scripts scripts;

  Interface interface;
  // the main run loop is inside main_menu
  interface.main_menu(scripts);

  return 0;
}
