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
int M = 5, N = 10;
std::vector<int> vec(N);
std::uniform_int_distribution<> distrib(min, max);

void fillVector() {
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = distrib(gen);
    }
}

void processVectorPart(int firstIndex, int lastIndex) {
    for (int i = firstIndex; i < lastIndex; i++) {
        if (vec[i] > 50) {

            // Complex vector processing
            vec[i] = std::pow(vec[i] / 5 + (vec[i] % 10) + log(vec[i]) - sqrt(vec[i]), POWER);
        } else {

            // Simple vector processing
            vec[i] = std::pow(vec[i], POWER);
        }
    }
}

std::vector processThreads()
{
    std::vector<std::thread> threads;
    fillVector();

    int chunk = N / M;

    // Processing M threads
    for (int i = 0; i < M; i++) {
        int startIndex = chunk * i;
        int endIndex = startIndex + chunk - 1;
        threads.emplace_back(processVectorPart, startIndex, endIndex);
    }

    return threads;
}

void mesureExecutionTime(std::vector<std::thread> threads)
{
    // Start timer
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < threads.size(); i++) {
        threads[i].join();
    }

    // End timer
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::high_resolution_clock::now();

    // Calculate and output the difference
    std::chrono::duration<double> duration = end - start;
    std::cout << "Parallel algorithm resulted in " << std::fixed << duration.count()  << " sec" << std::endl;
    std::cout << std::fixed << duration.count()  << " sec" << std::endl;
}

int main()
{
    std::vector<std::thread> threads = processThreads();
    mesureExecutionTime(threads);

    return 0;
}
