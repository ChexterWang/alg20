#include<iostream>
#include<fstream>
#include "solver.h"

using namespace std;

typedef vector<pair<int, int> > Adj;

int main(int argc, char* argv[]){
	
	if(argc != 3) return 0;
	fstream fin(argv[1]);
	if(!fin.is_open()) return 0;
	fstream fout;
	fout.open(argv[2], ios::out);

	char _type;
	int v, e, i, j, k;
	fin >> _type;
	fin >> v;
	fin >> e;

	solver* p;
	if(_type == 'u')
		p = (solver*) new usolver(v, e);
	else if(_type == 'd')
		p = (solver*) new dsolver(v, e);
	
	while(fin >> i >> j >> k){
		(*p).operator()(i, j, k);
	}
	
	k = 0;
	(*p).solve();
	fout << (*p).result();
}
