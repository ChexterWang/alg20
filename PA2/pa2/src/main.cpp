#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<sstream>

using namespace std;

struct M{
	queue<M*> m;
	int e, w;
};

struct T{
	T* t;
	M* m;
	int w;
};

vector<int> e, e2id;
vector<queue<int> > bkt;
vector<M> _m;
vector<T> _t;

int main(int argc, char* argv[]) {
    
	if(argc != 3) return 0;
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
	
	int n, i, j, k;
	fin >> n;
	
	e.resize(n, 0);
	bkt.resize(n, queue<int>());
	_m.resize(n/2, M());
	_t.resize(n, T());
	e2id.resize(n, 0);
	
	k = 0;
	while(fin >> i >> j){
		e[i] = j;
		e[j] = i;
		i = (j>i) ? i : j;
		bkt[e[i]-i].push(i);
		e2id[i] = k;
		e2id[e[i]] = k;
		_m[k].e = i;
		_m[k].w = 1;
		++k;
	}

	T* tptr;
	T tmp = {.t = nullptr, .m = nullptr, .w = 0};
	for(int _len = 0; _len < n; ++_len){
		if(bkt[_len].empty()) continue;
		while(!bkt[_len].empty()){
			i = bkt[_len].front();
			bkt[_len].pop();
			if(_len<3) continue;
			_t[e[i]] = tmp;
			for(int k = e[i] - 1; k > i; --k){
				tptr = &_t[k];
				tptr->t = &_t[k+1];
				tptr->w = tptr->t->w;
				if(e[k] < k) continue;
				if(e[k] >= e[i]) continue;
				if(tptr->w < _m[e2id[k]].w + _t[e[k]+1].w){
					tptr->t = &_t[e[k]+1];
					tptr->m = &_m[e2id[k]];
					tptr->w = tptr->m->w + tptr->t->w;
				}
			}
			tptr = &_t[i+1];
			_m[e2id[i]].w = tptr->w+1;
			while(tptr->t){
				if(tptr->m)
					_m[e2id[i]].m.push(tptr->m);
				tptr = tptr->t;
			}
		}
	}
	vector<queue<int> >().swap(bkt);

	_t[n-1] = tmp;
	for(i = n-2; i > -1; --i){
		tptr = &_t[i];
		tptr->t = &_t[i+1];
		tptr->w = tptr->t->w;
		if(e[i] < i) continue;
		if(e[i]==n-1){
			if(_m[e2id[i]].w > tptr->w){
			tptr->t = &_t[n-1];
			tptr->m = &_m[e2id[i]];
			tptr->w = tptr->m->w;
			}
		}
		else if(_m[e2id[i]].w + _t[e[i]+1].w > tptr->w){
			tptr->t = &_t[e[i]+1];
			tptr->m = &_m[e2id[i]];
			tptr->w = tptr->m->w + tptr->t->w;
		}
	}

	M mis;
	tptr = &_t[0];
	while(tptr->t){
		if(tptr->m)
			mis.m.push(tptr->m);
		tptr = tptr->t;
	}
	tptr = nullptr;
	vector<T>().swap(_t);

	// use e2id as chosen
	fill(e2id.begin(), e2id.end(), 0);
	queue<M*> trace;
	M* mptr;
	while(!mis.m.empty()){
		trace.push(mis.m.front());
		mis.m.pop();
	}
	while(!trace.empty()){
		mptr = trace.front();
		trace.pop();
		if(mptr->m.empty()) e2id[mptr->e] = e[mptr->e];
		while(!mptr->m.empty()){
			trace.push(mptr->m.front());
			mptr->m.pop();
		}
	}
	mptr = nullptr;
		
	stringstream ss;
	j = 0;
	for(i = 0; i < n; ++i){
		if(e2id[i]){
			ss << i << ' ' << e2id[i] << '\n';
			++j;
		}
	}
	fout << j << '\n';
	fout << ss.str();
}
