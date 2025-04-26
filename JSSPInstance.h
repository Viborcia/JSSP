#ifndef JSSP_INSTANCE_H
#define JSSP_INSTANCE_H

#include <vector>
#include <string>

struct OperationData {
    int job_id;         // ID joba
    int operation_id;   // Numer operacji w jobie
    int machine_id;     // Na jakiej maszynie
    int processing_time;// Czas trwania
};

class JSSPInstance {
public:
    int liczbaJobow;
    int liczbaMaszyn;
    std::vector<OperationData> operacje;

    // Wczytuje instancje z pliku .data
    bool wczytajPlik(const std::string& sciezka);

    // Wypisuje operacje (do testow)
    void wypiszOperacje() const;
};

#endif // JSSP_INSTANCE_H
