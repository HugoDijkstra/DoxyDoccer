#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void showHelp();
void documentFile(std::string path);
void documentAllFiles();

int main(int argc, char const *argv[]) {
  std::string ss = argv[1];
  switch (argc) {
  case 0:
    showHelp();
    return 0;
    break;
  case 1:
    if (ss == "-all")
      documentAllFiles();
    else
      documentFile(ss);
    return 1;
    break;
  }
  return 0;
}

void showHelp() { std::cout << "usage: " << std::endl; }

void documentFile(std::string path) {
  std::cout << "reading file" << std::endl;
  std::ifstream openFile;
  openFile.open("path", std::ifstream::in);

  std::cout << openFile << std::endl;

  openFile.close();
}

void documentAllFiles() { std::cout << "Documenting all files" << std::endl; }
