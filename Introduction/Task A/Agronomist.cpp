#include<iostream>
using namespace std;

int main(){
    int a;
    int equal, maxStart, maxEnd, curStart, curEnd;
    equal = maxStart = maxEnd = curStart = curEnd = 0;
    cin >> a;
    int x[a];
    for(int i = 0; i < a; i++){
        cin >> x[i];
    }
    for(int i = 0; i < a; i++){
        if(x[i] == x[i-1]){
            equal++;
            if(equal == 3){
                if(curEnd - curStart > maxEnd - maxStart){
                    maxEnd = curEnd;
                    maxStart = curStart;
                }
                curStart = i - 1;
                equal = 2;
            }
        } else {
            equal = 1;
        }
        curEnd = i;
    }
    if(curEnd - curStart > maxEnd - maxStart){
        maxEnd = curEnd;
        maxStart = curStart;
    }
    cout << maxStart + 1 << " " << maxEnd + 1 << "\n";
    return 0;
}