bool check_is_safe(vector<int32_t> report_values) {
    int8_t order_flag = 0;
    for(int idx = 0; idx < report_values.size() - 1; idx++) {
        int32_t current_value = report_values[idx];
        int32_t next_value = report_values[idx + 1];

        if(current_value == next_value) {
            return false;
        }

        if(order_flag == 0) {
            order_flag = current_value < next_value ? 1 : -1;
        }

        bool is_safe = order_flag == 1 ? current_value < next_value : current_value > next_value;
        int32_t report_difference =  abs(current_value - next_value);
        is_safe = is_safe && (report_difference >= 1 && report_difference <= 3);
        if(!is_safe) {
            return false;
        }
    }
    return true;
}

int32_t get_safe_report_count(vector<string> inputs) {
    int32_t safe_count = 0;
    for(auto input: inputs) {
        int split_char_occurance = -1, prev_occurance = 0;
        string split_char = " ";
        vector<int32_t> report_values;

        while((split_char_occurance = input.find(split_char, split_char_occurance+1)) != string::npos) {
            int char_count = split_char_occurance - prev_occurance;
            
            string report_value = input.substr(prev_occurance, char_count);
            report_values.push_back(stoll(report_value));
            prev_occurance = split_char_occurance + 1;
        }
        string report_value = input.substr(prev_occurance, input.size() - prev_occurance);
        report_values.push_back(stoll(report_value));
        
        safe_count += check_is_safe(report_values) ? 1 : 0;
    }

    return safe_count;
}
