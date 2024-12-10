#include <iostream>
#include <vector>

namespace part_1 {
    string VALID_INSTRUCTION_START_POINT = "mul(";

    int64_t find_valid_instruction(string input, int64_t start_pos, int64_t &result) {
        int64_t ins_start_pos = input.find(VALID_INSTRUCTION_START_POINT, start_pos);

        if(ins_start_pos == string::npos) {
            return ins_start_pos;
        }

        string first_no = "", second_no = "";

        int64_t idx = ins_start_pos + VALID_INSTRUCTION_START_POINT.size();
        while(isdigit(input[idx]) ) {
            first_no += input[idx];
            idx++;
        }
        idx++;
        while(isdigit(input[idx]) ) {
            second_no += input[idx];
            idx++;
        }
        if(input[idx] == ')') {
            result += stoll(first_no) * stoll(second_no);
        }

        return idx++;
    }

    int64_t find_all_valid_instruction(string input, int64_t &result) {
        int64_t next_pos = 0;
        while(next_pos != string::npos) {
            next_pos = find_valid_instruction(input, next_pos, result);
        }
        return 0;
    }

    int64_t scan_courrupted_memory(vector<string> inputs) {
        int64_t result = 0;
        for(auto i: inputs) {
            find_all_valid_instruction(i, result);
        }
        return result;
    }
}
