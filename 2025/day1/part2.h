#include <vector>
#include <cmath>

using namespace std;

namespace part2 {
    void is_crossed_0(string input, int64_t &dial_curr_pos, int64_t &password) {
        char rotation = input.at(0);
        int64_t steps_pos = 1;
        int64_t steps = convert_string_to_number(input, steps_pos);
        if (rotation == 'R') {
            int64_t temp_dial_curr_pos = (steps + dial_curr_pos);
            if (temp_dial_curr_pos >= 100) {
                int64_t temp_output = floor(temp_dial_curr_pos / 100);
                password += temp_output;
            }
            dial_curr_pos = temp_dial_curr_pos % 100;
        }
        else {
            if (dial_curr_pos == 0) {
                password += steps / 100;
            }
            else {
                int64_t steps_at_cross = steps / 100;
                password += steps_at_cross;
                int64_t temp_dial_curr_pos = (dial_curr_pos - (steps % 100));
                if (temp_dial_curr_pos <= 0) {
                    int64_t temp_output = abs(floor(temp_dial_curr_pos / 100));
                    password += temp_output ? temp_output : 1;
                }
            }
            dial_curr_pos = (dial_curr_pos - steps) % 100;
            if (dial_curr_pos < 0) {
                dial_curr_pos += 100;
            }
        }
    }

    void is_crossed_0_optimized(string input, int64_t &dial_curr_pos, int64_t &password) {
        char rotation = input.at(0);
        int64_t steps_pos = 1;
        int64_t steps = convert_string_to_number(input, steps_pos);
        if (rotation == 'R') {
            int64_t first_zero_at = dial_curr_pos == 0 ? 100 : (100 - dial_curr_pos);
            if (steps >= first_zero_at) {
                password += 1 + (steps - first_zero_at) / 100;
            }
            dial_curr_pos = (steps + dial_curr_pos) % 100;
        }
        else {
            int64_t first_zero_at = dial_curr_pos == 0 ? 100 : dial_curr_pos;
            if (steps >= first_zero_at) {
                password += 1 + (steps - first_zero_at) / 100;
            }
            dial_curr_pos = (dial_curr_pos - steps) % 100;
            if (dial_curr_pos < 0) {
                dial_curr_pos += 100;
            }
        }
    }
    
    int64_t get_password(vector<string> inputs) {
        int64_t password = 0;
        int64_t dial_curr_pos = 50;
        for (auto input: inputs) {
            is_crossed_0_optimized(input, dial_curr_pos, password);
        }
        
        return password;
    }
}