#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


int main()
{
    string filename = "C:/Users/Zuzia/Desktop/JSSP/Large_TA_tai_j10_m10_4_data.txt"; 
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Nie mogę otworzyć pliku: " << filename << endl;
        return 1;
    }

    int num_jobs, num_machines;
    file >> num_jobs >> num_machines;

    vector<vector<pair<int, int>>> jobs(num_jobs);

    for (int i = 0; i < num_jobs; ++i) {
        for (int j = 0; j < num_machines; ++j) {
            int machine, time;
            file >> machine >> time;
            jobs[i].push_back({machine, time});
        }
    }

    for (int i = 0; i < num_jobs; ++i) {
        cout << "Job " << i << ":\n";
        for (auto [machine, time] : jobs[i]) {
            cout << "  Maszyna: " << machine << ", Czas: " << time << "\n";
        }
    }

    return 0;
}