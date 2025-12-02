#include <vector>

using namespace std;

namespace part1 {
    void get_current_dial_pos(string input, int64_t &dial_curr_pos) {
        char rotation = input.at(0);
        int64_t steps_pos = 1;
        int64_t steps = convert_string_to_number(input, steps_pos);
        if (rotation == 'R') {
            dial_curr_pos = (steps + dial_curr_pos) % 100;
        }
        else {
            dial_curr_pos = (dial_curr_pos - steps) % 100;
        }
    }
    
    int64_t get_password(vector<string> inputs) {
        int64_t result = 0;
        int64_t dial_curr_pos = 50;
        for (auto input: inputs) {
            get_current_dial_pos(input, dial_curr_pos);
            if (dial_curr_pos == 0) {
                result += 1;
            }
        }
        
        return result;
    }
}