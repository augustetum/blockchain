#include "functions.h"


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
