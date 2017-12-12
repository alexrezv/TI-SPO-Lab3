//
// Created by alex on 12/12/17.
//

#ifndef LAB3_ERRORDETECTOR_H
#define LAB3_ERRORDETECTOR_H

#include <vector>
#include <string>

class ErrorDetector {
public:
    static std::vector<std::string> addCheckBit(std::vector<std::string>);
    static std::string addCheckBit(std::string);
    static std::vector<std::string> checkError(std::vector<std::string>);
    static std::string checkError(std::string);
};


#endif //LAB3_ERRORDETECTOR_H
