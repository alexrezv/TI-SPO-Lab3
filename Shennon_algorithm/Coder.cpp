//
// Created by alex on 11.11.16.
//

#include "Coder.h"



Coder::Coder(std::string alphabetFile, std::string probabilityFile) {
    //Инициализации
    setSourceAlphabet(std::move(alphabetFile));
    setP(std::move(probabilityFile));

    //Все буквы из алфавита записываются по убыванию вероятностей встречаемости в сообщениях.
    sortAlphabetAndP();
    Writer<std::string>::writeVector(&this->sourceAlphabet, "alphabet", ",");
    Writer<double>::writeVector(&this->p, "probabilityOfOccurrence", ",");

    setQ();   // Каждой букве ставится в соответствие кумулятивная вероятность по правилу: q1=0, q2=P1,...
    setL();
    setCode();
    Writer<std::string>::writeVector(&this->code, "code", ",");
}

void Coder::setSourceAlphabet(std::string filename) {
    this->sourceAlphabet = StringParser::getLineFromFile(std::move(filename));
}

std::vector<std::string> *Coder::getSourceAlphabet() {
    return &(this->sourceAlphabet);
}

void Coder::setP(std::string filename) {
    std::vector<std::string> strs = StringParser::getLineFromFile(std::move(filename));
    std::vector<double> nums;
    for (auto &str : strs) {
        nums.push_back(atof(str.c_str()));
    }
    this->p = nums;
}

std::vector<double> *Coder::getP() {
    return &(this->p);
}
//--
/*
 * Инициализации. Все буквы из алфавита записываются по убыванию
вероятностей встречаемости в сообщениях. Каждой букве ставится в
соответствие кумулятивная вероятность по правилу: q 1 0 , q 2 P 1 ,...,
*/
void Coder::sortAlphabetAndP() {
    for (int i = 0; i < this->p.size(); ++i) {
        for (int j = 0; j < this->p.size() - 1; ++j) {
            if (this->p.at(j) < this->p.at(j + 1)) {
                VectorUtil<double>::swapElements(&this->p, j, j + 1);
                VectorUtil<std::string>::swapElements(&this->sourceAlphabet, j, j + 1);
            }
        }
    }
}

//--
void Coder::setQ() {
    this->q.push_back(0);
    for (int i = 1; i < this->p.size(); ++i) {
        this->q.push_back(this->q.at(i - 1) + this->p.at(i - 1));
    }
}

std::vector<double> *Coder::getQ() {
    return &(this->q);
}

void Coder::setL() {
    for (double i : this->p) {
        l.push_back(std::fabs(std::logb(i)));
    }
}

std::vector<double> *Coder::getL() {
    return &(this->l);
}

void Coder::setCode() {
    for (int i = 0; i < this->q.size(); ++i) {
        this->code.push_back(this->decToBin(this->q.at(i), this->l.at(i)));
    }
}

std::vector<std::string> *Coder::getCode() {
    return &(this->code);
}

std::string Coder::decToBin(double num, int c) {
    double intpart;
    double buf = std::modf(num, &intpart);
    std::string cs;

    for (int i = 0; i < c; ++i) {
        buf = std::modf(buf * 2, &intpart);
        cs += std::to_string(intpart).substr(0, 1);
    }

    return cs;
}

std::vector<std::string> Coder::codeMessage(std::vector<std::string> message) {
    std::vector<std::string> encMsg = std::vector<std::string>();

    for (int i = 0; i < message.size(); ++i) {
        encMsg.emplace_back(codeWord(message.at(i)));
    }
    Writer<std::string>::writeVector(&encMsg, "codedMessage", "");
    setLastEncryptedMessage(encMsg);
    return encMsg;

}

std::string Coder::codeWord(std::string word) {
    std::string encWord;
    for (int i = 0; i < word.size(); i++) {
        for (int j = 0; j < this->sourceAlphabet.size(); ++j) {
            if (word.at(i) == this->sourceAlphabet.at(j).at(0)) {
                encWord += this->code.at(j);
            }
        }
    }
    return encWord;
}

void Coder::setLastEncryptedMessage(std::vector<std::string> lem) {
    this->lastEncryptedMessage = std::move(lem);
}

std::vector<std::string> Coder::getLastEncryptedMessage() {
    return this->lastEncryptedMessage;
}