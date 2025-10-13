#include "scripts.h"
#include <filesystem>
#include <iostream>
#include <ncurses.h>

namespace fs = std::filesystem;

Scripts::Scripts() {}
Scripts::~Scripts() {}

void Scripts::write_scripts() {}

std::vector<std::string> Scripts::load_scripts(const std::string &dir_path) {

  std::vector<std::string> scripts;

  try {
    // iterate through every file
    for (auto &entry : fs::directory_iterator(dir_path)) {
      if (!entry.is_regular_file())
        // skip irregular files
        continue;
      // extract permissions of the file
      auto perms = entry.status().permissions();
      // check for executable permissions
      if ((perms & fs::perms::owner_exec) != fs::perms::none) {
        scripts.push_back(entry.path().filename().string());
      }
    }
  } catch (const std::exception &e) {
    endwin();
    std::cerr << "Error reading directory: " << e.what() << "\n";
    exit(1);
  }

  if (scripts.empty()) {
    /*
    endwin();
    std::cerr << "No executable scripts found in " << dir_path << "\n";
    exit(0);
    */

    system(R"(
bash -c "
  mkdir -p $HOME/.scripts/essentials &&
  touch $HOME/.scripts/essentials/{font.sh,formulae.sh,homebrew.sh,lazyvim.sh,nvim.sh,shell.sh,starship.sh,tmux.sh,ripgrep.sh} &&
  chmod +x $HOME/.scripts/essentials/*.sh
"
)");
  }

  return scripts;
}

void Scripts::run_script(const std::string &path, const std::string &name) {
  endwin();

  std::string fullpath = path + name;
  std::cout << "[Running " << path + name << "]\n";
  std::string cmd = "bash \"" + fullpath + "\"";

  system(cmd.c_str());
  std::cout << "\nPress Enter to return to menu...";
  std::cin.get();
}
