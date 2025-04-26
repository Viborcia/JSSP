#include "JSSPInstance.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

bool JSSPInstance::wczytajPlik(const std::string& sciezka) {
    std::ifstream file(sciezka);
    if (!file.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku: " << sciezka << "\n";
        return false;
    }

    file >> liczbaJobow >> liczbaMaszyn;

    // WAŻNE: usuń znak nowej linii po liczbach
    std::string line;
    std::getline(file, line);

    int jobID = 0;
    while (jobID < liczbaJobow && std::getline(file, line)) {
        if (line.empty()) continue; // pomijamy puste linie

        std::istringstream iss(line);
        int maszyna, czas;
        int operationID = 0;

        while (iss >> maszyna >> czas) 
        {
            if (maszyna == -1 && czas == -1) 
            {
                break; // koniec operacji dla tego joba
            }

            operacje.push_back({ jobID, operationID, maszyna, czas });
            ++operationID;
        }
        ++jobID;
    }

    return true;
}


void JSSPInstance::wypiszOperacje() const {
    std::cout << "Liczba Jobow: " << liczbaJobow << ", Liczba Maszyn: " << liczbaMaszyn << "\n";
    for (const auto& op : operacje) {
        std::cout << "Job " << op.job_id << ", Operacja " << op.operation_id
                  << ", Maszyna " << op.machine_id
                  << ", Czas " << op.processing_time << "\n";
    }
}
