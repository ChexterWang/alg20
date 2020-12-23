#include<iostream>
#include<vector>
#include<utility>

using namespace std;

typedef vector<pair<int, int> > Adj;

class solver{

public:
	solver(int _v, int _e) : v(_v), e(_e), w(false) {}
	virtual void operator () (int _i, int _j, int _w) {}
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
	usolver(int _v, int _e) : solver(_v, _e) {}
	void operator () (int _i, int _j, int _w){
//		cout << "u " << _i << ", " << _j << ", " << _w << '\n';
		if(_w!=1) setW();
	}

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
	void reduction();
	void print();
	
private:
	vector<Adj> in;
	vector<Adj> out;
	void in0(int i);
	void out0(int i);
	void in1(int i);
	void out1(int i);
	void loop(int i);
};
