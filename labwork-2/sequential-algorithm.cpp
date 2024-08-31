#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <functional>

const int POWER = 2;

std::random_device rd;
std::mt19937 gen(rd());

int min = 1;
int max = 100;

std::uniform_int_distribution<> distrib(min, max);

void sequentialSimpleProcess(std::vector<int>& vec) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        vec[i] = std::pow(vec[i], POWER);
    }
}

void sequentialComplexProcess(std::vector<int>& vec) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        vec[i] = std::pow(vec[i] / 5 + (vec[i] % 10) + log(vec[i]) - sqrt(vec[i]), POWER);
    }
}

void fillVector(std::vector<int>& vec) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        vec[i] = distrib(gen);
    }
}

void measureExectutionTime(std::function<void(std::vector<int>&)> func, std::vector<int> &vec) {
    // Start timer
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::high_resolution_clock::now();

    func(vec);

    // End timer
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::high_resolution_clock::now();

    // Calculate and output the difference
    std::chrono::duration<double> duration = end - start;
    std::cout << "Sequential algorithm resulted in " << std::fixed << duration.count()  << " sec" << std::endl;
}

int main()
{
    std::vector<int> numbers(10000);
    fillVector(numbers);

    std::cout << "Simple execution:" << std::endl;
    measureExectutionTime(sequentialSimpleProcess, numbers);
    std::cout << "Complex execution:" << std::endl;
    measureExectutionTime(sequentialComplexProcess, numbers);

    return 0;
}
