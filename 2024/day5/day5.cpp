#include <iostream>
#include <readInput.h>
#include <chrono>

#include "part1.h"
#include "part2.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    vector<string> inputs = readInput("5", argv[1], "input");
    
    auto start = high_resolution_clock::now();

    cout << "--- Part 1 --- \n" << part_1::get_sum_of_page_number(inputs) << endl;
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time Taken - "
         << (duration.count() / 1000000.0) << " sec" << endl;

    start = high_resolution_clock::now();

    cout << "--- Part 2 --- \n" << part_2::get_sum_of_invalid_page_number(inputs) << endl;

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time Taken - "
         << (duration.count() / 1000000.0) << " sec" << endl;
}
