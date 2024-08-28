#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <vector>

void operate(char &letter) {
    double x = 12345.6789;
    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < 10000; j++) {
            x = sqrt(x);
            x = x + 0.000000001;
            x = pow(x, 2);
        }
    }
    std::cout << "Fragment: " << letter << ": " << x << std::endl;
}

void exeсSequentialOperations(std::vector<char> &letters)
{
    for (char &letter : letters) {
        operate(letter);
    }
}

void benchmarkSequentialAlgorithm(std::vector<char> &letters)
{
    // Start timer
    auto start = std::chrono::high_resolution_clock::now();
    exeсSequentialOperations(letters);
    // End Timer
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate and output the difference
    std::chrono::duration<double> duration = end - start;
    std::cout << "Sequential algorithm resulted in " << duration.count()  << " sec" << std::endl;
}

int main()
{
    std::vector<char> letters = {'A', 'B', 'C', 'D', 'E'};
    benchmarkSequentialAlgorithm(letters);

    return 0;
}
