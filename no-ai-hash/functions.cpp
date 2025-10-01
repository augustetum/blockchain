#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <filesystem>
#include <chrono>
#include <random>
#include <unordered_map>
#include <utility>
#include <iomanip>
#include "functions.h"



/* MAC
std::string pasirinktiFaila(){
    while(true){
        try{
            //system("ls *.txt failaiHashavimui/*.txt 2>/dev/null > temp.txt");    
            system("for /r %A in (*.txt) do @echo %~nxA >> temp.txt");
            std::ifstream tempFail("temp.txt");
            std::vector<std::string> failuPav;
     
            std::string failoPav;
            while(std::getline(tempFail, failoPav)){
                failuPav.push_back(failoPav);

            }
            tempFail.close();
            //system("rm temp.txt");
            system("del temp.txt");
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
}*/


//windowsams
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
        std::cout << " 'Konstitucija.txt' nuskaitomas eilučių kiekis: ";
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

// Funkcija atsitiktiniam string generavimui
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

//nu kazkodel to hasho nemato declarimnto
void kolizijos() {
    std::random_device rd;
    std::mt19937 gen(rd());
    HashGenerator hash;
    
    const int numPairs = 100000;
    std::vector<int> lengths = {10, 100, 500, 1000};
    
    for (int length : lengths) {
        std::cout << "String vienos poros simboliu skaicius: " << length << std::endl;
        
        auto startTime = std::chrono::high_resolution_clock::now();
        
        std::vector<std::pair<std::string, std::string>> stringPairs;
        stringPairs.reserve(numPairs);
        std::unordered_map<std::string, int> hashCount;
        
        
        for (int i = 0; i < numPairs; ++i) {
            std::string str1 = stringGeneratorius(length, gen); 
            std::string str2 = stringGeneratorius(length, gen);  
            stringPairs.push_back(std::make_pair(str1, str2));
            std::string hash1 = hash.generateHash(str1);
            std::string hash2 = hash.generateHash(str2);
            
            hashCount[hash1]++;
            hashCount[hash2]++;
        }
        
        std::cout << "Sugeneruotų porų skaičius : " << numPairs << std::endl;
        
        int collisionCount = 0;
        int totalCollisions = 0;
        std::vector<std::pair<std::string, int>> collisions;
        
        for (const auto& entry : hashCount) {
            if (entry.second > 1) {
                collisionCount++;
                totalCollisions += (entry.second - 1);
                collisions.push_back(entry);
            }
        }
        
        std::cout << "Kolizijų skaičius: " << totalCollisions << std::endl;
        
        double collisionRate = (double)totalCollisions / (numPairs * 2) * 100.0;
        std::cout << "Kolizijų kiekis procentais: " << std::fixed << std::setprecision(4) 
             << collisionRate << " %" << std::endl;
        
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = endTime - startTime;
        std::cout << "Laikas: " << diff.count() << " s" << std::endl;
    }
    
}