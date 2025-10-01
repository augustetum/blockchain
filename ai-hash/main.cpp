#include <chrono>
#include "functions.h"
#include "SHA256.h"
// hash generated with claude.ai

int main()
{

    int hashInput;
    std::cout << "Įvesti ranka        | 1" << std::endl;
    std::cout << "Nuskaityti is failo | 2" << std::endl;
    std::cout<< "Kolizijų testas      | 3" <<std::endl;
    std::cout<< "Lavinos testas       | 4"<<std::endl;
    std::cin >> hashInput;
    std::string input;
    switch(hashInput){
        case 1:{
            std::cout << "Enter string to hash: ";
            std::getline(std::cin, input);
            std::cout << "Enter salt: ";
            std::string salt;
            std::getline(std::cin, salt);
            std::string salted_input = input + salt;

            std::string result = CustomHash::hash(salted_input);
            std::cout<< result<<std::endl;
            std::cout<< "Hasho ilgis: " << result.size()<<" simbolių"<<std::endl;
            break;
            
        }

        case 2:{
            std::string input = failoNuskaitymas();
            std::cout << "Enter salt: ";
            std::string salt;
            std::getline(std::cin, salt);
            std::string salted_input = input + salt;
            double visasLaikas=0;
            double visasLaikasSHA=0;

            SHA256 sha;
            sha.update(salted_input);

            for(int i=0; i <= 2; i++){
                auto start1 = std::chrono::high_resolution_clock::now();  
                std::string result = CustomHash::hash(salted_input);
                auto end1 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> diff1 = end1 - start1;
                visasLaikas += diff1.count();
                if(i==2){ std::cout<< result<<std::endl;
                    std::cout<< "Hasho ilgis: " << result.size()<<" simbolių"<<std::endl;
                }


                auto start = std::chrono::high_resolution_clock::now();
                std::array<uint8_t, 32> digest = sha.digest();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> diff = end - start;
                visasLaikasSHA += diff.count();
                if(i==2){
                    std::cout << SHA256::toString(digest) <<" - SHA256 hashas" <<std::endl;
                }

            }
           
            std::cout<< "Laiko vidurkis: " << visasLaikas / 3 <<" s"<< std::endl;
            std::cout<< "Laiko vidurkis SHA: " <<visasLaikasSHA /3 << " s" <<std::endl;

            break;
        }
        case 3:{
            kolizijos();
        }
        case4:{
            //lavinosEfektas(100000);
        }
        return 0;

    }
}
