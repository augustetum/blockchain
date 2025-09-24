#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include "functions.h"

std::string pasirinktiFaila(){

    while(true){
        try{
            system("ls *.txt failaiHashavimui/*.txt 2>/dev/null > temp.txt");
            std::ifstream tempFail("temp.txt");
            std::vector<std::string> failuPav;
     
            std::string failoPav;
            while(std::getline(tempFail, failoPav)){
                failuPav.push_back(failoPav);

            }
            tempFail.close();
            system("rm temp.txt");
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