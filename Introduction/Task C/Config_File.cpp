#include<bits/stdc++.h>
#include<string>
using namespace std;

int main(){
    int hash = 0;
    map<string, int> hashMap;

    const int CACHE_PERIOD = 1000;
    vector<map<int,int>> callStack;
    callStack.emplace_back();
    string input;
    while(cin >> input){
        if(input == "-") {
            break;
        }
        if(input == "{") {
            if(callStack.size() % CACHE_PERIOD == 0){
                map<int,int> tmp;
                for(int i = (int) callStack.size() - CACHE_PERIOD; i < callStack.size(); i++){
                    for(auto &var : callStack[i]){
                        tmp[var.first] = var.second;
                    }
                }
                callStack.emplace_back(tmp);
            } else {
                callStack.emplace_back();
            }
        } else if(input == "}"){
            callStack.pop_back();
        } else {
            int del = (int) input.find('=');
            string left = input.substr(0, del);
            string right = input.substr(del + 1);
            if(hashMap.count(left) == 0)
                hashMap[left] = hash++;
            int lHash = hashMap[left];
            if(right.find_first_of("0123456789") != string::npos) {
                callStack.back()[lHash] = stoi(right);
            } else {
                if(hashMap.count(right) == 0){
                    hashMap[right] = hash++;
                }
                int rHash = hashMap[right];
                for(int i = callStack.size() - 1; i >= 0; i--){
                    if(callStack[i].count(rHash)) {
                        callStack.back()[lHash] = callStack[i][rHash];
                        cout << callStack[i][rHash] << "\n";
                        break;
                    }
                    if(i % CACHE_PERIOD == 0){
                        callStack.back()[lHash] = 0;
                        cout << "0" << "\n";
                    }
                }
            }
        }
    }
    return 0;
}
