#ifndef CUSTOMGENERATOR_H
#define CUSTOMGENERATOR_H

#include <string>
#include <cstdint>

class HashGenerator {
private:
    static const int prekesKodai[440];

public:
    std::string generateHash(std::string input);
    std::string stringToHex(const std::string& input);
    static int weightedSum(std::string input);
    uint32_t varikliukas(uint32_t seed, int offset);
};

#endif