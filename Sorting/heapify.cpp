#include <algorithm>
#include <iostream>
#include <vector>

template <typename ITR>

void heapify(ITR begin, ITR i, int sz) {
    ITR largest;
    auto left = std::next(begin, 2 * std::distance(begin, i) + 1);
    auto right = std::next(begin, 2 * std::distance(begin, i) + 2);
    if(std::distance(begin, left) <= sz && *left > begin[std::distance(begin, i)]) {
        largest = left;
    } else {
        largest = i;
    }
    if(std::distance(begin, right) <= sz && *right > *largest) {
        largest = right;
    }
    if(largest != i) {
        auto tmp = i;
        i = largest;
        largest = tmp;
        heapify(begin, largest, sz);
    }
}

void buildMaxHeap(std::vector<int>::iterator begin, std::vector<int>::iterator end){
    for(auto i = begin; i != end; ++i) {
        heapify(begin, i, (int) (end - begin));
    }
}

int main() {
    std::vector<int> vec({1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17});
    std::cout << "\nVector to heap (custom-made):\n";
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
