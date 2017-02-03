#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void showHelp();
void documentFile(std::string path);
void documentAllFiles();
bool checkIfContainsWord(std::vector<std::string> v, std::string word);

std::string ss;

std::vector<std::string> variables;
std::vector<std::string> functions;

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
      std::string lastWord = "";
      std::string word = "";
      int wordCount = 0;
      std::string::iterator it = line.begin();
      while (it != line.end()) {
        if ((*it) == ' ') {
          wordCount++;
          // std::cout << word << std::endl;
          lastWord = word;
          word = "";
        }
        if ((*it) == ';') {
          if (!checkIfContainsWord(variables, word)) {
            variables.push_back(word);
          }
        } else
          word += (*it);
        it++;
      }
    }

  } else {
    std::cout << "File not found" << std::endl;
    return;
  }
  openFile.close();
}

bool checkIfContainsWord(std::vector<std::string> v, std::string word) {
  std::vector<std::string>::iterator it = v.begin();
  while (it != v.end()) {
    if ((*it) == word)
      return true;
    it++;
  }
  return false;
}
void documentAllFiles() { std::cout << "Documenting all files" << std::endl; }
