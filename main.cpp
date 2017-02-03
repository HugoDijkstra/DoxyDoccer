#include <fstream>
#include <iostream>
#include <sstream>
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
std::string ss;

std::vector<std::string> variables;
std::vector<std::string> functions;
std::vector<std::string> bannedWords;
std::vector<std::string> bannedParts;

int main(int argc, char const *argv[]) {

  addBannedWords();
  addBannedParts();
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
    // get line
    while (getline(openFile, line)) {
      // inside ()?
      bool caged = false;
      int cagedDepht = 0;
      std::string lastWord = "";
      std::string word = "";

      std::string parameters;
      int wordCount;
      wordCount = 1;
      std::string::iterator it = line.begin();
      while (it != line.end()) {
        if ((*it) == '(') {
          caged = true;
          cagedDepht++;
          word += (*it);
          it++;
          continue;
        } else if ((*it) == ')') {
          cagedDepht--;
          if (checkIfWordContainsPart(parameters, " ") ||
              parameters.length() == 0)
            word += parameters;
          else
            break;
          word += (*it);
          it++;
          continue;
        }
        if (cagedDepht == 0) {
          if ((int)(*it) == 32) {
            if ((int)lastWord[0] != 0) {
              wordCount++;
            }
            // std::cout << word << std::endl;

            lastWord = word;
            word = "";
          } else if ((*it) == ';') {
            wordCount++;
            std::cout << wordCount << " : " << line << std::endl;
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
            break;
          } else
            word += (*it);
        } else {
          parameters += (*it);
        }
        it++;
      }
    }
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
    }

  } else {
    std::cout << "File not found" << std::endl;
    return;
  }
  openFile.close();
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
}

void documentAllFiles() { std::cout << "Documenting all files" << std::endl; }
