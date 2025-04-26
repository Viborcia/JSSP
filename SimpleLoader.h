#ifndef SIMPLE_LOADER_H
#define SIMPLE_LOADER_H

#include <vector>
#include <string>

struct OperationData2 {
    int job_id;         
    int operation_id;   
    int machine_id;     
    int processing_time;
};

class SimpleLoader {
public:
    int liczbaJobow;
    int liczbaMaszyn;
    std::vector<OperationData2> operacje; // Wczytane operacje w nowej strukturze!

    bool load(const std::string& filename);
    void wypisz() const;
};

#endif // SIMPLE_LOADER_H
