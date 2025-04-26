#include "SimpleLoader.h"
#include <fstream>
#include <iostream>

bool SimpleLoader::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nie mogę otworzyć pliku: " << filename << std::endl;
        return false;
    }

    file >> liczbaJobow >> liczbaMaszyn;

    int jobID = 0;
    for (int i = 0; i < liczbaJobow; ++i) {
        for (int opID = 0; opID < liczbaMaszyn; ++opID) {
            int maszyna, czas;
            file >> maszyna >> czas;

            OperationData2 op;
            op.job_id = jobID;
            op.operation_id = opID;
            op.machine_id = maszyna;
            op.processing_time = czas;

            operacje.push_back(op);
        }
        ++jobID;
    }

    return true;
}

void SimpleLoader::wypisz() const {
    std::cout << "Liczba Jobow: " << liczbaJobow << ", Liczba Maszyn: " << liczbaMaszyn << "\n";
    for (const auto& op : operacje) {
        std::cout << "Job " << op.job_id
                  << ", Operacja " << op.operation_id
                  << ", Maszyna " << op.machine_id
                  << ", Czas: " << op.processing_time << "\n";
    }
}
