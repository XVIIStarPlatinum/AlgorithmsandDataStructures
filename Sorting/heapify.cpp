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
    return {random_set.begin(), random_set.end()};
}

template <typename RandomAccessIterator>
void output_vector(std::ostream& output_file, RandomAccessIterator begin, RandomAccessIterator end) {
    for(auto i = begin; i != end; ++i){
        std::cout << *i << " ";
        output_file << *i << ",";
    }
    std::cout << "\n";
}

template <typename RandomAccessIterator>
void heapify(RandomAccessIterator begin, RandomAccessIterator end, RandomAccessIterator current) {

    RandomAccessIterator largest = current;
    auto left_child = current + std::distance(begin, current);
    auto right_child = left_child + 1;

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
void buildMaxHeap(RandomAccessIterator begin, RandomAccessIterator end) {
    for(auto current = begin + std::distance(begin, end) / 2; current >= begin; --current) {
        heapify(begin, end, current);
    }
}

template <typename RandomAccessIterator>
bool check_heap(RandomAccessIterator begin, RandomAccessIterator end) {
    for(auto current = begin; current <= begin + (std::distance(begin, end)) / 2; ++current) {
        auto left_child = current + std::distance(begin, current);
        auto right_child = left_child + 1;
        if (*left_child > *current){
            return false;
        }
        if (right_child < end && *right_child > *current) {
            return false;
        }
    }
    return true;
}
void test_heapify(std::mt19937 &rng, int min, int max) {
    const char* path = R"(D:\ITMOrbius\A&DS_XVIIstarPt_\Sorting\test_results.csv)";
    std::ofstream result_file;
    result_file.open(path, std::ios::in | std::ios::app);

    auto vec1 = generate_vector(rng, min, max);
    auto vec2 = vec1;

    std::cout << "Randomly generated vector before being heapified:\n";
    result_file << "Before\n";
    output_vector(result_file, vec1.begin(), vec1.end());
    result_file << "\n";

    std::cout << "\nVector to heap (custom-made):\n";
    result_file << "buildMaxHeap()\n";
    const auto start1{std::chrono::steady_clock::now()};
    buildMaxHeap(vec1.begin(), vec1.end());
    const auto end1 {std::chrono::steady_clock::now()};
    const std::chrono::duration<double> time_custom{end1 - start1};
    output_vector(result_file, vec1.begin(), vec1.end());
    assert(std::is_heap(vec1.begin(), vec1.end()) && "Вектор не является кучей.");
    std::cout << "\nElapsed time for custom function: " << time_custom.count() << "\n";
    result_file << "\nT1," << time_custom.count() << "\n";

    std::cout << "\nVector to heap (stdlib):\n";
    result_file << "make_heap()\n";
    const auto start2{std::chrono::steady_clock::now()};
    std::make_heap(vec2.begin(), vec2.end());
    const auto end2{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> time_lib{end2 - start2};
    output_vector(result_file, vec2.begin(), vec2.end());
    assert(std::is_heap(vec2.begin(), vec2.end()) && "Вектор не является кучей.");
    std::cout << "\nElapsed time for custom function: " << time_lib.count() << "\n";
    result_file << "\nT1," << time_lib.count() << "\n";

    result_file.flush();
    result_file.close();
}

int main() {
    std::random_device dev;
    std::mt19937 rng(dev());
    for(int i = 1; i <= 100; ++i) {
        std::cout << "TEST " << i << std::string(100, '=') << "\n";
        test_heapify(rng, 1, 20);
    }
    return 0;
}
