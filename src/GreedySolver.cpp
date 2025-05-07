#include "GreedySolver.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <limits>

GreedySolver::GreedySolver() : makespan(0) {}

void GreedySolver::solve(const std::vector<OperationSchedule>& operations, int liczbaJobow, int liczbaMaszyn) {
    schedule.clear();
    makespan = 0;

    std::vector<std::vector<OperationSchedule>> jobs(liczbaJobow);
    for (const auto& op : operations) {
        jobs[op.job_id].push_back(op);
    }

    std::vector<int> jobProgress(liczbaJobow, 0);
    std::vector<int> machineAvailable(liczbaMaszyn, 0);
    std::vector<int> jobAvailable(liczbaJobow, 0);

    int totalOperations = operations.size();
    int scheduledOperations = 0;

    while (scheduledOperations < totalOperations) {
        OperationSchedule bestOp;
      //  int bestTime = std::numeric_limits<int>::max();
      int bestTime = 0;
        bool found = false;

        for (int j = 0; j < liczbaJobow; ++j) {
            int opIdx = jobProgress[j];
            if (opIdx < jobs[j].size()) {
                const OperationSchedule& op = jobs[j][opIdx];
                int readyTime = std::max(machineAvailable[op.machine_id], jobAvailable[j]);

                if (op.processing_time > bestTime) {
                    bestTime = op.processing_time;
                    bestOp = op;
                    found = true;
                }
            }
        }

        if (found) {
            int job_id = bestOp.job_id;
            int op_id = jobProgress[job_id];
            OperationSchedule& op = jobs[job_id][op_id];

            int start = std::max(machineAvailable[op.machine_id], jobAvailable[op.job_id]);
            int end = start + op.processing_time;

            op.start_time = start;
            op.end_time = end;

            machineAvailable[op.machine_id] = end;
            jobAvailable[op.job_id] = end;

            schedule.push_back(op);
            makespan = std::max(makespan, end);
            jobProgress[op.job_id]++;
            scheduledOperations++;
        }
    }
}

void GreedySolver::printSchedule() const {
    for (const auto& op : schedule) {
        std::cout << "Job " << op.job_id
                  << ", Operacja " << op.operation_id
                  << ", Maszyna " << op.machine_id
                  << ", Start: " << op.start_time
                  << ", Koniec: " << op.end_time << "\n";
    }
    std::cout << "Makespan: " << makespan << "\n";
}

int GreedySolver::getMakespan() const {
    return makespan;
}
