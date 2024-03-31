#include <algorithm>
#include <iostream>

bool comparator(int const a, int const b){
    return a > b;
}
int main(){
    int n, k, total = 0;
    std::cin >> n >> k;
    int products[n];
    for(int i = 0; i < n; i++) {
        std::cin >> products[i];
    }
    std::sort(products, products + sizeof products / sizeof products[0], comparator);
    for(int i = 1; i <= n; i++) {
        if(i % k != 0) {
            total += products[i - 1];
        }
    }
    std::cout << total;
    return 0;
}
