#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void showHelp();
void documentFile(std::string path);
void documentAllFiles();

std::string ss;

std::std::vector<std::string> variables;
std::std::vector<std::string> functions;

int main(int argc, char const *argv[]) {
  if (argc > 1)
    ss = argv[1];
  else {
    showHelp();
    return 1;
  }
  switch (argc) {
  case 1:
    showHelp();
    return 0;
    break;
  case 2:
    if (ss == "-all")
      documentAllFiles();
    else
      documentFile(ss);
    break;
  }
  return 0;
}

void showHelp() { std::cout << "usage: " << std::endl; }

void documentFile(std::string path) {
  std::cout << "reading file" << std::endl;
  std::ifstream openFile;
  openFile.open(path.c_str(), std::ifstream::in);

  std::string line;
  if (openFile.is_open()) {
    while (getline(openFile, line)) {
    }
  } else {
    std::cout << "File not found" << std::endl;
    return;
  }
  openFile.close();
}

void documentAllFiles() { std::cout << "Documenting all files" << std::endl; }
