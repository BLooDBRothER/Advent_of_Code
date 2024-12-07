namespace part2 {
    bool is_report_value_safe(int8_t order_flag, int32_t current_value, int32_t next_value) {
        bool is_safe = order_flag == 1 ? current_value < next_value : current_value > next_value;
        int32_t report_difference =  abs(current_value - next_value);

        return is_safe && (report_difference >= 1 && report_difference <= 3);
    }

    bool run_dampner(int8_t order_flag, int32_t prev_value, int32_t curr_value, int32_t next_value, int32_t next_plus_one_value, int &idx) {
        bool is_safe_without_curr = is_report_value_safe(order_flag, prev_value, next_value);
        if(is_safe_without_curr) {
            return true;
        }
        bool is_safe_without_next = is_report_value_safe(order_flag, curr_value, next_plus_one_value);

        if(is_safe_without_next) {
            idx++;
            return true;
        }

        return false;

    }

    bool check_is_safe(vector<int32_t> report_values) {
        int8_t inc_count = 0, dec_count = 0;
        
        for(int idx = 0; idx < report_values.size() - 1; idx++){
            int32_t current_value = report_values[idx];
            int32_t next_value = report_values[idx + 1];

            current_value < next_value ? inc_count++ : dec_count++;
        }

        bool order_flag = inc_count > dec_count;
        int32_t prev_value = -1;
        bool is_level_removed = false;
        int idx = 0;
        for(; idx < report_values.size() - 2; idx++) {
            int32_t current_value = report_values[idx];
            int32_t next_value = report_values[idx + 1];
            bool is_safe = is_report_value_safe(order_flag, current_value, next_value);

            if(!is_safe) {
                if(is_level_removed) {
                    return false;
                }

                int32_t next_plus_one_value = report_values[idx + 2];
                if(prev_value != -1) {
                    bool is_safe = run_dampner(order_flag, prev_value, current_value, next_value, next_plus_one_value, idx);
                    
                    if(!is_safe) {
                        return false;
                    }
                }
                else {
                    bool is_curr_safe = is_report_value_safe(order_flag, current_value, next_plus_one_value);
                    bool is_next_safe = is_report_value_safe(order_flag, next_value, next_plus_one_value);

                    if(!is_curr_safe && !is_next_safe) {
                        return false;
                    }

                    if(!is_next_safe) {
                        idx++;
                    }
                }

                is_level_removed = true;
            }

            prev_value = current_value;
        }
        if(is_level_removed && idx < report_values.size() -1) {
            int32_t current_value = report_values[idx];
            int32_t next_value = report_values[idx + 1];
            bool is_safe = is_report_value_safe(order_flag, current_value, next_value);
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
}

