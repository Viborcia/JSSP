#ifndef GREEDY_SOLVER_H
#define GREEDY_SOLVER_H

#include "OperationSchedule.h"
#include <vector>

class GreedySolver {
public:
    GreedySolver();

    void solve(const std::vector<OperationSchedule>& operations, int liczbaJobow, int liczbaMaszyn);
    void printSchedule() const;
    int getMakespan() const;

private:
    std::vector<OperationSchedule> schedule;
    int makespan;
};

#endif // GREEDY_SOLVER_H
