#include <iostream>
#include <string>
#include <chrono>
#include "functions.h"
#include "SHA256.h"

int main() {
    int menuChoice;
                
    std::cout << "Pasirinkite programos eigą:" << std::endl;
    std::cout << "1 | Įvesti norimą hashuoti tekstą ranka" << std::endl;
    std::cout << "2 | Nuskaityti failą" << std::endl;
    std::cout << "3 | Kolizijų paieška" << std::endl;
    std::cout << "4 | Lavinos efekto testas (CustomHash)" << std::endl;
    std::cout << "5 | Lavinos efekto testas (SHA-256)" << std::endl;
    std::cout << "6 | Hiding/puzzle-friendliness testas" << std::endl;
    std::cout << "7 | Hash'avimo efektyvumo testas" << std::endl;
    std::cin >> menuChoice;

    switch(menuChoice) {
        case 1: {
            std::cout << "Pasirinkote teksto įvestį ranka" << std::endl;
            std::cout << "---------------------------------" << std::endl;
            
            std::cin.ignore(); 
            std::string hashuojamasTekstas;
            std::cout << "Įveskite tekstą: ";
            std::getline(std::cin, hashuojamasTekstas);
            
            auto start = std::chrono::high_resolution_clock::now();
            std::string hashed = CustomHash::hash(hashuojamasTekstas);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end - start;
            
            std::cout << "\n=== Rezultatai ===" << std::endl;
            std::cout << "Hash'as: " << hashed << std::endl;
            std::cout << "Hash ilgis: " << hashed.size() << " simbolių" << std::endl;
            std::cout << "Sugaišta laiko: " << diff.count() << " s" << std::endl;
            break;
        }  

        case 2: {
            std::cout << "Pasirinkote nuskaityti duomenis iš failo" << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            
            std::cin.ignore(); 
            std::string hashuojamasTekstas = failoNuskaitymas();
            
            if (hashuojamasTekstas.empty()) {
                std::cout << "Klaida: Nepavyko nuskaityti failo arba jis tuščias." << std::endl;
                break;
            }

            auto start = std::chrono::high_resolution_clock::now();
            std::string hashed = CustomHash::hash(hashuojamasTekstas);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end - start;

            std::cout << "\n=== Rezultatai ===" << std::endl;
            std::cout << "Hash'as: " << hashed << std::endl;
            std::cout << "Hash ilgis: " << hashed.size() << " simbolių" << std::endl;
            std::cout << "Failo dydis: " << hashuojamasTekstas.length() << " simbolių" << std::endl;
            std::cout << "Sugaišta laiko: " << diff.count() << " s" << std::endl;
            break;
        }

        case 3: {
            std::cout << "Pasirinkote kolizijų paiešką" << std::endl;
            std::cout << "----------------------------" << std::endl;
            kolizijos();
            break;
        }
            
        case 4: {
            std::cout << "Pasirinkote lavinos efekto testą (CustomHash)" << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
            int numPairs = 100000;
            lavinosEfektas(numPairs);
            break;
        }
            
        case 5: {
            std::cout << "Pasirinkote lavinos efekto testą (SHA-256)" << std::endl;
            std::cout << "------------------------------------------" << std::endl;
            int numPairs = 100000;
            lavinosEfektasSHA(numPairs);
            break;
        }
            
        case 6: {
            std::cout << "Pasirinkote Hiding/puzzle-friendliness testą" << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
            hidingPuzzleTest();
            break;
        }
            
        case 7: {
            std::cout << "Pasirinkote hash'avimo efektyvumo testą" << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            testHashPerformance();
            break;
        }
            
        default:
            std::cout << "Neteisingas pasirinkimas!" << std::endl;
    }
    
    return 0;
}
