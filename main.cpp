#include <iostream>
#include <vector>
#include "util/Reader.h"
#include "Shennon_algorithm/Coder.h"
#include "TransmissionChannel/TransmissionChannel.h"
#include "ErrorDetector/ErrorDetector.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::string filename = "./message";
    std::vector<std::string> message;

    StringParser sp = StringParser("alphabet");

    message = sp.parseMessage(Reader::readMessage(filename));
    std::cout << "┌──────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << "│  Input message is: ";
    VectorUtil<std::string>::printVector(&message, " , ");
    std::cout << "├──────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    Coder shC = Coder("alphabet", "probabilityOfOccurrence");
    std::cout << "│  Source alphabet: ";
    VectorUtil<std::string>::printVector(shC.getSourceAlphabet(), " , ");
    std::cout << "│  Probability: ";
    VectorUtil<double>::printVector(shC.getP(), " , ");
    std::cout << "│  Computed code: ";
    VectorUtil<std::string>::printVector(shC.getCode(), " , ");
    std::cout << "├──────────────────────────────────────────────────────────────────────────────────────" << std::endl;

    std::vector<std::string> codedMessage = shC.codeMessage(message);
    std::cout << "│  Coded message is:   ";
    VectorUtil<std::string>::printVector(&codedMessage, "\t");
    std::cout << "├──────────────────────────────────────────────────────────────────────────────────────" << std::endl;

    std::vector<std::string> codedMessageWithCB = ErrorDetector::addCheckBit(codedMessage);
    std::cout << "│  With check bits:    ";
    VectorUtil<std::string>::printVector(&codedMessageWithCB, "\t");
    std::cout << "├──────────────────────────────────────────────────────────────────────────────────────" << std::endl;

    std::vector<std::string> transmittedMessage = TransmissionChannel::emulateTransmission(codedMessageWithCB);
    std::cout << "│  After transmission: ";
    VectorUtil<std::string>::printVector(&transmittedMessage, "\t");
    std::cout << "├──────────────────────────────────────────────────────────────────────────────────────" << std::endl;

    std::vector<std::string> verdicts = ErrorDetector::checkError(transmittedMessage);
    std::cout << "│  After transmission: ";
    VectorUtil<std::string>::printVector(&verdicts, "\t");
    std::cout << "└──────────────────────────────────────────────────────────────────────────────────────" << std::endl;

    return 0;
}