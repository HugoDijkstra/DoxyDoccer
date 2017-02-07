#include <iostream>
#include <malloc.h>
#include <map>
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
<<<<<<< HEAD
=======
  std::map<int, Line *> lines;
  int size = 1024, pos;
  int c;
  char *buffer = (char *)malloc(size);
>>>>>>> e3e570a... Added -std=c++11 to makefile and adding strings to lines
  if (f != NULL) {
    int size = 1024, pos;
    int c;
    char *buffer = (char *)malloc(size);
    bool caged = false;
    bool sentenceStart = false;
    int cagedDepht = 0;
    int wordCount = 0;
    int lineCount;
    pos = 0;
    std::string word = "";
    std::string lastWord = "";
    std::string parameters = "";
<<<<<<< HEAD
    do {
      c = fgetc(f);
=======
    Line *l = new Line();

    do {
      c = fgetc(f);
      if (c == EOF)
        continue;

      if (c != 32)
        sentenceStart = true;
      if (!sentenceStart)
        continue;
>>>>>>> e3e570a... Added -std=c++11 to makefile and adding strings to lines
      bool shouldAdd = true;

<<<<<<< HEAD
      if (c == '(') {
        caged = true;
        cagedDepht++;
        word += c;
        buffer[pos++] = c;
        continue;
      } else if (c == ')') {
        cagedDepht--;
        if (checkIfWordContainsPart(parameters, " ") ||
            parameters.length() == 0)
          word += parameters;
        buffer[pos++] = c;
      }
      if (cagedDepht == 0) {
        if (c == 32) {
          if (buffer[pos] != 0) {
            wordCount++;
          }
          // std::cout << word << std::endl;

          lastWord = word;
          word = "";
        } else if (c == ';') {
          wordCount++;
          if (wordCount == 2)
            if (!checkIfVectorContainsWord(variables, word) &&
                !checkIfVectorContainsWord(functions, word) &&
                !checkIfVectorContainsWord(bannedWords, lastWord) &&
                !checkIfVectorContainsWord(bannedWords, word) &&
                !checkIfContainsPartOfWordInVector(bannedParts, word) &&
                !checkIfContainsPartOfWordInVector(bannedParts, lastWord)) {
              if (checkIfWordContainsPart(word, "(")) {
                functions.push_back(word);
              } else
                variables.push_back(word);
            }
        } else
          word += c;
      } else {
        parameters += c;
      }
      if (c != EOF) {
        buffer[pos++] = (char)c;
      }
    } while (c != EOF);
    printf("%s\n", buffer);
    // printf("%s", buffer);
    std::cout << "\nVariables:" << std::endl;
    std::vector<std::string>::iterator it = variables.begin();
    while (it != variables.end()) {
      std::cout << (*it) << std::endl;
      it++;
    }
    std::cout << "\nFunctions:" << std::endl;
    std::vector<std::string>::iterator jt = functions.begin();
    while (jt != functions.end()) {
      std::cout << (*jt) << std::endl;
      jt++;
=======
      if (c == '\n') {
        lines.emplace(lineCount++, l);
        l = new Line();
        sentenceStart = false;
      }
      if (shouldAdd && sentenceStart) {
        buffer[pos++] = (char)c;
        l->line += (char)c;
        printf("%c\n", c);
      }
      if (pos == size - 1) {
        size *= 2;
        buffer = (char *)realloc(buffer, size);
      }
    } while (c != EOF);

    std::map<int, Line *>::iterator it;
    int curline = 0;
    it = lines.find(curline);
    while (curline <= lines.size()) {
      std::cout << it->second->line << std::endl;
      it = lines.find(curline++);
>>>>>>> e3e570a... Added -std=c++11 to makefile and adding strings to lines
    }
    fclose(f);
    free(buffer);
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
