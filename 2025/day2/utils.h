struct Range {
    int64_t start;
    string start_str;
    int64_t end;
    string end_str;
};

vector<Range> split_ranges(const string& input) {
    vector<Range> ranges;
    stringstream ss(input);
    string range_str;

    while (getline(ss, range_str, ',')) {
        size_t dash_pos = range_str.find('-');
        if (dash_pos != string::npos) {
            int64_t start = stoll(range_str.substr(0, dash_pos));
            int64_t end = stoll(range_str.substr(dash_pos + 1));
            ranges.push_back({start, range_str.substr(0, dash_pos), end, range_str.substr(dash_pos + 1)});
        }
    }

    return ranges;
}
