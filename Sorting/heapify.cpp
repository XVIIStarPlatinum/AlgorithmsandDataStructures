#include <algorithm>
#include <iostream>
#include <vector>

template <typename RAND_ACC_ITR>
void heapify(RAND_ACC_ITR begin, RAND_ACC_ITR end, RAND_ACC_ITR current) {

    RAND_ACC_ITR largest;

    auto left = current + std::distance(begin, current);
    auto right = left++;

    if(left < end && *left > *current) {
        largest = left;
    } else {
        largest = current;
    }
    if(right < end && *right > *largest) {
        largest = right;
    }
    if(largest != current) {
        std::swap(*largest, *current);
        heapify(current, end, largest);
    }
}

template <typename RAND_ACC_ITR>
void buildMaxHeap(RAND_ACC_ITR begin, RAND_ACC_ITR end){
    for(auto current = std::next(begin, std::distance(begin, end) / 2); current >= begin; current--) {
        heapify(begin, end, current);
    }
}

int main() {
    std::vector<int> vec{1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};
    std::cout << "Vector to heap (custom-made):\n";
    buildMaxHeap(vec.begin(), vec.end());
    for(int i : vec) {
        std::cout << i << " ";
    }
    std::cout << "\nVector to heap (make_heap):\n";
    std::make_heap(vec.begin(), vec.end());
    for (int i : vec) {
        std::cout << i << " ";
    }
    return 0;
}
