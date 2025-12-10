#include <vector>

using namespace std;

namespace part2 {
    void calculate_largest_joltage(string battery_bank, int64_t &largest_joltage) {
        int8_t total_joltage_digits = 12;
        vector<int8_t> joltage_digits(total_joltage_digits, INT8_MIN);
        int8_t total_batteries = battery_bank.length();

        int8_t current_digit = 0;
        int8_t start_digit_idx = 0;
        int8_t end_digit_idx = total_batteries - total_joltage_digits;

        while (current_digit < total_joltage_digits) {
            int8_t max_digit_idx = start_digit_idx;
            while (start_digit_idx <= end_digit_idx) {
                if (battery_bank[start_digit_idx] > joltage_digits[current_digit]) {
                    max_digit_idx = start_digit_idx;
                    joltage_digits[current_digit] = battery_bank[max_digit_idx];
                }
                start_digit_idx++;
            }

            start_digit_idx = max_digit_idx + 1;
            current_digit++;
            end_digit_idx = (total_batteries - (total_joltage_digits - current_digit));
        }

        string total_joltage_string = "";
        for (auto value: joltage_digits) {
            total_joltage_string += value;
        }

        largest_joltage += stoll(total_joltage_string);
    }
    
    int64_t get_total_joltage(vector<string> inputs) {
        int64_t total_joltage = 0;
        for (auto input: inputs) {
            calculate_largest_joltage(input, total_joltage);
        }
    
        return total_joltage;
    }
}
