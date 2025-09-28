#include <iostream>
#include <string>
#include "functions.h"
#include "customGenerator.h"

int main(){

    int menuChoice;
                
    std::cout << "Pasirinkite programos eigą:" << std::endl;
    std::cout << "1 | Įvesti norimą hashuoti tekstą ranka" << std::endl;
    std::cout << "2 | Nuskaityti failą" << std::endl;
    std::cin >> menuChoice;

    switch(menuChoice){
        case 1: {
            std::cout << "Pasirinkote teksto įvestį ranka" << std::endl;
            std::cout << "---------------------------------" << std::endl;

            std::string hashuojamasTekstas;
            std::cin >> hashuojamasTekstas;

            HashGenerator hash;

            std::string hashed = hash.generateHash(hashuojamasTekstas);
            std::cout << hashed << std::endl;
            break;
        }  

        case 2: {
            std::cout << "Pasirinkote nuskaityti duomenis iš failo" << std::endl;
            std::cout << "----------------------------------------" << std::endl;

            try {
                std::string fail = pasirinktiFaila();
            } catch (const char* e){
                std::cout << "Nuskaitymas nepavyko. " << e << std::endl;
                break;
            } catch (const std::runtime_error &e){
                std::cout << e.what();
            }

            break;

        }
        
    }







    return 0;
}