#include <iostream>
#include "stack.h"
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    // Open the file "abc.txt" for reading
    ifstream inputFile("data.txt");

    // Variable to store each line from the file
    std::string line;

    // Read each line from the file and print it
    while (getline(inputFile, line)) {
        // Process each line as needed
        cout << "infix: " << line << endl;
        string postfix = in2post(line);
        cout << "postfix: " << postfix << endl;
        double answer = eval_postfix(postfix);
        cout << "answer: " << fixed << setprecision(1) << answer << endl;
        cout << endl;
    }

    // Always close the file when done
    inputFile.close();

    return 0;
}