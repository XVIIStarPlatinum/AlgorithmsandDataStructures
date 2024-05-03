#include <algorithm>
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

unsigned int randomGenerator(std::mt19937 &rng, unsigned int min, unsigned int max) {
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    return dist(rng);
}

std::vector<unsigned int> generate_vector(std::mt19937 &rng, unsigned int min, unsigned int max, size_t size){
    std::vector<unsigned int> random_vector;
    for(int i = 1; i < size; ++i) {
        random_vector.push_back(randomGenerator(rng, min, max));
    }
    return random_vector;
}

template <typename RandomAccessIterator>
void heapify(RandomAccessIterator begin, RandomAccessIterator end, RandomAccessIterator current) {

    RandomAccessIterator largest = current;

    auto child1 = current + std::distance(begin, current);
    auto child2 = child1++;

    if(child1 < end && *current < *child1) {
        largest = child1;
    } else {
        largest = current;
    }
    if(child2 < end && *largest < *child2) {
        largest = child2;
    }
    if(largest != current) {
        std::swap(*current, *largest);
        heapify(current, end, largest);
    }
}

template <typename RandomAccessIterator>
void buildMaxHeap(RandomAccessIterator begin, RandomAccessIterator end){
    for(auto current = std::next(begin, std::distance(begin, end) / 2) - 1; current >= begin; --current) {
        heapify(begin, end, current);
    }
}
void test_heapify(std::mt19937 &rng, unsigned int min, unsigned int max, size_t size) {
    const char* path = R"(D:\ITMOrbius\A&DS_XVIIstarPt_\Sorting\test_results.csv)";
    std::ofstream result_file;
    result_file.open(path, std::ios::in | std::ios::app);
    std::vector<unsigned int> vec1 = generate_vector(rng, min, max, size);
    std::cout << "Randomly generated vector before being heapified:\n";
    result_file << "Before\n";
    for(unsigned int i : vec1) {
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
    for(unsigned int i : vec1) {
        std::cout << i << " ";
        result_file << i << ",";
    }
    std::cout << "\nElapsed time for custom function: " << time_custom.count();
    result_file << "\nT1," << time_custom.count() << "\n";
//    std::vector<int> vec2 = vec1;
    std::cout << "\nVector to heap (make_heap):\n";
    result_file << "make_heap()\n";
    const auto start2 {std::chrono::steady_clock::now()};
    std::make_heap(vec1.begin(), vec1.end());
    const auto end2 {std::chrono::steady_clock::now()};
    for (unsigned int i : vec1) {
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
        std::cout << "TEST " << i << std::string(60, '=') << "\n";
        test_heapify(rng, 5, 25, 25);
    }
    return 0;
}
