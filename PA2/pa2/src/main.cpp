#include<iostream>
#include<fstream>
#include<stack>
#include<vector>
#include<sstream>

using namespace std;

int _type(vector<vector<int> >& M, vector<int>& E, int i, int j){
	int max = 0, k = E[j];
	if(k == i)	return 0;
	else		max = M[i][j-1];
	if(k > i && k < j && M[i][k-1]+M[k+1][j-1]+1 > max) return 2;
	return 1;
}

int main(int argc, char* argv[]) {
    if(argc != 3) return 0;
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
	int n;
	fin >> n;
	vector<vector<int> > M(n, vector<int>(n, 0));
//	vector<vector<int> > T(n, vector<int>(n, 0));
	vector<int> E(n, 0);
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
//				T[i][j] = 0;
            }
            else{
                max = M[i][j-1];
//				T[i][j] = 1;
            }
            if(k > i && k < j && M[i][k-1]+M[k+1][j-1]+1 > max) {
                max = M[i][k-1]+M[k+1][j-1]+1; 
//				T[i][j] = 2;
            } 
            M[i][j] = max;
        }
    }
    stack<int> traceback;
	vector<int> chosen(n, 0);
    traceback.push(n-1);
    traceback.push(0);
    while(!traceback.empty()){
        i = traceback.top();
        traceback.pop();
        j = traceback.top();
        traceback.pop();
//		if(T[i][j] == 0){
		if(_type(M,E,i,j)==0){
            if(M[i+1][j-1]){
                traceback.push(j-1);
                traceback.push(i+1);
            }
			chosen[i] = j;
			chosen[j] = i;
        }
//		else if(T[i][j] == 1){
		if(_type(M,E,i,j)==1){
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
			chosen[j] = E[j];
			chosen[E[j]] = j;
        }
    }
	stringstream ss;
	j = 0;
	for(i = 0; i < n; i++){
		if(chosen[i]) {
			ss << i << ' ' << chosen[i] << '\n';
			j++;
			chosen[chosen[i]] = 0;
		}
	}
	fout << j << '\n';
	fout << ss.str();
}
