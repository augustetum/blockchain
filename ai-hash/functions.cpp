#include "functions.h"
#include "SHA256.h"

std::string pasirinktiFaila(){
    while(true){
        try{
            system("ls *.txt ../failaiHashavimui/*.txt 2>/dev/null > temp.txt");    
            //system("for /r %A in (*.txt) do @echo %~nxA >> temp.txt"); //windowsam
            std::ifstream tempFail("temp.txt");
            std::vector<std::string> failuPav;
     
            std::string failoPav;
            while(std::getline(tempFail, failoPav)){
                failuPav.push_back(failoPav);

            }
            tempFail.close();
            system("rm temp.txt"); 
            //system("del temp.txt"); windowsam
            std::string fail;

            std::cout << "Pasirinkite norimą failą" << std::endl;
            for(std::size_t i = 0; i < failuPav.size(); ++i){
                std::cout << (i + 1) << "| " << failuPav[i] << std::endl;
            }
            int choice;
            std::cin >> choice;
            if (choice < 1 || choice > static_cast<int>(failuPav.size())) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Neteisingas failo pasirinkimas");
            } else {
                 fail = failuPav[static_cast<std::size_t>(choice - 1)];
            }
            return fail;
            break;
        } catch (const std::runtime_error &e) {
            std::cout << e.what() << std::endl;
            continue;
        } catch (const char* e){
            std::cout << e << std::endl;
            throw;
        }
    }
}


std::string failoNuskaitymas(){
    std::string fileName = pasirinktiFaila();
    std::ifstream f(fileName);
    std::string tekstas;
    std::string eilute;
    while (getline(f, eilute))
    {
        tekstas += eilute;
        if (!f.eof()) { //kad neimtu newlines
            tekstas += '\n';
        }
    }
    f.close();
    return tekstas;
}


/*
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
*/

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
    std::random_device rd;
    std::mt19937 gen(rd());
    const int STRING_LENGTH = 64;  
    std::uniform_int_distribution<> pos_dist(0, STRING_LENGTH - 1);
    std::uniform_int_distribution<int> char_dist('a', 'z'); 

    int totalBitDiff = 0, totalHexDiff = 0;
    int minBitDiff = std::numeric_limits<int>::max(), maxBitDiff = 0;
    int minHexDiff = std::numeric_limits<int>::max(), maxHexDiff = 0;
    int zeroBitDiffs = 0, zeroHexDiffs = 0;
    
    const size_t HASH_BIT_LENGTH = 256; 
    const size_t HASH_HEX_LENGTH = 64;   
    const double EXPECTED_BIT_DIFF = HASH_BIT_LENGTH / 2.0; 
    const double EXPECTED_HEX_DIFF = HASH_HEX_LENGTH * 0.5;
    

    CustomHash::hash("apsilimas");
    
    auto startTime = std::chrono::high_resolution_clock::now();
    auto lastPrintTime = startTime;
    
    std::cout << "Pradedamas lavinos efekto testas su " << numPairs << " porų..." << std::endl;

    for (int i = 0; i < numPairs; ++i) {
        // Generate original string
        std::string original(STRING_LENGTH, ' ');
        for (int j = 0; j < STRING_LENGTH; ++j) {
            original[j] = static_cast<char>(char_dist(gen));
        }
        
        // Create modified string (1-bit difference)
        std::string modified = original;
        int pos = pos_dist(gen);
        char newChar;
        do {
            newChar = static_cast<char>(char_dist(gen));
        } while (newChar == original[pos]);
        modified[pos] = newChar;

        std::string hash1 = CustomHash::hash(original);
        std::string hash2 = CustomHash::hash(modified);

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
        

        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = currentTime - lastPrintTime;
        if ((i + 1) % 10000 == 0 || elapsed.count() >= 5.0) {
            double progress = (i + 1) * 100.0 / numPairs;
            std::cout << "Apdorota " << (i + 1) << " / " << numPairs 
                      << " (" << std::fixed << std::setprecision(1) << progress << "%)..." << std::endl;
            lastPrintTime = currentTime;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    
    // Calculate statistics
    double avgBitDiff = static_cast<double>(totalBitDiff) / numPairs;
    double avgHexDiff = static_cast<double>(totalHexDiff) / numPairs;
    double bitDiffPercentage = (avgBitDiff / HASH_BIT_LENGTH) * 100.0;
    double hexDiffPercentage = (avgHexDiff / HASH_HEX_LENGTH) * 100.0;
    
    // Calculate how close we are to ideal avalanche effect (50%)
    double bitAvalancheQuality = 100.0 - std::abs(bitDiffPercentage - 50.0) * 2.0;
    double hexAvalancheQuality = 100.0 - std::abs(hexDiffPercentage - 50.0) * 2.0;
    
    // Output results
    std::cout << "\n=== Lavinos efekto testavimo rezultatai (CustomHash) ===" << std::endl;
    std::cout << "Iš viso išbandyta porų: " << numPairs << std::endl;
    std::cout << "Testo trukmė: " << std::fixed << std::setprecision(2) << duration.count() << " s" << std::endl;
    std::cout << "Vidutinis greitis: " << std::setprecision(0) << (numPairs / duration.count()) << " porų/s" << std::endl;
    std::cout << "Hash ilgis: " << HASH_HEX_LENGTH << " simboliai (" << HASH_BIT_LENGTH << " bitai)" << std::endl;
    
    std::cout << "\n--- Bitų lygmenyje ---" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  Minimalus skirtumas: " << minBitDiff << "/" << HASH_BIT_LENGTH 
              << " bitų (" << (minBitDiff * 100.0 / HASH_BIT_LENGTH) << "%)" << std::endl;
    std::cout << "  Maksimalus skirtumas: " << maxBitDiff << "/" << HASH_BIT_LENGTH 
              << " bitų (" << (maxBitDiff * 100.0 / HASH_BIT_LENGTH) << "%)" << std::endl;
    std::cout << "  Vidutinis skirtumas: " << std::setprecision(2) << avgBitDiff 
              << " bitų (" << bitDiffPercentage << "%)" << std::endl;
    std::cout << "  Idealus lavinos efektas: 50% (" << EXPECTED_BIT_DIFF << " bitų)" << std::endl;
    std::cout << "  Kokybė: " << std::setprecision(1) << bitAvalancheQuality << "% (100% = idealus lavinos efektas)" << std::endl;
    std::cout << "  Kolizijos (0 bitų skirtumas): " << zeroBitDiffs << " ("
              << std::setprecision(4) << (zeroBitDiffs * 100.0 / numPairs) << "%)" << std::endl;
    
    std::cout << "\n--- Hex simbolių lygmenyje ---" << std::endl;
    std::cout << "  Minimalus skirtumas: " << minHexDiff << "/" << HASH_HEX_LENGTH 
              << " simbolių (" << (minHexDiff * 100.0 / HASH_HEX_LENGTH) << "%)" << std::endl;
    std::cout << "  Maksimalus skirtumas: " << maxHexDiff << "/" << HASH_HEX_LENGTH 
              << " simbolių (" << (maxHexDiff * 100.0 / HASH_HEX_LENGTH) << "%)" << std::endl;
    std::cout << "  Vidutinis skirtumas: " << std::setprecision(2) << avgHexDiff 
              << " simbolių (" << hexDiffPercentage << "%)" << std::endl;
    std::cout << "  Kokybė: " << std::setprecision(1) << hexAvalancheQuality << "% (100% = idealus lavinos efektas)" << std::endl;
    std::cout << "  Kolizijos (0 simbolių skirtumas): " << zeroHexDiffs << " ("
              << std::setprecision(4) << (zeroHexDiffs * 100.0 / numPairs) << "%)" << std::endl;
    
    std::cout << "\n=== Išvados ===" << std::endl;
    if (bitAvalancheQuality > 95.0) {
        std::cout << "Puikus lavinos efektas! Vidutinis bitų skirtumas labai artimas 50%." << std::endl;
    } else if (bitAvalancheQuality > 90.0) {
        std::cout << "Geras lavinos efektas. Vidutinis bitų skirtumas artimas 50%." << std::endl;
    } else if (bitAvalancheQuality > 80.0) {
        std::cout << "Vidutiniškas lavinos efektas. Yra vietos tobulėjimui." << std::endl;
    } else {
        std::cout << "Silpnas lavinos efektas. Rekomenduojama patobulinti maišos funkciją." << std::endl;
    }

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

void testHashPerformance() {
    const std::string filename = "../failaiHashavimui/konstitucija.txt";
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << filename << std::endl;
        return;
    }
    
    // Read all lines from the file
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    file.close();
    
    if (lines.empty()) {
        std::cerr << "Failas tusčias arba neturi eilučių" << std::endl;
        return;
    }
    
    std::cout << "=== Hash'avimo efektyvumo testas (CustomHash) ===" << std::endl;
    std::cout << "Failas: " << filename << std::endl;
    std::cout << "Iš viso eilučių: " << lines.size() << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    std::cout << std::setw(10) << "Eilučių" << std::setw(20) << "Laikas (s)" 
              << std::setw(20) << "Vid. laikas (ms)" << std::setw(20) << "Hash'as" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    
    // Warm-up
    CustomHash::hash("warmup");
    
    for (int chunkSize = 1; chunkSize <= lines.size(); ) {
        std::string input;
        for (int i = 0; i < chunkSize; ++i) {
            input += lines[i] + "\n";
        }

        auto start = std::chrono::high_resolution_clock::now();
        std::string hash = CustomHash::hash(input);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        double avgTimePerHash = duration.count() * 1000.0; // Convert to milliseconds

        std::cout << std::setw(10) << chunkSize
                  << std::setw(20) << std::scientific << std::setprecision(6) << duration.count()
                  << std::setw(20) << std::fixed << std::setprecision(6) << avgTimePerHash
                  << std::setw(20) << hash.substr(0, 12) << "..." << std::endl;

        if (chunkSize >= lines.size()) {
            break;
        }

        chunkSize *= 2;
        if (chunkSize > lines.size()) {
            chunkSize = lines.size();
        }
    }
    
    std::cout << std::string(70, '-') << std::endl;
    std::cout << "Testas baigtas" << std::endl;
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

void hidingPuzzleTest() {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::cout << "=== Hiding savybės testas (CustomHash) ===" << std::endl;
    
    std::string salt = stringGeneratorius(32, gen);
    std::string secret = "Slapta žinutė";
    
    std::cout << "   Salt (r): " << salt << std::endl;
    std::cout << "   Secret (x): " << secret << std::endl;
    
    std::string hash = CustomHash::hash(salt + secret);
    std::cout << "   H(r || x): " << hash << std::endl;
    
    std::cout << "\n=== Puzzle-Friendliness testas ===" << std::endl;
    std::cout << "Ieškoma x' tokio, kad H(r || x') prasideda su '000'..." << std::endl;
    
    const int NUM_TRIALS = 5;  
    const std::string TARGET_PREFIX = "000";
    const double EXPECTED_ATTEMPTS = 4096.0;  // 16^3 = 4096 (trys nuliai hex'e)
    
    std::vector<int> all_attempts;
    auto totalStart = std::chrono::high_resolution_clock::now();
    
    for (int trial = 0; trial < NUM_TRIALS; trial++) {
        int attempts = 0;
        std::string x_prime;
        std::string target_hash;
        auto trialStart = std::chrono::high_resolution_clock::now();
        
        while (true) {
            x_prime = stringGeneratorius(10, gen);
            target_hash = CustomHash::hash(salt + x_prime);
            attempts++;
            
            if (target_hash.substr(0, TARGET_PREFIX.length()) == TARGET_PREFIX) {
                auto trialEnd = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> trialDuration = trialEnd - trialStart;
                all_attempts.push_back(attempts);
                
                std::cout << "   Bandymas #" << (trial + 1) << ": " << attempts 
                          << " bandymų (" << std::fixed << std::setprecision(3) 
                          << trialDuration.count() << "s), x' = " << x_prime 
                          << ", H = " << target_hash.substr(0, 12) << "..." << std::endl;
                break;
            }
        }
        
        std::cout << "   Bandymas #" << (trial + 1) << ": x' rastas po " 
                  << attempts << " bandymų (x' = " << x_prime 
                  << ", H = " << target_hash << ")" << std::endl;
    }
    
    auto totalEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> totalDuration = totalEnd - totalStart;
    
    double mean = std::accumulate(all_attempts.begin(), all_attempts.end(), 0.0) / NUM_TRIALS;
    double variance = 0.0;
    for (int a : all_attempts) {
        variance += (a - mean) * (a - mean);
    }
    variance /= NUM_TRIALS;
    double std_dev = std::sqrt(variance);
    
    std::cout << "\n=== Statistika ===" << std::endl;
    std::cout << "Iš viso bandymų: " << NUM_TRIALS << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Bendras laikas: " << totalDuration.count() << " s" << std::endl;
    std::cout << "Vidutinis laikas vienam bandymui: " << (totalDuration.count() * 1000.0 / mean) << " ms" << std::endl;
    
    std::cout << "\nRezultatai ieškant pradžios '000':" << std::endl;
    std::cout << "- Tikėtina bandymų (16^3): ~" << EXPECTED_ATTEMPTS << std::endl;
    std::cout << "- Faktinis vidurkis: " << mean << " bandymų" << std::endl;
    std::cout << "- Standartinis nuokrypis: " << std_dev << std::endl;
    std::cout << "- Mažiausiai bandymų: " << *std::min_element(all_attempts.begin(), all_attempts.end()) << std::endl;
    std::cout << "- Daugiausiai bandymų: " << *std::max_element(all_attempts.begin(), all_attempts.end()) << std::endl;
    
    double ratio = mean / EXPECTED_ATTEMPTS;
    std::cout << "\nSantykis (faktinis/numatytas): " << std::setprecision(4) << ratio << std::endl;
    
    double z_score = std::abs(mean - EXPECTED_ATTEMPTS) / (std_dev / std::sqrt(NUM_TRIALS));
    bool passes = z_score < 2.0;
    
    std::cout << "\nIšvada: " << (passes ? "PAVYKO" : "NEPAVYKO") << " (z-score: " 
              << std::setprecision(2) << z_score << ")" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
}
