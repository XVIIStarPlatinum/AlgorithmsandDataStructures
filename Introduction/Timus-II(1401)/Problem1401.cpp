#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int cnt = 3, arr[512][512];
void place(int sz, int x, int y, int nx, int ny){
    if(sz == 2) {
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                if(x + i != nx || y + j != ny){
                    arr[x + i][y + j] = cnt++ / 3;
                }
            }
        }
        return;
    }
    int hsz = sz / 2;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            if(x + i * hsz > nx || nx >= x + hsz * (i + 1) || y + j * hsz > ny || ny >= y + hsz * (j + 1)){
                arr[x + hsz + i - 1][y + hsz + j - 1] = cnt++ / 3;
            }
        }
    }
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            (x + i * hsz <= nx && nx < x + hsz * (i + 1) && y + j * hsz <= ny && ny < y + hsz * (j + 1)) ?
            place(hsz, x + i * hsz, y + j * hsz, nx, ny) :
            place(hsz, x + i * hsz, y + j * hsz, x + hsz + i - 1, y + hsz + j - 1);
        }
    }
}
int main(){
    int n, x, y;
    cin >> n >> x >> y;
    int s = (int) pow(2, n);
    place(s, 0, 0, x - 1, y - 1);
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
