#ifndef SCRIPTS_H
#define SCRIPTS_H

#include <string>
#include <vector>

class Scripts {
public:
  Scripts();
  ~Scripts();

  void write_scripts();
  std::vector<std::string> load_scripts(const std::string &dir_path);
  void run_script(const std::string &path, const std::string &name);

private:
};

#endif
