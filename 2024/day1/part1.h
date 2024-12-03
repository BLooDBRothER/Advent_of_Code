#include<vector>

using namespace std;

void parse_lists_to_number(vector<string> inputs, vector<int64_t> &left_list, vector<int64_t> &right_list) {
    string split_sub_str = "   ";
    
    for(auto input: inputs) {
        int split_start_pos = input.find(split_sub_str);

        string left_list_number = input.substr(0, split_start_pos);
        string right_list_number = input.substr(split_start_pos + split_sub_str.length());

        left_list.push_back(stoll(left_list_number));
        right_list.push_back(stoll(right_list_number));
    }

}

int64_t get_total_distance(vector<string> inputs) {
    int64_t result = 0;
    vector<int64_t> left_list, right_list ;
    parse_lists_to_number(inputs, left_list, right_list);


    sort(left_list.begin(), left_list.end());
    sort(right_list.begin(), right_list.end());

    for(int32_t idx = 0; idx < left_list.size(); idx++) {
        int64_t left_number = left_list[idx];
        int64_t right_number = right_list[idx];
        result += abs(left_number - right_number);   
    }

    return result;
}
