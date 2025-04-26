#include "JSSPInstance.h"
#include <iostream>
using namespace std;

int main() 
{
    JSSPInstance instancja;
    if (instancja.wczytajPlik("Known-Optima/long-js-600000-100-10000-1.data")) {
        instancja.wypiszOperacje();
    }
    //std::cout<<instancja.liczbaJobow << " <- liczba job, liczba maszyn -> " << instancja.liczbaMaszyn << endl;
    return 0;
}
