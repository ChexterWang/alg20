#include<iostream>
#include<fstream>
#include<stack>

using namespace std;

int main(int argc, char* argv[]) {
    if(argc != 3) return 0;
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
	int n;
	fin >> n;
	int M[n][n], E[n], T[n][n];
	std::fill((int*)M, (int*)M+sizeof(M)/sizeof(int), 0);
	std::fill((int*)E, (int*)E+sizeof(E)/sizeof(int), 0);
	std::fill((int*)T, (int*)T+sizeof(T)/sizeof(int), 0);
	int i, j;
    while(fin >> i >> j) {
        E[i] = j;
        E[j] = i;
	}
    for(int l = 0; l < n-1; l++){
        for(i = 0; i < n-l-1; i++){
            j = i+l+1;
            int max = 0, k = E[j];
            if(k == i){
                max =  M[i+1][j-1]+1;
                T[i][j] = 0;
            }
            else{
                max = M[i][j-1];
                T[i][j] = 1;
            }
            if(k > i && k < j && M[i][k-1]+M[k+1][j-1]+1 > max) {
                max = M[i][k-1]+M[k+1][j-1]+1; 
                T[i][j] = 2;
            } 
            M[i][j] = max;
        }
    }
    for(j = 0; j < n; j++){
        for(i = 0; i < n; i++){
            cout << M[j][i] << ", ";
        }
        cout << "\n";
    }
    stack<int> traceback;
    traceback.push(n-1);
    traceback.push(0);
    while(!traceback.empty()){
        i = traceback.top();
        traceback.pop();
        j = traceback.top();
        traceback.pop();
        if(T[i][j] == 0){
            if(M[i+1][j-1]){
                traceback.push(j-1);
                traceback.push(i+1);
            }
            cout << i << ", " << j << "\n";
        }
        else if(T[i][j] == 1){
            if(M[i][j-1]){
                traceback.push(j-1);
                traceback.push(i);
            }
        }
        else {
            if(M[i][E[j]-1]){
                traceback.push(E[j]-1);
                traceback.push(i);
            }
            if(M[E[j]+1][j-1]){
                traceback.push(j-1);
                traceback.push(E[j]+1);
            }
            cout << j << ", " << E[j] << "\n";
        }
    }
}
