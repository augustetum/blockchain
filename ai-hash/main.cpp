#include "functions.h"

// hash generated with claude.ai

int main()
{

    int hashInput;
    std::cout << "Hashing string      | 1" << std::endl;
    std::cout << "Hashing from a file | 2" << std::endl;
    std::cin >> hashInput;
    std::string input;

    //sutvarkyt, nes input not declared visam scope
    if (hashInput == 1)
    {
        std::cout << "Enter string to hash: ";
        std::getline(std::cin, input);
    }
    else
    {
        pasirinktiFaila();
    }

    std::cout << "Enter salt: ";
    std::string salt;
    std::getline(std::cin, salt);

    std::string salted_input = input + salt;
    std::string result = CustomHash::hash(salted_input);
    std::cout << std::endl;
    std::cout << "| String     | " << input << std::endl;
    std::cout << "| --------" << std::endl;
    std::cout << "| Hash value | " << result << std::endl;
    std::cout << std::endl;
    return 0;
}


//failo nuskaitymas is OOP
//testai
//