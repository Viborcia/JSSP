#include "JSSPInstance.h"
#include "SimpleLoader.h"
#include <iostream>
using namespace std;

int main() 
{
    /*JSSPInstance instancja;
    if (instancja.wczytajPlik("Known-Optima/long-js-600000-100-10000-1.data")) {
        instancja.wypiszOperacje();
    }*/

    SimpleLoader instancja;
    if (instancja.load("LA/tai_j10_m10_4.data")) 
    {
        instancja.wypisz();
    }

    //std::cout<<instancja.liczbaJobow << " <- liczba job, liczba maszyn -> " << instancja.liczbaMaszyn << endl;
    return 0;
}
