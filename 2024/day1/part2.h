#include<vector>
#include<map>

using namespace std;

void check_and_insert(map<int64_t, int64_t> &right_list_number_appearance, int64_t number) {
    right_list_number_appearance[number]++;
}

void parse_lists_to_number(vector<string> inputs, vector<int64_t> &left_list, map<int64_t, int64_t> &right_list_number_appearance) {
    string split_sub_str = "   ";
    
    for(auto input: inputs) {
        int split_start_pos = input.find(split_sub_str);

        string left_list_number = input.substr(0, split_start_pos);
        string right_list_number = input.substr(split_start_pos + split_sub_str.length());

        left_list.push_back(stoll(left_list_number));
        check_and_insert(right_list_number_appearance, stoll(right_list_number));
    }

}

int64_t get_similarity_score(vector<string> inputs) {
    int64_t result = 0;

    vector<int64_t> left_list;
    map<int64_t, int64_t> right_list_number_appearance;
    parse_lists_to_number(inputs, left_list, right_list_number_appearance);


    for(int32_t idx = 0; idx < left_list.size(); idx++) {
        int64_t left_number = left_list[idx];
        result += left_number * right_list_number_appearance[left_number];   
    }

    return result;
}
