#include <algorithm>
#include <iostream>
#include <vector>

int heapSize;

void heapify(int *arr, int i){
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest;
    if(l <= heapSize && arr[l] > arr[i]){
        largest = l;
    }else{
        largest = i;
    }
    if(r <= heapSize && arr[r] > arr[largest]){
        largest = r;
    }
    if(largest != i){
        int tmp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = tmp;
        heapify(arr, largest);
    }
}

void buildMaxHeap(int arr[], int n){
    heapSize = n;
    for(int i = n/2 - 1; i >= 0; i--){
        heapify(arr, i);
    }
}



int main() {
    int arr[] = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};
    int n = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Array to heap:\n";
    buildMaxHeap(arr, n);
    std::vector<int> vec(arr, arr + n);

    for(int i = 0; i < n; i++){
        std::cout << arr[i] << " ";
    }
    std::cout << "\nVector to heap (make_heap):\n";
    std::make_heap(vec.begin(), vec.end());
    for (int i : vec) {
        std::cout << i << " ";
    }
    return 0;
}
