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
            break;
            
        }

        case 2:{
            std::string input = pasirinktiFaila();
            std::cout << "Enter salt: ";
            std::string salt;
            std::getline(std::cin, salt);
            std::string salted_input = input + salt;

            std::string result = CustomHash::hash(salted_input);
            std::cout<< result<<std::endl;
            break;
        }
        return 0;

    }
}
