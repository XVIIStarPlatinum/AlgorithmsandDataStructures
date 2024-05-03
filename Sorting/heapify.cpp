#include <algorithm>
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

int randomGenerator(std::mt19937 &rng, int min, int max) {
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    return dist(rng);
}

std::vector<int> generate_vector(std::mt19937 &rng, int min, int max){
    std::unordered_set<int> random_set;
    size_t size = randomGenerator(rng, min, max);
    if(size < 3) {
        size = 3;
    }
    while(random_set.size() != size) {
        random_set.insert(randomGenerator(rng, min, max));
    }
    std::vector<int> random_vector(random_set.begin(), random_set.end());
    return random_vector;
}

template <typename RandomAccessIterator>
void heapify(RandomAccessIterator begin, RandomAccessIterator end, RandomAccessIterator current) {

    RandomAccessIterator largest = current;

    auto left_child = current + std::distance(begin, current) + 1;
    auto right_child = left_child++;

    if(left_child < end && *current < *left_child) {
        largest = left_child;
    }

    if(right_child < end && *largest < *right_child) {
        largest = right_child;
    }
    if(largest != current) {
        std::swap(*current, *largest);
        heapify(current, end, largest);
    }
}

template <typename RandomAccessIterator>
void buildMaxHeap(RandomAccessIterator begin, RandomAccessIterator end){
    for(auto current = begin + std::distance(begin, end) / 2; current >= begin; --current) {
        heapify(begin, end, current);
    }
}
void test_heapify(std::mt19937 &rng, int min, int max) {
    const char* path = R"(D:\ITMOrbius\A&DS_XVIIstarPt_\Sorting\test_results.csv)";
    std::ofstream result_file;
    result_file.open(path, std::ios::in | std::ios::app);
    std::vector<int> vec1 = generate_vector(rng, min, max);
    std::vector<int> vec2 = vec1;
    std::cout << "Randomly generated vector before being heapified:\n";
    result_file << "Before\n";
    for(int i : vec1) {
        std::cout << i << " ";
        result_file << i << ",";
    }
    result_file << "\n";
    std::cout << "\nVector to heap (custom-made):\n";
    result_file << "buildMaxHeap()\n";
    const auto start1{std::chrono::steady_clock::now()};
    buildMaxHeap(vec1.begin(), vec1.end());
    const auto end1 {std::chrono::steady_clock::now()};
    const std::chrono::duration<double> time_custom{end1 - start1};
    for(int i : vec1) {
        std::cout << i << " ";
        result_file << i << ",";
    }
    std::cout << "\nElapsed time for custom function: " << time_custom.count();
    result_file << "\nT1," << time_custom.count() << "\n";
//    std::vector<int> vec2 = vec1;
    std::cout << "\nVector to heap (make_heap):\n";
    result_file << "make_heap()\n";
    const auto start2 {std::chrono::steady_clock::now()};
    std::make_heap(vec2.begin(), vec2.end());
    const auto end2 {std::chrono::steady_clock::now()};
    for (int i : vec2) {
        std::cout << i << " ";
        result_file << i << ",";
    }
    const std::chrono::duration<double> time_lib{end2 - start2};
    std::cout << "\nElapsed time for make_heap(): " << time_lib.count() << "\n";
    result_file << "\nT2," << time_lib.count() << "\n";
//    assert(vec1 == vec2 && "Функция не прошла тестирование.");
    result_file.flush();
    result_file.close();
}

int main() {
    std::random_device dev;
    std::mt19937 rng(dev());
    for(int i = 1; i <= 3; ++i) {
        std::cout << "TEST " << i << std::string(100, '=') << "\n";
        test_heapify(rng, 1, 20);
    }
    return 0;
}
