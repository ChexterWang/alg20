#include<iostream>
#include<vector>
#include<utility>
#include<sstream>
#include<cstdlib>
#include<string>
#include<deque>
#include "solver.h"

using namespace std;

typedef vector<pair<int, int> > Adj;

/* -- function for disjointSet -- */
disjointSet::disjointSet(int i) {
	rank = new int[i];
	parent = new int[i];
	n = i;
	makeSet();
}

void disjointSet::makeSet(){
	for (int i = 0; i < n; i++){
		parent[i] = i;
		rank[i] = 0;
	}
}

int disjointSet::findSet(int x) {
	if (parent[x] != x) parent[x] = findSet(parent[x]);
	return parent[x];
}

void disjointSet::Union(int x, int y) {
	int xset = findSet(x);
	int yset = findSet(y);
	if      (xset == yset) return;
	if      (rank[xset] < rank[yset]) parent[xset] = yset;
	else if (rank[xset] > rank[yset]) parent[yset] = xset;
	else {
		parent[yset] = xset;
		rank[xset] = rank[xset] + 1;
	}
}

/* -- function for usolver -- */

int comp(const void* a, const void* b){
	return ((edge*)a)->w < ((edge*)b)->w;
}

void usolver::solve() {
	/* 
	*  The minimum feedback arc set for undirected graph is
	*  the complementary of maximum spanning tree, we would
	*  find our maximum spanning tree using Kruskal's algo-
	*  rithm since we can use non-comparison sort for cases
	*  that have maximum input number.
	*/
	int x = 0, y = 0;
	edge next;
	qsort(e, getE(), sizeof(edge), comp);
	disjointSet d = disjointSet(getV());
	for(int i = 0; i < getE();) {
		next = e[i++];
		x = d.findSet(next.s);
		y = d.findSet(next.d);
		if(x != y){
			b[i-1] = false;
			d.Union(x, y);
		}
	}
}

string usolver::result(){
	stringstream ss;
	int w = 0;
	for(int i = 0; i < getE(); ++i){
		if(b[i]){
			ss << e[i].s << ' ' << e[i].d << ' ' << e[i].w << '\n';
			w += e[i].w;
		}
	}
	return to_string(w) + "\n" + ss.str();
}

/* -- function for dsolver -- */
void dsolver::print() {
	int icnt = 0, ocnt = 0;
	cout << "in list:\n";
	for(int m = 0; m < getV(); ++m){
		if(in[m].empty()) continue;
		for(int n = 0; n < in[m].size(); ++n){
			cout << "(" << in[m][n].first << ", " << m << ", " << in[m][n].second << ") ";
			++icnt;
			if(icnt%5 == 0) cout << "\n";
		}
	}
	cout << "\nout list:\n";
	for(int m = 0; m < getV(); ++m){
		if(out[m].empty()) continue;
		for(int n = 0; n < out[m].size(); ++n){
			cout << "(" << m << ", " << out[m][n].first << ", " << out[m][n].second << ") ";
			++ocnt;
			if(ocnt%5 == 0) cout << "\n";
		}
	}
	cout << "\n" << icnt << ", " << ocnt << "\n";
}

void dsolver::deleteSource(vector<Adj>& _i, vector<Adj>& _o, int k){
	for(int j = 0; j < _o[k].size(); ++j){
		vector<pair<int, int> >::iterator it;
		int p = _o[k][j].first;
		for(int m = 0; m < _i[p].size(); ++m){
			if(_i[p][m].first == k){
				_i[p][m] = _i[p][_i[p].size()-1];
				_i[p].pop_back();
				break;
			}
		}
	}
	_o[k] = Adj();
}

void dsolver::deleteSink(vector<Adj>& _i, vector<Adj>& _o, int k){
	for(int j = 0; j < _i[k].size(); ++j){
		int p = _i[k][j].first;
		for(int m = 0; m < _o[p].size(); ++m){
			if(_o[p][m].first == k){
				_o[p][m] = _o[p][_o[p].size()-1];
				_o[p].pop_back();
				break;
			}
		}
	}
	_i[k] = Adj();
}

void dsolver::solve() {
	bool containSink = true, containSource = true;
	deque<int> s1, s2, G;
	vector<Adj> _i = in, _o = out;
	for(int i = 0; i < getV(); ++i) G.push_back(i);
	while(!G.empty()){
		while(containSink){
			containSink = false;
			for(deque<int>::iterator i = G.begin(); i != G.end();){
				if(!sink(_i, _o, *i)){ ++i; continue; }
				s2.push_front(*i);
				deleteSink(_i, _o, *i);
				i = G.erase(i);
				containSink = true;
			}
		}
		while(containSource){
			containSource = false;
			for(deque<int>::iterator i = G.begin(); i != G.end();){
				if(!source(_i, _o, *i)){ ++i; continue; }
				s1.push_back(*i);
				deleteSource(_i, _o, *i);
				i = G.erase(i);
				containSource = true;
			}
		}
		deque<int>::iterator maxIt = G.begin();
		int  maxDelta = 0;
		for(deque<int>::iterator i = G.begin(); i != G.end(); ++i){
			if(delta(_i, _o, *i) > maxDelta){
				maxIt = i;
				maxDelta - delta(_i, _o, *i);
			}
		}
		s1.push_back(*maxIt);
		deleteSink(_i, _o, *maxIt);
		deleteSource(_i, _o, *maxIt);
		G.erase(maxIt);
	}
	while(!s1.empty()){
		s.push_back(s1.front());
		s1.pop_front();
	}
	while(!s2.empty()){
		s.push_back(s2.front());
		s2.pop_front();
	}
}

string dsolver::result() {
	vector<int> ss;
	stringstream sss;
	int k = 0;
	ss.resize(getV(), 0);
	for(int i = 0; i < s.size(); ++i){
		cout << i << ", " << s[i] << '\n';
		ss[s[i]] = i;
	}
	for(int i = 0; i < s.size(); ++i){
		for(int j = 0; j < out[s[i]].size(); ++j){
			if(ss[out[s[i]][j].first] < i){
				sss << s[i] << ' ' << out[s[i]][j].first << ' ' << out[s[i]][j].second << '\n';
				k += out[s[i]][j].second;
			}
		}
	}
	return to_string(k) + '\n' + sss.str();
}
