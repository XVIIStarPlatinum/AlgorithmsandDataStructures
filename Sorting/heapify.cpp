#include <algorithm>
#include <iostream>
#include <vector>

int n;
void heapify(int *arr, int i){
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest;
    if(l <= n && arr[l] > arr[i]){
        largest = l;
    } else {
        largest = i;
    }
    if(r <= n && arr[r] > arr[largest]){
        largest = r;
    }
    if(largest != i){
        int tmp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = tmp;
        heapify(arr, largest);
    }
}

void heapify(std::vector<int>::iterator begin, int i) {
    int largest;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if(l <= n && begin[l] > begin[i]) {
        largest = l;
    } else {
        largest = i;
    }
    if(r <= n && begin[r] > begin[largest]) {
        largest = r;
    }
    if(largest != i) {
        int tmp = begin[i];
        begin[i] = begin[largest];
        begin[largest] = tmp;
        heapify(begin, largest);
    }
}
void buildMaxHeap(int arr[], int sz) {
    for(int i = sz / 2 - 1; i >= 0; i--) {
        heapify(arr, i);
    }
}
void buildMaxHeap(std::vector<int>::iterator begin, std::vector<int>::iterator end){
    for(int i = (int)(end - begin) / 2 - 1; i >= 0; i--) {
        heapify(begin, i);
    }
}

int main() {
    int arr[] = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};
    n = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Array to heap:\n";
    buildMaxHeap(arr, n);
    for(int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::vector<int> vec(arr, arr + n);
    std::cout << "\nVector to heap (custom-made):\n";
    n = (int) (vec.end() - vec.begin());
    buildMaxHeap(vec.begin(), vec.end());
    for(int i = 0; i < n; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\nVector to heap (make_heap):\n";
      std::make_heap(vec.begin(), vec.end());
    for (int i : vec) {
        std::cout << i << " ";
    }
    return 0;
}
