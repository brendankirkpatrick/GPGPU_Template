/*
 * Simple sample program that verifies that library can be linked and is working properly
 */

#include <iostream>
#include <span>
#include <sstream>
#include <vector>

#include "simple_nn.hpp"

using namespace std;

int main()
{
    cout << "Input a space-separated list of numbers: ";

    string input;
    vector<float> values;
    getline(std::cin, input);

    istringstream iss(input);

    float number;
    while(iss >> number)
    {
        values.push_back(number);
    }

    float scalar;
    cout << "Input scaling factor: ";
    cin >> scalar;

    // use library function to scale values by constant
    scale_by_constant(values, scalar);

    cout << "Scaled output: ";
    for(const auto val : values)
    {
        cout << val << ' ';
    }
    cout << endl;

    return 0;
}
