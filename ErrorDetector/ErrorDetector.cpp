//
// Created by alex on 12/12/17.
//

#include "ErrorDetector.h"

std::vector<std::string> ErrorDetector::addCheckBit(std::vector<std::string> message) {
    std::vector<std::string> messageWithCB;
    for (std::string word : message) {
        messageWithCB.emplace_back(addCheckBit(word));
    }
    return messageWithCB;
}

std::string ErrorDetector::addCheckBit(std::string word) {
    unsigned int bits = 0;
    for (int i = 0; i < word.length(); ++i) {
        if (word.at(i) == '1') {
            bits++;
        }
    }
    if (bits%2 == 0) {
        word.resize(word.length()+1,'1');
    } else {
        word.resize(word.length()+1,'0');
    }
    return word;
}

std::vector<std::string> ErrorDetector::checkError(std::vector<std::string> message) {
    std::vector<std::string> verdicts;
    for (std::string word : message) {
        verdicts.emplace_back(checkError(word));
    }
    return verdicts;
}

std::string ErrorDetector::checkError(std::string word) {
    unsigned int bits = 0;
    std::string verdict;
    for (int i = 0; i < word.length()-1; ++i) {
        if (word.at(i) == '1') {
            bits++;
        }
    }
    if (bits%2 == 0 && word.at(word.length()-1) == '1') {
        verdict = "Correct";
    } else if (bits%2 == 1 && word.at(word.length()-1) == '0'){
        verdict = "Correct";
    } else {
        verdict = "Error";
    }
    return verdict;
}