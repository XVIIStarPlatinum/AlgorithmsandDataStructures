#include<iostream>
using namespace std;

int main(){
    int a;
    int equal, mStart, mEnd, curStart, curEnd;
    equal = mStart = mEnd = curStart = curEnd = 0;
    cin >> a;
    int x[a];
    for(int i = 0; i < a; i++){
        cin >> x[i];
    }
    for(int i = 0; i < a; i++){
        if(x[i-1] == x[i]){
            equal++;
            if(equal == 3){
                if(curEnd - curStart > mEnd - mStart){
                    mEnd = curEnd;
                    mStart = curStart;
                }
                curStart = i - 1;
                equal = 2;
            }
        } else {
            equal = 1;
        }
        curEnd = i;
    }
    if(curEnd - curStart > mEnd - mStart){
        mEnd = curEnd;
        mStart = curStart;
    }
    cout << mStart + 1 << " " << mEnd + 1 << endl;
    return 0;
}