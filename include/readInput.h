#include <iostream>
#include <unistd.h>
#include "inputFile.h"

using namespace std;

string constructEachDayInputFilePath(string day, string year, string type) {
    // Buffer to hold the current working directory
    char buffer[PATH_MAX];

    if (getcwd(buffer, sizeof(buffer)) != nullptr) {
        // Print the current working directory
        std::cout << "Current Execution Path: " << buffer << std::endl;
    } else {
        // Handle error if getcwd fails
        std::cerr << "Error getting current working directory." << std::endl;
    }

    string file_path = "./" + year + "/day" + day + "/" + type + ".txt";
    cout << "Input file path: " << file_path << endl;

    cout << "Solution for the day" << day << endl;
    return "./" + year + "/day" + day + "/" + type + ".txt";
}

vector<string> readInput(string dayNo, string year, string type = "input") {

    InputFile inputFile(constructEachDayInputFilePath(dayNo, year, type));

    return inputFile.getInput();
}
