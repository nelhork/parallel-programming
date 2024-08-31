#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <iomanip>

const int POWER = 2;

std::random_device rd;
std::mt19937 gen(rd());

int min = 1;
int max = 100;

// M - number of threads, N - number of vector's elements
int M = 5, N = 1000;

std::uniform_int_distribution<> distrib(min, max);

void fillVector(std::vector<int> &vec) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        vec[i] = distrib(gen);
    }
}

void processVectorPart(std::vector<int> &vec, int threadId) {
    for (int i = threadId; i < N; i += M) {
        vec[i] = std::pow(vec[i] / 5 + (vec[i] % 10) + log(vec[i]) - sqrt(vec[i]), POWER);
    }
}

void measureExecutionTime(std::vector<std::thread> &threads)
{
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::high_resolution_clock::now();
    for (unsigned int i = 0; i < threads.size(); i++) {
        threads[i].join();
    }
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Parallel algorithm resulted in " << std::fixed << duration.count()  << " sec" << std::endl;
}

int main()
{
    std::vector<int> numbers(N);
    std::vector<std::thread> threads;
    fillVector(numbers);

    // Create threads with circular separation of elements
    for (int i = 0; i < M; i++) {
        threads.emplace_back(processVectorPart, std::ref(numbers), i);
    }

    measureExecutionTime(threads);

    return 0;
}
