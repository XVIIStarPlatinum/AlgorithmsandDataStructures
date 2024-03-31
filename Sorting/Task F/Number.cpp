#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool comparator(const std::string &s1, const std::string &s2) {
    return s1 + s2 > s2 + s1;
}

int main(){
    std::vector<std::string> number;
    std::string num;

    while(std::cin >> num){
        if(num.empty()) break;
        number.push_back(num);
    }

    std::sort(number.begin(), number.end(), comparator);
    for(const auto & i : number){
        std::cout << i;
    }
    return 0;
}
