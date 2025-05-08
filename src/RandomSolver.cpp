#include "RandomSolver.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>

// Funkcja pomocnicza do sortowania operacji po operation_id
bool porownajOperacje(const OperationSchedule& a, const OperationSchedule& b)
{
    return a.operation_id < b.operation_id;
}

RandomSolver::RandomSolver()
    : makespan(0)
{}

void RandomSolver::solve(const std::vector<OperationSchedule>& operations, int liczbaJobow, int liczbaMaszyn)
{
    schedule.clear();

    // 1. Grupujemy operacje po jobach - do przmeyslenia 
    std::vector<std::vector<OperationSchedule>> operacjePoJobach;
    operacjePoJobach.resize(liczbaJobow);

    for (int i = 0; i < operations.size(); ++i) 
    {
        const OperationSchedule& op = operations[i];
        operacjePoJobach[op.job_id].push_back(op); //odkladanie na kupke
    }

    // 2. Sortujemy operacje w każdym jobie po operation_id
    for (int job = 0; job < liczbaJobow; ++job) 
    {
        std::sort(operacjePoJobach[job].begin(), operacjePoJobach[job].end(), porownajOperacje);
    }

    // 3. Tablice dostępności
    std::vector<int> machine_available; //kiedy maszyna wolna do operacji 
    machine_available.resize(liczbaMaszyn, 0);

    std::vector<int> job_available; //kiedy job moze rozpoaczac kolejna operacje
    job_available.resize(liczbaJobow, 0);

    // 4. Tablica która mówi, którą operację wykonujemy teraz w danym jobie
    std::vector<int> ktora_operacja;
    ktora_operacja.resize(liczbaJobow, 0);

    // 5. Lista aktywnych jobów- wskzanik na te ktore jeszcze zostaly
    std::vector<int> aktywne_joby;
    for (int job = 0; job < liczbaJobow; ++job) 
    {
        aktywne_joby.push_back(job);
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    // 6. Budowanie harmonogramu
    while (!aktywne_joby.empty()) 
    {
        // Losujemy aktywny job
        std::shuffle(aktywne_joby.begin(), aktywne_joby.end(), gen); //tasujemy aktynwe job

        int znaleziony = -1;
        int job_id = -1;

        for (int i = 0; i < aktywne_joby.size(); ++i) 
        {
            job_id = aktywne_joby[i]; //numer job ktory atakujemy
            if (ktora_operacja[job_id] < operacjePoJobach[job_id].size()) //sprawdzamy, czy ten job ma jeszcze coś do zrobienia
            {
                znaleziony = i; //jesli tak to przerwanie
                break;
            }
        }

        if (znaleziony == -1) 
        {
            break; // awaryjne zabezpieczenie (nie powinno się zdarzyć)
        }

        job_id = aktywne_joby[znaleziony];

        OperationSchedule op = operacjePoJobach[job_id][ktora_operacja[job_id]]; //bierzemy następną operację, którą ten job powinien teraz wykonać

        int earliest_start;
        if (machine_available[op.machine_id] > job_available[op.job_id]) 
        {
            earliest_start = machine_available[op.machine_id];
        } 
        else 
        {
            earliest_start = job_available[op.job_id];
        }

        //nadpisanie startu i konca
        op.start_time = earliest_start;
        op.end_time = earliest_start + op.processing_time;

        machine_available[op.machine_id] = op.end_time; //aktualizacja dostpenosci
        job_available[op.job_id] = op.end_time;

        schedule.push_back(op);

        ktora_operacja[job_id]++; //narzucenie kolejnej operacji 

        // Jeśli job wykonał już wszystkie operacje, usuwamy go z aktywnych
        if (ktora_operacja[job_id] == operacjePoJobach[job_id].size()) 
        {
            aktywne_joby.erase(aktywne_joby.begin() + znaleziony);
        }
    }

    // 7. Liczymy makespan- przegladamy caly harmonogram i szukamy najwiekszej liczby
    makespan = 0;
    for (int i = 0; i < schedule.size(); ++i) 
    {
        if (schedule[i].end_time > makespan) 
        {
            makespan = schedule[i].end_time;
        }
    }
}

void RandomSolver::printSchedule() const
{
    for (int i = 0; i < schedule.size(); ++i) 
    {
        const OperationSchedule& op = schedule[i];
        std::cout << "Job " << op.job_id
                  << ", Operacja " << op.operation_id
                  << ", Maszyna " << op.machine_id
                  << ", Start: " << op.start_time
                  << ", Koniec: " << op.end_time << "\n";
    }
    std::cout << "Makespan: " << makespan << "\n";
}

int RandomSolver::getMakespan() const
{
    return makespan;
}


void RandomSolver::zapiszDoCSV(const std::string& nazwaPliku) const
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
