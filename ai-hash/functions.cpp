#include "functions.h"
#include "SHA256.h"

namespace fs = std::filesystem;
std::string pasirinktiFaila(){
    while(true){
        try{
            fs::path folderPath = "../failaiHashavimui";
            if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
                throw std::runtime_error("failaiHashavimui nerastas");
            }
            
            std::vector<std::string> failuPav;
            for (const auto& entry : fs::directory_iterator(folderPath)) {
                if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                    failuPav.push_back(entry.path().filename().string());
                }
            }
            if (failuPav.empty()) {
                throw std::runtime_error("failaiHashavimui nera .txt failų");
            }
            std::cout << "Pasirinkite norimą failą:" << std::endl;
            for(std::size_t i = 0; i < failuPav.size(); ++i){
                std::cout << (i + 1) << "| " << failuPav[i] << std::endl;
            }
            
            int choice;
            std::cin >> choice;
            
            if (std::cin.fail() || choice < 1 || choice > static_cast<int>(failuPav.size())) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Neteisingas failo pasirinkimas");
            }
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string selectedFile = (folderPath / failuPav[static_cast<std::size_t>(choice - 1)]).string();
            return selectedFile;
            
        } catch (const std::runtime_error &e) {
            std::cout << e.what() << std::endl;
            continue;
        } catch (const std::exception &e) {
            std::cout << "Klaida: " << e.what() << std::endl;
            throw;
        }
    }
}

std::string failoNuskaitymas(){
    std::string fileName = pasirinktiFaila();
    std::ifstream f(fileName);
    
    if (!f.is_open()) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + fileName);
    }
    
    std::string tekstas;
    std::string eilute;
    fs::path filePath(fileName);

    if (filePath.filename() == "konstitucija.txt") {
        int eiluciuSkaicus = 789;
        int nuskaitymoEilutes;
        std::cout << "'Konstitucija.txt' nuskaitomas eilučių kiekis: ";
        std::cin >> nuskaitymoEilutes;

        int nuskaitytosEilutes = 0;
        while (getline(f, eilute) && nuskaitytosEilutes < nuskaitymoEilutes) {
            tekstas += eilute;
            nuskaitytosEilutes++;
            if (nuskaitytosEilutes < nuskaitymoEilutes && !f.eof()) {
                tekstas += '\n';}
        }
    } else {
        while (getline(f, eilute)) {
            tekstas += eilute;
            if (!f.eof()) {
                tekstas += '\n';
            }
        }
    }
    f.close();
    return tekstas;
}

std::string stringGeneratorius(int length, std::mt19937& gen) {
    static const char charset[] = 
        "abcdefghijklmnopqrstuvwxyząčęėįšųū"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZĄČĘĖĮŠŲŪ"
        "0123456789";
    static const int charsetSize = sizeof(charset) - 1;
    std::uniform_int_distribution<> dist(0, charsetSize - 1);
    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += charset[dist(gen)];
    }
    return result;
}



//lavinos testavimas AI IR SHA256

//Function to calculate the number of differing bits between two strings
int countBitDifference(const std::string& str1, const std::string& str2) {
    int diff = 0;
    for (size_t i = 0; i < str1.size() && i < str2.size(); ++i) {
        unsigned char x = str1[i] ^ str2[i];
        while (x) {
            diff += x & 1;
            x >>= 1;
        }
    }
    return diff;
}

// Function to calculate the number of differing hex characters between two strings
int countHexDifference(const std::string& str1, const std::string& str2) {
    int diff = 0;
    for (size_t i = 0; i < str1.size() && i < str2.size(); ++i) {
        if (str1[i] != str2[i]) {
            diff++;
        }
    }
    return diff;
}

void lavinosEfektas(int numPairs) {
    //HashGenerator hashGenerator;
    std::random_device rd;
    std::mt19937 gen(rd());
    const int STRING_LENGTH = 64;  
    std::uniform_int_distribution<> pos_dist(0, STRING_LENGTH - 1);
    std::uniform_int_distribution<int> char_dist('a', 'z'); 

    int totalBitDiff = 0, totalHexDiff = 0;
    int minBitDiff = std::numeric_limits<int>::max(), maxBitDiff = 0;
    int minHexDiff = std::numeric_limits<int>::max(), maxHexDiff = 0;
    int zeroBitDiffs = 0, zeroHexDiffs = 0;

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numPairs; ++i) {
        std::string original;
        original.reserve(STRING_LENGTH);
        for (int j = 0; j < STRING_LENGTH; ++j) {
            original += static_cast<char>(char_dist(gen));
        }
        

        std::string modified = original;
        int pos = pos_dist(gen);
        char newChar;
        do {
            newChar = static_cast<char>(char_dist(gen));
        } while (newChar == original[pos]);
        modified[pos] = newChar;

        //AI
        std::string hash1 = CustomHash::hash(original); //hashGenerator.generateHash(original);
        std::string hash2 = CustomHash::hash(modified); //hashGenerator.generateHash(modified); 


        if (hash1.length() != hash2.length()) {
            std::cerr << "Klaida: Skirtingi hash ilgiai! " << hash1.length() << " vs " << hash2.length() << std::endl;
            continue;
        }

        int bitDiff = countBitDifference(hash1, hash2);
        int hexDiff = countHexDifference(hash1, hash2);


        if (bitDiff == 0) zeroBitDiffs++;
        if (hexDiff == 0) zeroHexDiffs++;


        totalBitDiff += bitDiff;
        totalHexDiff += hexDiff;
        minBitDiff = std::min(minBitDiff, bitDiff);
        maxBitDiff = std::max(maxBitDiff, bitDiff);
        minHexDiff = std::min(minHexDiff, hexDiff);
        maxHexDiff = std::max(maxHexDiff, hexDiff);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;

    double avgBitDiff = static_cast<double>(totalBitDiff) / numPairs;
    double avgHexDiff = static_cast<double>(totalHexDiff) / numPairs;
    double bitDiffPercentage = (avgBitDiff / (CustomHash::hash("test").length() * 8)) * 100.0;  
    double hexDiffPercentage = (avgHexDiff / static_cast<double>(CustomHash::hash("test").length())) * 100.0;

    size_t hashBitLength = CustomHash::hash("test").length() * 4; // Each hex char = 4 bits
    
    std::cout << "\n=== Lavinos efekto testavimo rezultatai AI ===" << std::endl;
    std::cout << "Iš viso išbandyta porų: " << numPairs << std::endl;
    std::cout << "Testo trukmė: " << duration.count() << " sekundžių" << std::endl;
    
    std::cout << "\nBitų lygmenyje (hash ilgis: " << hashBitLength << " bitai):" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  Minimalus skirtumas: " << minBitDiff << " bitai (" << (minBitDiff * 100.0 / hashBitLength) << "%)" << std::endl;
    std::cout << "  Maksimalus skirtumas: " << maxBitDiff << " bitai (" << (maxBitDiff * 100.0 / hashBitLength) << "%)" << std::endl;
    std::cout << "  Vidutinis skirtumas: " << avgBitDiff << " bitai (" << bitDiffPercentage << "% hash'o ilgio)" << std::endl;
    std::cout << "  Porų be skirtumų: " << zeroBitDiffs << " (" << (zeroBitDiffs * 100.0 / numPairs) << "%)" << std::endl;
    
    std::cout << "\nHex simbolių lygmenyje:" << std::endl;
    std::cout << "  Minimalus skirtumas: " << minHexDiff << " simboliai (" << (minHexDiff * 100.0 / (hashBitLength/4)) << "%)" << std::endl;
    std::cout << "  Maksimalus skirtumas: " << maxHexDiff << " simboliai (" << (maxHexDiff * 100.0 / (hashBitLength/4)) << "%)" << std::endl;
    std::cout << "  Vidutinis skirtumas: " << avgHexDiff << " simboliai (" << hexDiffPercentage << "% hash'o ilgio)" << std::endl;
    std::cout << "  Porų be skirtumų: " << zeroHexDiffs << " (" << (zeroHexDiffs * 100.0 / numPairs) << "%)" << std::endl;

}


void lavinosEfektasSHA(int numPairs) {
    
    SHA256 sha1;
    SHA256 sha;
    std::random_device rd;
    std::mt19937 gen(rd());
    const int STRING_LENGTH = 64;  
    std::uniform_int_distribution<> pos_dist(0, STRING_LENGTH - 1);
    std::uniform_int_distribution<int> char_dist('a', 'z'); 

    int totalBitDiff = 0, totalHexDiff = 0;
    int minBitDiff = std::numeric_limits<int>::max(), maxBitDiff = 0;
    int minHexDiff = std::numeric_limits<int>::max(), maxHexDiff = 0;
    int zeroBitDiffs = 0, zeroHexDiffs = 0;

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numPairs; ++i) {
        std::string original;
        original.reserve(STRING_LENGTH);
        for (int j = 0; j < STRING_LENGTH; ++j) {
            original += static_cast<char>(char_dist(gen));
        }
        
        std::string modified = original;
        int pos = pos_dist(gen);
        char newChar;
        do {
            newChar = static_cast<char>(char_dist(gen));
        } while (newChar == original[pos]);
        modified[pos] = newChar;

        sha1.update(original);
        sha.update(modified);

        std::array<uint8_t, 32> digest1 = sha1.digest();
        std::array<uint8_t, 32> digest = sha.digest();

        std::string hash1 = SHA256::toString(digest1);  //hashGenerator.generateHash(original); CustomHash::hash(original);
        std::string hash2 = SHA256::toString(digest); //hashGenerator.generateHash(modified); CustomHash::hash(modified);


        if (hash1.length() != hash2.length()) {
            std::cerr << "Klaida: Skirtingi hash ilgiai! " << hash1.length() << " vs " << hash2.length() << std::endl;
            continue;
        }

        int bitDiff = countBitDifference(hash1, hash2);
        int hexDiff = countHexDifference(hash1, hash2);


        if (bitDiff == 0) zeroBitDiffs++;
        if (hexDiff == 0) zeroHexDiffs++;


        totalBitDiff += bitDiff;
        totalHexDiff += hexDiff;
        minBitDiff = std::min(minBitDiff, bitDiff);
        maxBitDiff = std::max(maxBitDiff, bitDiff);
        minHexDiff = std::min(minHexDiff, hexDiff);
        maxHexDiff = std::max(maxHexDiff, hexDiff);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;

    SHA256 sha3;
    sha.update("test");
    std::array<uint8_t, 32> digest3 = sha3.digest();
    std::string forSizeOfHash = SHA256::toString(digest3);



    double avgBitDiff = static_cast<double>(totalBitDiff) / numPairs;
    double avgHexDiff = static_cast<double>(totalHexDiff) / numPairs;
    double bitDiffPercentage = (avgBitDiff / (forSizeOfHash.length() * 8)) * 100.0;
    double hexDiffPercentage = (avgHexDiff / static_cast<double>(forSizeOfHash.length())) * 100.0;

    size_t hashBitLength = forSizeOfHash.length() * 4; // Each hex char = 4 bits
    
    std::cout << "\n=== Lavinos efekto testavimo rezultatai SHA ===" << std::endl;
    std::cout << "Iš viso išbandyta porų: " << numPairs << std::endl;
    std::cout << "Testo trukmė: " << duration.count() << " sekundžių" << std::endl;
    
    std::cout << "\nBitų lygmenyje (hash ilgis: " << hashBitLength << " bitai):" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  Minimalus skirtumas: " << minBitDiff << " bitai (" << (minBitDiff * 100.0 / hashBitLength) << "%)" << std::endl;
    std::cout << "  Maksimalus skirtumas: " << maxBitDiff << " bitai (" << (maxBitDiff * 100.0 / hashBitLength) << "%)" << std::endl;
    std::cout << "  Vidutinis skirtumas: " << avgBitDiff << " bitai (" << bitDiffPercentage << "% hash'o ilgio)" << std::endl;
    std::cout << "  Porų be skirtumų: " << zeroBitDiffs << " (" << (zeroBitDiffs * 100.0 / numPairs) << "%)" << std::endl;
    
    std::cout << "\nHex simbolių lygmenyje:" << std::endl;
    std::cout << "  Minimalus skirtumas: " << minHexDiff << " simboliai (" << (minHexDiff * 100.0 / (hashBitLength/4)) << "%)" << std::endl;
    std::cout << "  Maksimalus skirtumas: " << maxHexDiff << " simboliai (" << (maxHexDiff * 100.0 / (hashBitLength/4)) << "%)" << std::endl;
    std::cout << "  Vidutinis skirtumas: " << avgHexDiff << " simboliai (" << hexDiffPercentage << "% hash'o ilgio)" << std::endl;
    std::cout << "  Porų be skirtumų: " << zeroHexDiffs << " (" << (zeroHexDiffs * 100.0 / numPairs) << "%)" << std::endl;

}















void kolizijos() {
    int numPairs = 1000000;
    int length = 10;
    std::cout << "String vienos poros simbolių skaičius: " << length << std::endl;
    
    //HashGenerator hash;
    std::random_device rd;
    std::mt19937 gen(rd());
    
    auto startTime = std::chrono::high_resolution_clock::now();
    int pairCollisions = 0;
    for (int i = 0; i < numPairs; ++i) {
        std::string str1 = stringGeneratorius(length, gen);
        std::string str2 = stringGeneratorius(length, gen);
        
        std::string hash1 = CustomHash::hash(str1);
        std::string hash2 = CustomHash::hash(str2);
        
        if (hash1 == hash2) {
            ++pairCollisions;}
    }
    auto endTime = std::chrono::high_resolution_clock::now();


    //SHA256
    SHA256 sha1;
    SHA256 sha2;
    auto startTimeSHA = std::chrono::high_resolution_clock::now();
    int pairCollisionsSHA = 0;
    for (int i = 0; i < numPairs; ++i) {
        
        sha1.update(stringGeneratorius(length, gen));
        sha2.update(stringGeneratorius(length, gen));

        std::array<uint8_t, 32> digest1 = sha1.digest();
        std::array<uint8_t, 32> digest2 = sha2.digest();

        std::string hash1 = SHA256::toString(digest1);
        std::string hash2 = SHA256::toString(digest2);
        
        if (hash1 == hash2) {
            ++pairCollisionsSHA;}
    }

    auto endTimeSHA = std::chrono::high_resolution_clock::now();

    std::cout << "Porų skaičius: " << numPairs << std::endl;

    std::cout << "Porų kolizijų skaičius AI: " << pairCollisions << std::endl;
    std::cout<< "Porų kolizijų skaičius SHA: " << pairCollisionsSHA << std::endl;

    double perPairRateAI = static_cast<double>(pairCollisions) / numPairs * 100.0;
    double perPairRateSHA = static_cast<double>(pairCollisionsSHA) / numPairs * 100.0;

    std::cout << "Porų kolizijų tikimybė AI: " << std::fixed << std::setprecision(6)<< perPairRateAI << " %" << std::endl;
    std::cout << "Porų kolizijų tikimybė SHA: " << std::fixed << std::setprecision(6)<< perPairRateSHA << " %" << std::endl;
    
    std::chrono::duration<double> diff = endTime - startTime;
    std::chrono::duration<double> diffSHA = endTimeSHA - startTimeSHA;
    std::cout << "LaikasAI: " << diff.count() << " s" << std::endl;
    std::cout << "LaikasSHA: " << diffSHA.count() << " s" << std::endl;
}
