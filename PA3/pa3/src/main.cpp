#include<iostream>
#include<fstream>
#include<sstream>
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
//	cout << p->isWeighted() << "\n";
	
	k = 0;
	(*p).solve();
	vector<Adj> ret = p->getRet();
	stringstream ss;
	for(i = 0; i < ret.size(); ++i){
		for(j = 0; j < ret[i].size(); ++j){
			ss << i << ' ' << ret[i][j].first << ' ' << ret[i][j].second << '\n';
			k += ret[i][j].second;
		}
	}
	fout << k << '\n';
	fout << ss.str();

}