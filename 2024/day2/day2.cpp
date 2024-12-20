#include <iostream>
#include <readInput.h>
#include <chrono>

#include "part1.h"
#include "part2.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    vector<string> inputs = readInput("2", argv[1], "input");
    
    auto start = high_resolution_clock::now();

    cout << "--- Part 1 --- \n" << get_safe_report_count(inputs) << endl;
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time Taken - "
         << (duration.count() / 1000000.0) << " sec" << endl;

    start = high_resolution_clock::now();

    cout << "--- Part 2 --- \n" << part2::get_safe_report_count(inputs) << endl;

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time Taken - "
         << (duration.count() / 1000000.0) << " sec" << endl;
}
