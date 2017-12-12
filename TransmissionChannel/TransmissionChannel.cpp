//
// Created by alex on 12/11/17.
//

#include "TransmissionChannel.h"

std::vector<std::string> TransmissionChannel::emulateTransmission(std::vector<std::string> message) {
    srand(time(0));
    for (int i = 0; i < message.size(); ++i) {
        int ifRand = 0 + rand() % 4;
        if (ifRand == 1) {
            message.at(i) = interfere(message.at(i));
        }
    }
    return message;
}

std::string TransmissionChannel::interfere(std::string word) {
    unsigned long symbolToChange = 0 + rand() % word.length();
    if (word.at(symbolToChange) == (char) '1') {
        word.at(symbolToChange) = (char) '0';
    } else {
        word.at(symbolToChange) = (char) '1';
    }
    return word;
}