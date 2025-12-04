#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

namespace part2 {
    
    void get_invalid_id_in_range(Range range, set<int64_t>& invalid_ids) {
        cout << "______________ ";
        cout << range.start_str << " - " << range.end_str << " ______________" << endl; 
        int64_t min_digit = range.start_str.length();
        int64_t max_digit = range.end_str.length();
        int64_t max_pattern_len = floor(max_digit/2);
        cout << "Max pattern len: " << max_pattern_len << endl;

        for (int64_t pattern_len = 1; pattern_len <= max_pattern_len; pattern_len++) {
            int64_t pattern_start = pow(10, pattern_len-1);
            int64_t pattern_end = pow(10, pattern_len) - 1;
            cout << "Pattern start: " << pattern_start << " - Pattern end: " << pattern_end << endl;

            for (int64_t i = pattern_start; i <= pattern_end; i++) {
                string pattern = to_string(i) + to_string(i);
                while (pattern.length() < min_digit) {
                    pattern += to_string(i);
                }
                while (pattern.length() <= max_digit) {
                    int64_t invalid_id = stoll(pattern);
                    if (invalid_id >= range.start && invalid_id <= range.end) {
                        // cout << invalid_id << endl;
                        invalid_ids.insert(invalid_id);
                    }
                    pattern += to_string(i);
                }
            }
        }
        cout << "______________" << endl;
    }
    
    int64_t get_invalid_id_sum(vector<string> inputs) {
        int64_t invalid_id_sum = 0;
        set<int64_t> invalid_ids;
        string input = inputs.at(0);
        vector<Range> ranges = split_ranges(input);
        for (auto range: ranges) {
            get_invalid_id_in_range(range, invalid_ids);
        }
        cout << "Invalid IDs: ";
        for (auto invalid_id: invalid_ids) {
            cout << invalid_id << " ";
            invalid_id_sum += invalid_id;
        }
        cout << endl;
        return invalid_id_sum;
    }
}
