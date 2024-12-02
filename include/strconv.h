int64_t convert_string_to_number(string input, int64_t& position) {
    string number = "";
    bool is_negative_number = false;

    if(input.at(position) == '-') {
        is_negative_number = true;
        position++;
    }
    
    while(position < input.size() && isdigit(input.at(position))) {
        number += input.at(position);
        position++;
    }

    return is_negative_number ? -1 * stoll(number) : stoll(number);
}
