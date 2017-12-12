//
// Created by alex on 12/11/17.
//

#ifndef LAB3_TRANSMISSIONCHANNEL_H
#define LAB3_TRANSMISSIONCHANNEL_H

#include <vector>
#include <cstring>
#include <cmath>
#include <random>

class TransmissionChannel {
public:
    static std::vector<std::string> emulateTransmission(std::vector<std::string>);

private:
    static std::string interfere(std::string);
};


#endif //LAB3_TRANSMISSIONCHANNEL_H
