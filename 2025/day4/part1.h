#include <vector>


using namespace std;

namespace part1 {

    bool is_paper_roll_accessible(int64_t row, int64_t col, vector<vector<char>> input_rolls) {
        int64_t adjacent_paper_rolls = 0;
        int64_t rows = input_rolls.size();
        int64_t cols = rows > 0 ? input_rolls[0].size() : 0;

        // 8 directions: up, down, left, right, and 4 diagonals
        vector<pair<int64_t, int64_t>> directions = {
            {-1, 0},  // up
            {1, 0},   // down
            {0, -1},  // left
            {0, 1},   // right
            {-1, -1}, // up-left
            {-1, 1},  // up-right
            {1, -1},  // down-left
            {1, 1}    // down-right
        };

        for (auto [dr, dc] : directions) {
            int64_t new_row = row + dr;
            int64_t new_col = col + dc;

            if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols) {
                if (input_rolls[new_row][new_col] == '@') {
                    adjacent_paper_rolls++;
                }

                if (adjacent_paper_rolls >= 4) {
                    return false;
                }
            }
        }

        return true;
    }

    void calculate_accessible_paper_rolls(vector<vector<char>> input_rolls, int64_t &total_paper_rolls) {
        int64_t row = 0;
        int64_t col = 0;

        for (int64_t row = 0; row < input_rolls.size(); row++) {
            for (int64_t col = 0; col < input_rolls.size(); col++) {
                if (input_rolls[row][col] == '@' && is_paper_roll_accessible(row, col, input_rolls)) {
                    total_paper_rolls++;
                }
            }
        }
    }
 
    int64_t get_total_paper_rolls(vector<string> inputs) {
        int64_t total_paper_rolls = 0;
        vector<vector<char>> input_rolls;

        for (auto rolls: inputs) {
            vector<char> roll_char;
            for (auto each: rolls) {
                roll_char.push_back(each);
            }
            input_rolls.push_back(roll_char);
        }

        calculate_accessible_paper_rolls(input_rolls, total_paper_rolls);

        return total_paper_rolls;
    }
}