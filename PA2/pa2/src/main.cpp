#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<sstream>

using namespace std;

int m(vector<vector<int> >& M, vector<int>& E, int i, int j){
	int k = E[j];
	if(i >= j) return 0;
	if(M[i][j-i] > -1) return M[i][j-i];
	if(k == i) {
		M[i][j-i] =  m(M, E, i+1, j-1)+1;
		return M[i][j-i];
	}
	if(k > j || k < i){
		M[i][j-i] =  m(M, E, i, j-1);
		return M[i][j-i];
	}
	int p = m(M, E, i, j-1), q = m(M, E, i, k-1) + m(M, E, k+1, j-1)+1;
	if(p < q){
		M[i][j-i] = q;
		return q;
	}
	else{
		M[i][j-i] = p;
		return p;
	}
}

int _type(vector<vector<int> >& M, vector<int>& E, int i, int j){
	int max = 0, k = E[j];
	if(k == i)	return 0;
	else		max = m(M, E, i, j-1);
	if(k>i && k<j && m(M, E, i, k-1)+m(M, E, k+1, j-1)+1 > max) return 2;
	return 1;
}

int main(int argc, char* argv[]) {
    
	if(argc != 3) return 0;
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
	
	int n, i, j;
	fin >> n;
	vector<int> E(n, 0), chosen(n, 0);
	vector<vector<int> > M(n, vector<int>());
	for(i = 0; i < n; i++){
		M[i].resize(n-i);
		for(j = 0; j < n-i; j++){
			M[i][j] = -1;
		}
	}
	while(fin >> i >> j){
		E[i] = j;
		E[j] = i;
	}

	m(M, E, 0, n-1);
	
	queue<int> trace;
	trace.push(0);
	trace.push(n-1);
	while(!trace.empty()){
		i = trace.front();
		trace.pop();
		j = trace.front();
		trace.pop();
		if(_type(M,E,i,j)==0){
			if(m(M,E,i+1,j-1)){
				trace.push(i+1);
				trace.push(j-1);
			}
			chosen[i] = j;
			chosen[j] = i;
		}
		else if(_type(M,E,i,j)==1){
			if(m(M,E,i,j-1)){
				trace.push(i);
				trace.push(j-1);
			}
		}
		else{
			if(m(M,E,i,E[j]-1)){
				trace.push(i);
				trace.push(E[j]-1);
			}
			if(m(M,E,E[j]+1,j-1)){
				trace.push(E[j]+1);
				trace.push(j-1);
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
