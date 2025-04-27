#ifndef RANDOM_SOLVER_H
#define RANDOM_SOLVER_H

#include "OperationSchedule.h"
#include <vector>

class RandomSolver {
public:
    RandomSolver();

    // Funkcja główna: buduje losowy harmonogram
    void solve(const std::vector<OperationSchedule>& operations, int liczbaJobow, int liczbaMaszyn);

    // Wypisuje harmonogram operacji
    void printSchedule() const;

    // Zwraca wartość makespan (maksymalny czas zakończenia operacji)
    int getMakespan() const;

private:
    std::vector<OperationSchedule> schedule; // Lista wykonanych operacji
    int makespan;                            // Najdłuższy czas zakończenia
};

#endif // RANDOM_SOLVER_H
