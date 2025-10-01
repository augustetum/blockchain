#include <chrono>
#include "functions.h"
// hash generated with claude.ai

int main()
{

    int hashInput;
    std::cout << "Hashing string      | 1" << std::endl;
    std::cout << "Hashing from a file | 2" << std::endl;
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
            int visasLaikas=0;

            for(int i=0; i <= 2; i++){
                auto start = std::chrono::high_resolution_clock::now();
                std::string result = CustomHash::hash(salted_input);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> diff = end - start;
                visasLaikas += diff.count();
                if(i==2){ std::cout<< result<<std::endl;
                    std::cout<< "Hasho ilgis: " << result.size()<<" simbolių"<<std::endl;
                }
            }
           
            std::cout<< "Laiko vidurkis: " << visasLaikas / 3 <<" s"<< std::endl;
            break;
        }
        return 0;

    }
}
