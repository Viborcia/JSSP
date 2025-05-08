#include "GreedySolver.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <limits>
#include <fstream>


// Konstruktor inicjalizuje makespan na 0
GreedySolver::GreedySolver() : makespan(0) {}

// Funkcja algorytmu zachłannego
void GreedySolver::solve(const std::vector<OperationSchedule>& operations, int liczbaJobow, int liczbaMaszyn) {
    schedule.clear(); // Czyści poprzedni harmonogram
    makespan = 0;     // Resetuje makespan

    // Grupowanie operacji według zadań (jobów)
    std::vector<std::vector<OperationSchedule>> jobs(liczbaJobow);
    for (const auto& op : operations) {
        jobs[op.job_id].push_back(op);
    }

    std::vector<int> jobProgress(liczbaJobow, 0);        // Indeks aktualnej operacji dla każdego joba
    std::vector<int> machineAvailable(liczbaMaszyn, 0);  // Kiedy dana maszyna będzie dostępna
    std::vector<int> jobAvailable(liczbaJobow, 0);       // Kiedy dany job będzie mógł kontynuować operację

    int totalOperations = operations.size();
    int scheduledOperations = 0;

    // Pętla wykonuje się, dopóki wszystkie operacje nie zostaną zaplanowane w harmonogramie
    while (scheduledOperations < totalOperations) {
        OperationSchedule bestOp;                         // Najlepsza aktualnie wybrana operacja
        int bestTime = std::numeric_limits<int>::max();   // Minimalny czas przetwarzania, ustawiony na maksymalny
        bool found = false;

        // Przeglądanie dostępnych operacji dla każdego joba
        for (int j = 0; j < liczbaJobow; ++j) {
            int opIdx = jobProgress[j];
            if (opIdx < jobs[j].size()) {
                const OperationSchedule& op = jobs[j][opIdx];
                int readyTime = std::max(machineAvailable[op.machine_id], jobAvailable[j]);

                // Wybór operacji z najmniejszym czasem przetwarzania
                if (op.processing_time < bestTime) {
                    bestTime = op.processing_time;
                    bestOp = op;
                    found = true;
                }
            }
        }

        // Jeśli udało się znaleźć operację do zaplanowania
        if (found) {
            int job_id = bestOp.job_id;
            int op_id = jobProgress[job_id];
            OperationSchedule& op = jobs[job_id][op_id];

            // Obliczanie czasu rozpoczęcia i zakończenia operacji
            int start = std::max(machineAvailable[op.machine_id], jobAvailable[op.job_id]);
            int end = start + op.processing_time;

            op.start_time = start;
            op.end_time = end;

            // Aktualizacja dostępności maszyny
            machineAvailable[op.machine_id] = end;
            // Aktualizacja dostępności joba
            jobAvailable[op.job_id] = end;

            schedule.push_back(op);                       // Dodanie operacji do harmonogramu
            makespan = std::max(makespan, end);           // Aktualizacja makespanu
            jobProgress[op.job_id]++;                     // Przejście do następnej operacji joba
            scheduledOperations++;                        // Zwiększenie liczby zaplanowanych operacji
        }
    }
}

// Funkcja drukująca harmonogram operacji
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

// Funkcja zwracająca makespan harmonogramu
int GreedySolver::getMakespan() const {
    return makespan;
}
// Funkcja zapisująca algorytm zachłanny do csv
void GreedySolver::zapiszDoCSV(const std::string& nazwaPliku) const
{
    std::ofstream out(nazwaPliku);
    if (!out.is_open()) {
        std::cerr << "Nie można otworzyć pliku do zapisu: " << nazwaPliku << "\n";
        return;
    }

    out << "job_id,operation_id,machine_id,start_time,end_time\n";
    for (const auto& op : schedule) {
        out << op.job_id << ","
            << op.operation_id << ","
            << op.machine_id << ","
            << op.start_time << ","
            << op.end_time << "\n";
    }
}