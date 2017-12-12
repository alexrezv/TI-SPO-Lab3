//
// Created by alex on 05.12.16.
//

#include <cstring>
#include <utility>
#include "StringParser.h"

StringParser::StringParser(std::string filename) {
    this->setSourceAlphabet(std::move(filename));
}

void StringParser::setSourceAlphabet(std::string filename) {
    this->sourceAlphabet = getLineFromFile(std::move(filename));
}

std::vector<std::string> StringParser::getLineFromFile(std::string filename) {
    std::vector<std::string> result;

    //open file
    std::ifstream f_alphabet(filename);
    std::istream &str = f_alphabet;
    //get line from file
    std::string line;
    getline(str, line);
    //convert line to stream
    std::stringstream lineStream(line);
    std::string cell;

    while (getline(lineStream, cell, ',')) {
        result.push_back(cell);
    }

    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty()) {
        // If there was a trailing comma then add an empty element.
        result.emplace_back("");
    }

    return result;
}

std::vector<std::string> StringParser::getSourceAlphabet() {
    return this->sourceAlphabet;
}

/**
 * @returns vector of strings(symbols) in the same order as they appear in message */
std::vector<std::string> StringParser::parseMessage(std::string message) {
    std::vector<std::string> words;

    //need to tokenize string by whitespace into vector<string>
    std::istringstream iss(message);
    while (iss) {
        std::string subs;
        iss >> subs;
        words.push_back(subs);
    }
    words.pop_back();


    //check if there is a symbol not presented in alphabet -> delete word from vector
    std::vector<int> wordsForErase;
    for (int i = 0; i < words.size(); i++) {
        if ( !ifValidWord(words.at(i)) ) {
            wordsForErase.emplace_back(i);
        }
    }
    for (int j = 0; j < wordsForErase.size(); ++j) {
        words.erase(words.begin()+wordsForErase.at(j));
    }

    if (words.size() == 0) {
        std::cerr << "NO VALID WORDS IN MESSAGE" << std::endl;
        exit(1);
    }

    return words;
}

/*std::vector<std::string> StringParser::splitString(std::string message) {
    std::istringstream iss(message);

    while (iss) {
        std::string subs;
        iss >> subs;
        std::cout << "Substring: " << subs << std::endl;
    }
}*/

unsigned long StringParser::getMaxWordLength() {
    unsigned long currentMax = 0;
    for (int i = 0; i < this->sourceAlphabet.size(); ++i) {
        if (currentMax < this->sourceAlphabet[i].size()) {
            currentMax = this->sourceAlphabet[i].size();
        }
    }
    return currentMax;
}

std::string StringParser::getFirstLongestValidWord(std::string string) {
    std::string word;

    unsigned long maxWordLength = getMaxWordLength();
    for (unsigned long i = 0; i < 3; ++i) {
        word = string.substr(0, maxWordLength - i);
        if (ifValidWord(word)) break;
    }

    return word;
}

bool StringParser::ifValidWord(std::string word) {
    bool validation = false;
    int v = 0;
    for (int i = 0; i < word.length(); ++i) {
        for (int j = 0; j < this->sourceAlphabet.size(); ++j) {
            if (word.at(i) == sourceAlphabet.at(j).at(0)) {
                v++;
            }
        }
    }
    if (v == word.length()) {
        validation = true;
    }
    return validation;
}
