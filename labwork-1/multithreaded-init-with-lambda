#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <thread>

static void operate(char letter) {
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

int main()
{
    std::vector<char> letters = {'A', 'B', 'C', 'D', 'E'};
    std::vector<std::thread> threads;

    for (char& letter : letters) {
        threads.emplace_back([letter]() {
            operate(letter);
        });
    }

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    for (auto& thread : threads) {
        thread.join();
    }

    // End Timer
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate and output the difference
    std::chrono::duration<double> duration = end - start;
    std::cout << "Parallel algorithm using multithreading and lambda expressions resulted in " << duration.count()  << " sec" << std::endl;

    return 0;
}
