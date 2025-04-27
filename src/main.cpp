#include "JSSPInstance.h"
#include "SimpleLoader.h"
#include "RandomSolver.h"

#include <iostream>
using namespace std;

int main() 
{
    /*JSSPInstance instancja;
    if (instancja.wczytajPlik("Known-Optima/long-js-600000-100-10000-1.data")) {
        instancja.wypiszOperacje();
    }*/

    SimpleLoader loader;
    loader.load("LA/toy.data");
    loader.wypisz();

    RandomSolver solver;
    solver.solve(loader.operacje, loader.liczbaJobow, loader.liczbaMaszyn);
    solver.printSchedule();
    

    return 0;
}
