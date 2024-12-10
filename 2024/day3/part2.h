#include <iostream>
#include <vector>

namespace part_2 {
    string VALID_INSTRUCTION_START_POINT = "mul(";
    string DO_INSTRUCTION = "do()";
    string DONT_INSTRUCTION = "don't()";

    int64_t update_index_to_dont_instruction(vector<pair<int64_t, int64_t>> index_to_skip, int64_t index) {
        // cout << "before " << index << endl;
        for(auto to_skip: index_to_skip) {
            if(index >= to_skip.first && (to_skip.second == string::npos || index < to_skip.second)) {
                return to_skip.second;
            }
        }
        return index;
    }

    int64_t find_valid_instruction(string input, int64_t start_pos, int64_t &result, vector<pair<int64_t, int64_t>> index_to_skip) {
        int64_t ins_start_pos = input.find(VALID_INSTRUCTION_START_POINT, start_pos);
        int64_t updated_index = update_index_to_dont_instruction(index_to_skip, ins_start_pos);
        // cout << ins_start_pos << " " << updated_index << " " << string::npos << endl;
        if(ins_start_pos != updated_index) {
            return updated_index;
        }

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
            // cout << first_no << " " << second_no << endl;
            result += stoll(first_no) * stoll(second_no);
        }

        return idx++;
    }

    void find_invalid_memory_position(string input, vector<pair<int64_t, int64_t>> &index_to_skip) {
        int64_t start_pos = 0;
        int64_t dont_ins_index = input.find(DONT_INSTRUCTION, start_pos);

        while(dont_ins_index != string::npos) {
            int64_t do_ins_index = input.find(DO_INSTRUCTION, dont_ins_index);
            do_ins_index = do_ins_index != string::npos ? do_ins_index + DO_INSTRUCTION.size() : string::npos;
            // cout << dont_ins_index << " " << input[dont_ins_index] << " " << do_ins_index << " " << input[do_ins_index] << endl;
            index_to_skip.push_back(pair<int64_t, int64_t>{dont_ins_index, do_ins_index});
            dont_ins_index = input.find(DONT_INSTRUCTION, do_ins_index);
        }
    }

    int64_t find_all_valid_instruction(string input, int64_t &result) {
        vector<pair<int64_t, int64_t>> index_to_skip;
        int64_t next_pos = 0;
        find_invalid_memory_position(input, index_to_skip);
        while(next_pos != string::npos) {
            next_pos = find_valid_instruction(input, next_pos, result, index_to_skip);
            // cout << next_pos << endl;
        }
        return 0;
    }

    int64_t scan_courrupted_memory(vector<string> inputs) {
        int64_t result = 0;
        string all_input = "";
        for(auto i: inputs) {
            all_input += i;
        }
        find_all_valid_instruction(all_input, result);

        return result;
    }
}
