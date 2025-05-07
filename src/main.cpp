#include "JSSPInstance.h"
#include "SimpleLoader.h"
#include "RandomSolver.h"
#include "GreedySolver.h"

#include <iostream>
using namespace std;

int main() 
{

    SimpleLoader loader;
    loader.load("LA/toy.data");
    loader.wypisz();

    RandomSolver solver;
    solver.solve(loader.operacje, loader.liczbaJobow, loader.liczbaMaszyn);
    solver.printSchedule();

    GreedySolver greedy;
    greedy.solve(loader.operacje, loader.liczbaJobow, loader.liczbaMaszyn);
    greedy.printSchedule();
    

   /* JSSPInstance loader;
    loader.wczytajPlik("Known-Optima/long-js-600000-100-10000-1.data");
    loader.wypiszOperacje();

    RandomSolver solver;
    solver.solve(loader.operacje, loader.liczbaJobow, loader.liczbaMaszyn);
    solver.printSchedule();*/

    return 0;
}
