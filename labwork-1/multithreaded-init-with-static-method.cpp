#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <thread>

class Initializer {
public:
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
};

int main()
{
    std::vector<std::thread> threads;
    std::vector<char> letters = {'A', 'B', 'C', 'D', 'E'};

    for (char letter : letters) {
        threads.emplace_back([letter]() {
            Initializer::operate(letter);
        });
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < threads.size(); i++) {
        threads[i].join();
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << std::fixed << "Parallel algorithm using static method resulted in " << duration.count()  << " sec" << std::endl;

    return 0;
}
