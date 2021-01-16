#include<iostream>
#include<vector>
#include<utility>
#include "solver.h"

using namespace std;

typedef vector<pair<int, int> > Adj;

/* -- function for disjointSet -- */
disjointSet::disjointSet(int i)
{
	rank = new int[i];
	parent = new int[i];
	n = i;
	makeSet();
}

void disjointSet::makeSet()
{ for (int i = 0; i < n; i++) parent[i] = i; }

int disjointSet::findSet(int x)
{
	if (parent[x] != x) parent[x] = findSet(parent[x]);
	return parent[x];
}

void disjointSet::Union(int x, int y)
{
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
void usolver::solve() {
	/* 
	*  The minimum feedback arc set for undirected graph is
	*  the complementary of maximum spanning tree, we would
	*  find our maximum spanning tree using Kruskal's algo-
	*  rithm since we can use non-comparison sort for cases
	*  that have maximum input number.
	*/

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

void dsolver::solve() {
	;
}
