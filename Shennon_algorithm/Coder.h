//
// Created by alex on 11.11.16.
//

#ifndef LAB2_CODER_H
#define LAB2_CODER_H

#include <vector>
#include <string>
#include <cmath>
#include <utility>
#include "../util/StringParser/StringParser.h"
#include "../util/VectorUtil.h"
#include "../util/Writer.h"


class Coder {
private:
    std::vector<std::string> sourceAlphabet;
    std::vector<double> p, q, l;
    std::vector<std::string> code;
    std::vector<std::string> lastEncryptedMessage;

    void setSourceAlphabet(std::string filename);

    void setP(std::string filename); //Probability
    void setQ();

    void sortAlphabetAndP();

    void setL();

    void setCode();

    void setLastEncryptedMessage(std::vector<std::string>);

    std::string decToBin(double, int);

    std::string codeWord(std::string);

public:
    Coder(std::string, std::string);

    std::vector<std::string> *getSourceAlphabet();

    std::vector<double> *getP();

    std::vector<double> *getQ();

    std::vector<double> *getL();

    std::vector<std::string> *getCode();

    std::vector<std::string> getLastEncryptedMessage();

    std::vector<std::string> codeMessage(std::vector<std::string> message);

};


#endif //LAB2_CODER_H
