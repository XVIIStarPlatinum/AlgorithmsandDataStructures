#include <bits/stdc++.h>
using namespace std;

bool comparator(const string &s1, const string &s2) {
    return s1 + s2 > s2 + s1;
}

int main(){
    vector<string> number;
    string num;

    while(cin >> num){
        if(num.length() == 0) break;
        number.push_back(num);
    }

    sort(number.begin(), number.end(), comparator);
    for(const auto & i : number){
        cout << i;
    }
    return 0;
}
