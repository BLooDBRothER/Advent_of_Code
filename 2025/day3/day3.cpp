#include <iostream>
#include <readInput.h>
#include <chrono>

#include "part1.h"
#include "part2.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    vector<string> inputs = readInput("3", argv[1]);
    
    auto start = high_resolution_clock::now();

    auto part1_solution = get_total_joltage(inputs);
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║            PART 1 SOLUTION             ║" << endl;
    cout << "╠════════════════════════════════════════╣" << endl;
    cout << "║  Answer: " << part1_solution << endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "║  Time:   " << (duration.count() / 1000000.0) << " seconds" << endl;
    cout << "╚════════════════════════════════════════╝\n" << endl;

    start = high_resolution_clock::now();

    // auto part2_solution = {<call_method>};
    // cout << "╔════════════════════════════════════════╗" << endl;
    // cout << "║            PART 2 SOLUTION             ║" << endl;
    // cout << "╠════════════════════════════════════════╣" << endl;
    // cout << "║  Answer: " << part2_solution << endl;

    // stop = high_resolution_clock::now();
    // duration = duration_cast<microseconds>(stop - start);
    // cout << "║  Time:   " << (duration.count() / 1000000.0) << " seconds" << endl;
    // cout << "╚════════════════════════════════════════╝\n" << endl;
}
