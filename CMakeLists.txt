cmake_minimum_required(VERSION 3.8)
project(Lab3)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp
        Shennon_algorithm/Coder.cpp
        Shennon_algorithm/Coder.h
        Shennon_algorithm/Decoder.cpp
        Shennon_algorithm/Decoder.h

        util/StringParser/StringParser.cpp
        util/StringParser/StringParser.h

        util/VectorUtil.h
        util/Reader.h
        util/Writer.h

        TransmissionChannel/TransmissionChannel.cpp
        TransmissionChannel/TransmissionChannel.h

        ErrorDetector/ErrorDetector.cpp
        ErrorDetector/ErrorDetector.h)
add_executable(Lab3 ${SOURCE_FILES})