#include<iostream>
#include<vector>
#include<utility>
#include<sstream>

using namespace std;

typedef vector<pair<int, int> > Adj;

class edge;
class disjointSet;
class solver;
class dsolver;
class usolver;

class edge {
public:
	int s, d, w;
};

class disjointSet {
public:
    disjointSet(int i);
    void makeSet();
    int findSet(int x);
    void Union(int x, int y);
private:
    int *rank, *parent, n;
};

class solver{

public:
	solver(int _v, int _e) : v(_v), e(_e), w(false) {}
	virtual void operator () (int _i, int _j, int _w) {}
	virtual void solve() {}
	virtual string result(){}
	int getV() { return v; }
	int getE() { return e; }
	void setW() { w = true; }
	bool isWeighted() { return w; }

private:
	int v, e;
	bool w;
};

class usolver : public solver{

public:
	usolver(int _v, int _e) : solver(_v, _e) {
		e = new edge[_e];
	}
	void operator () (int _i, int _j, int _w){
		// cout << "u " << _i << ", " << _j << ", " << _w << '\n';
		if(_w!=1) setW();
		e[edgeAdded].s = _i;
		e[edgeAdded].d = _j;
		e[edgeAdded++].w = _w;
	}
	void solve();
	string result();

private:
	int edgeAdded = 0;
	edge* e;
};


class dsolver : public solver{

public:
	dsolver(int _v, int _e) : solver(_v, _e) {
		in.resize(_v, Adj());
		out.resize(_v, Adj());
	}
	void operator () (int _i, int _j, int _w){
		// cout << "d " << _i << ", " << _j << ", " << _w << '\n';
		if(_w!=1) setW();
		in[_j].push_back(pair<int, int>(_i, _w));
		out[_i].push_back(pair<int, int>(_j, _w));
	}
	void print();
	void solve();
	string result();
	
private:
	vector<Adj> in;
	vector<Adj> out;
	vector<Adj> ret;
};
