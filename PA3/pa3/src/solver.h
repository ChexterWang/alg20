#include<iostream>
#include<vector>
#include<utility>

using namespace std;

typedef vector<pair<int, int> > Adj;

class solver{

public:
	solver(int _v, int _e) : v(_v), e(_e), w(false) {
		ret.resize(_v, Adj());
	}
	virtual void operator () (int _i, int _j, int _w) {}
	void add(int _i, int _j, int _w) {
		ret[_i].push_back(pair<int, int>(_j, _w));
	}
	virtual void solve() {}
	vector<Adj> getRet() { return ret; }
	int getV() { return v; }
	int getE() { return e; }
	void setW() { w = true; }
	bool isWeighted() { return w; }

private:
	int v, e;
	bool w;
	vector<Adj> ret;
};

class usolver : public solver{

public:
	usolver(int _v, int _e) : solver(_v, _e) {}
	void operator () (int _i, int _j, int _w){
//		cout << "u " << _i << ", " << _j << ", " << _w << '\n';
		if(_w!=1) setW();
	}
	void solve();

private:
};


class dsolver : public solver{

public:
	dsolver(int _v, int _e) : solver(_v, _e) {
		in.resize(_v, Adj());
		out.resize(_v, Adj());
	}
	void operator () (int _i, int _j, int _w){
//		cout << "d " << _i << ", " << _j << ", " << _w << '\n';
		if(_w!=1) setW();
		in[_j].push_back(pair<int, int>(_i, _w));
		out[_i].push_back(pair<int, int>(_j, _w));
	}
	void print();
	void solve();
	
private:
	vector<Adj> in;
	vector<Adj> out;
};
