#include <iostream>
#include <malloc.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

void showHelp();
void documentFile(std::string path);
void documentAllFiles();
void addBannedWords();
void addBannedParts();

bool checkIfVectorContainsWord(std::vector<std::string> v, std::string word);
bool checkIfWordContainsPart(std::string word, std::string part);
bool checkIfContainsPartOfWordInVector(std::vector<std::string> v,
                                       std::string word);
std::string path;

std::vector<std::string> variables;
std::vector<std::string> functions;
std::vector<std::string> bannedWords;
std::vector<std::string> bannedParts;

struct Line {
  Line() {
    hasType = false;
    hasName = false;
    hasDef = false;
    hasBracket = false;
    hasCurlyBracket = false;
    hasSquareBracket = false;
    line = "";
  }
  bool hasType;
  bool hasName;
  bool hasDef;
  bool hasBracket;
  bool hasCurlyBracket;
  bool hasSquareBracket;
  std::string line;
  // not defining = 0; variable = 1; function = 2;
  int getLineType() {
    if (!hasType || hasName)
      return 0;
    if (hasType && hasName) {
      if (hasBracket) {
        return 2;
      } else
        return 1;
    }
  }
};

bool backup;
bool all;

int main(int argc, char const *argv[]) {
  backup = false;
  all = false;
  addBannedWords();
  addBannedParts();
  if (argc < 2) {
    std::cout << argv[0] << std::endl;
    showHelp();
    return 0;
  }
  for (int i = 0; i < argc; i++) {
    if (i == 1) {
      path = argv[i];
    }
    if (argv[i] == "-all")
      all = true;
    if (argv[i] == "-b")
      backup = true;
  }
  if (all)
    documentAllFiles();
  else
    documentFile(path);
  return 0;
}

void showHelp() { std::cout << "usage: " << std::endl; }

void documentFile(std::string path) {
  // allocation size and current position in line;
  printf("%s", "Start file reading: ");
  printf("%s\n", path.c_str());
  FILE *f;
  f = fopen(path.c_str(), "r+");

  int size = 1024, pos;
  int c;
  char *buffer = (char *)malloc(size);
  if (f != NULL) {
    bool caged = false;
    int cagedDepht = 0;
    int wordCount = 0;
    pos = 0;
    std::string word = "";
    std::string lastWord = "";
    std::string parameters = "";

    do {
      c = fgetc(f);
      if (c == EOF)
        continue;

      std::cout << c << ": " << (char)c << std::endl;

      bool shouldAdd = true;
      if (c == 32)
        if ((int)buffer[pos] == 32) {
          shouldAdd = false;
        }

      if (shouldAdd)
        buffer[pos++] = (char)c;
      if (pos == size - 1) {
        size *= 2;
        buffer = (char *)realloc(buffer, size);
      }
    } while (c != EOF);
    printf("%s\n", buffer);

    fclose(f);
    delete buffer;
  } else {
    printf("%s", "File doesn't exist : ");
    perror("open");
    free(buffer);
    return;
  }
}

bool checkIfVectorContainsWord(std::vector<std::string> v, std::string word) {
  std::vector<std::string>::iterator it = v.begin();
  while (it != v.end()) {
    if ((*it) == word)
      return true;
    it++;
  }
  return false;
}
bool checkIfWordContainsPart(std::string word, std::string part) {
  std::string::iterator it = word.begin();
  int count = 0;
  while (it != word.end()) {
    if ((*it) == part[0]) {
      std::string str = "";
      for (int i = 0; i < part.length(); i++) {
        str += word[count + i];
      }
      if (str == part)
        return true;
    }
    count++;
    it++;
  }
  return false;
}

bool checkIfContainsPartOfWordInVector(std::vector<std::string> v,
                                       std::string word) {
  std::vector<std::string>::iterator it = v.begin();
  while (it != v.end()) {
    if (checkIfWordContainsPart(word, (*it))) {
      return true;
    }
    it++;
  }
  return false;
}
void addBannedWords() {
  bannedWords.push_back("return");
  bannedWords.push_back("break");
  bannedWords.push_back("continue");
}
void addBannedParts() {
  bannedParts.push_back(".");
  bannedParts.push_back("++");
  bannedParts.push_back("--");
  bannedParts.push_back("}");
  bannedParts.push_back("{");
}

void documentAllFiles() { std::cout << "Documenting all files" << std::endl; }
