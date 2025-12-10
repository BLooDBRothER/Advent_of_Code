#include <vector>

using namespace std;

namespace part1 {
    void calculate_largest_joltage(string battery_bank, int64_t &largest_joltage) {
        int8_t first_digit = INT8_MIN;
        int8_t second_digit = INT8_MIN;
        int64_t first_digit_idx = 0;
        int64_t second_digit_idx = 1;
    
        while (second_digit_idx < battery_bank.length()) {
            int8_t curr_first_digit = battery_bank.at(first_digit_idx) - '0';
            int8_t curr_second_digit = battery_bank.at(second_digit_idx) - '0'; 
            
            if (curr_first_digit > first_digit) {
                first_digit = curr_first_digit;
                second_digit = curr_second_digit;
            }
    
            if (curr_second_digit > second_digit) {
                second_digit = curr_second_digit;
            }
    
            first_digit_idx++;
            second_digit_idx++;
        }
    
        largest_joltage += first_digit * 10 + second_digit;
    }
    
    int64_t get_total_joltage(vector<string> inputs) {
        int64_t total_joltage = 0;
        for (auto input: inputs) {
            calculate_largest_joltage(input, total_joltage);
        }
    
        return total_joltage;
    }
}
