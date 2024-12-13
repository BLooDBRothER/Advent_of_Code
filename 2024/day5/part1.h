#include<iostream>
#include<string>
#include<unordered_map>
#include <sstream>

namespace part_1 {
    void create_page_order_map(unordered_map<int64_t, vector<int64_t>> &page_order_map, string input) {
        stringstream input_stream(input);

        char delimitter = '|';
        string first_no_str = "", second_no_str = "";

        getline(input_stream, first_no_str, delimitter);
        getline(input_stream, second_no_str, delimitter);

        int64_t first_no = stoll(first_no_str);
        int64_t second_no = stoll(second_no_str);

        page_order_map[first_no].push_back(second_no);
    } 

    void convert_order_str_to_int(string input, vector<int64_t> &orders) {
        stringstream input_stream(input);
        char delimitter = ',';
        string order = "";

        while(getline(input_stream, order, delimitter)) {
            orders.push_back(stoll(order));
        }
    }

    bool is_page_in_valid_order(vector<int64_t> orders, int64_t prev_page_idx, int64_t current_page, unordered_map<int64_t, vector<int64_t>> &page_order_map) {
        vector<int64_t> page_order = page_order_map[current_page];
        for(int64_t idx = 0; idx <= prev_page_idx; idx++) {
            for (auto page_order_of_curr_page: page_order) {
                if(page_order_of_curr_page == orders[idx]) {
                    return false;
                }
            }
        }
        return true;
    }

    void get_middle_page_of_valid_order(string input, unordered_map<int64_t, vector<int64_t>> &page_order_map, int64_t &result) {
        vector<int64_t> orders;
        convert_order_str_to_int(input, orders);
        for(int64_t idx = orders.size() - 1; idx > 0; idx--) {
            if(!is_page_in_valid_order(orders, idx - 1, orders[idx], page_order_map)) {
                return ;
            }
        }
        result += orders[orders.size() / 2];
    }

    int64_t get_sum_of_page_number(vector<string> inputs) {
        unordered_map<int64_t, vector<int64_t>> page_order_map;
        int64_t idx = 0;
        int64_t result = 0;
        
        while(inputs[idx] != "") {
            create_page_order_map(page_order_map, inputs[idx++]);
        }
        
        idx++;

        while(idx < inputs.size()) {
            get_middle_page_of_valid_order(inputs[idx++], page_order_map, result);
        }        
        
        return result;
    }
}
