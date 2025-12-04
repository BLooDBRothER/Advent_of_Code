#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

namespace part1{
    bool include_number(string number, bool is_start) {
        int64_t first_half = stoll(number.substr(0, number.length()/2));
        int64_t second_half = stoll(number.substr(number.length()/2, number.length()));
    
        return is_start ? first_half >= second_half : first_half <= second_half;
    }
    
    void get_invalid_id_in_range(Range range, int64_t& invalid_id_sum) {
        cout << "Range to process: " << range.start_str << " - " << range.end_str << endl;
        bool include_start_no = include_number(range.start_str, true);
        bool include_end_no = include_number(range.end_str, false);
    
        cout <<"Include start no: " << include_start_no << " - Include end no: " << include_end_no << endl;
    
        int64_t start_number = stoll(range.start_str.substr(0, range.start_str.length()/2));
        int64_t end_number = stoll(range.end_str.substr(0, range.end_str.length()/2));
    
        start_number = include_start_no ? start_number : start_number + 1;
        end_number = include_end_no ? end_number : end_number - 1;
    
        cout << "Start number: " << start_number << " - End number: " << end_number << endl;
    
        cout << "Invalid IDs: ";
        for (int64_t i = start_number; i <= end_number; i++) {
            string number = to_string(i);
            int64_t invalid_id = stoll(number + number);
            cout << invalid_id << " ";
            invalid_id_sum += invalid_id;
        }
        cout << endl;
    }
    
    void process_invalid_id(Range range, int64_t& invalid_id_sum) {
        cout << "______________ ";
        cout << range.start_str << " - " << range.end_str << " ______________" << endl; 
        int64_t start_digit = range.start_str.length();
        int64_t end_digit = range.end_str.length();
        cout << start_digit << " - " << end_digit << endl;
        for (int64_t digit = start_digit; digit <= end_digit; digit++) {
            if (digit % 2) {
                continue;
            } 
            cout << "digit: " << digit << endl;
            if (start_digit == end_digit) {
                cout << "start_digit == end_digit" << endl;
                get_invalid_id_in_range(range, invalid_id_sum);
            }
            else if (digit == start_digit) {
                cout << "digit == start_digit" << endl;
                int64_t end = pow(10, digit) - 1;
                Range range_in_digit = {
                    range.start,
                    range.start_str,
                    end,
                    to_string(end)
                };
                get_invalid_id_in_range(range_in_digit, invalid_id_sum);
            }
            else if (digit == end_digit) {
                cout << "digit == end_digit" << endl;
                int64_t start = pow(10, digit-1);
                Range range_in_digit = {
                    start,
                    to_string(start),
                    range.end,
                    range.end_str
                };
                get_invalid_id_in_range(range_in_digit, invalid_id_sum);
            }
            else {
                cout << "digit in between" << endl;
                int64_t start = pow(10, digit-1);
                int64_t end = pow(10, digit) - 1;
                Range range_in_digit = {
                    start,
                    to_string(start),
                    end,
                    to_string(end)
                };
                get_invalid_id_in_range(range_in_digit, invalid_id_sum);
            }
        }
        cout << "______________" << endl;
    }
    
    int64_t get_invalid_id_sum(vector<string> inputs) {
        int64_t invalid_id_sum = 0;
        string input = inputs.at(0);
        vector<Range> ranges = split_ranges(input);
        for (auto range: ranges) {
            process_invalid_id(range, invalid_id_sum);
        }
        return invalid_id_sum;
    }
}