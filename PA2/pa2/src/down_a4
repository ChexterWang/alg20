#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include<sstream>

using namespace std;

static unsigned short mask[16] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768};

class A{
public:
	A(){ memset(i, 65535, 17*sizeof(short)); }
	unsigned int operator() (short j){
		return (i[16]&mask[15-j]) ? i[j]+65536 : i[j];
	}
	void operator() (short j, int num){
		i[16] = (num&65536) ? i[16]|mask[15-j] : i[16]&(65535-mask[15-j]);
		i[j] = num&65535;
	}
private:
	unsigned short i[17];
};

int m(int i, int j){
	if(i >= j) return 0;
	unsigned short q = (j-i)/16, r = (j-i)%16;
	extern vector<vector<A> > M;
	extern vector<int> E;
	if(M[i][q](r) != 131071) return M[i][q](r);
	unsigned int k = E[j];
	if(k == i)
		M[i][q](r, m(i+1, j-1)+1);
	else if(k > j || k < i)
		M[i][q](r, m(i, j-1));
	else{
		int u = m(i, j-1), v = m(i, k-1) + m(k+1, j-1)+1;
		if(u < v) M[i][q](r, v);
		else M[i][q](r, u);
	}
	return M[i][q](r);
}

void _m(int i, int j){
	extern vector<int> E;
	extern vector<int> chosen;
	unsigned int k = E[j];
	if(k == i){
		chosen[i] = j;
		chosen[j] = i;
		if(m(i+1, j-1)) _m(i+1, j-1);
	}
	else if(k>j || k<i){
		if(m(i, j-1)) _m(i, j-1);
	}
	else{
		if(m(i, k-1)+m(k+1, j-1)+1 > m(i, j-1)){
			chosen[k] = j;
			chosen[j] = k;
			if(m(i, k-1))   _m(i, k-1);
			if(m(k+1, j-1)) _m(k+1, j-1);
		}
		else _m(i, j-1);
	}
}

vector<int> E, chosen;
vector<vector<A> > M;

int main(int argc, char* argv[]) {
    
	if(argc != 3) return 0;
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
	
	int n, i, j;
	fin >> n;
	E.resize(n, 0);
	chosen.resize(n, 0);
	M.resize(n, vector<A>());
	for(i = 0; i < n; ++i){
		M[i].resize((n-i)/16+1, A());
	}
	while(fin >> i >> j){
		E[i] = j;
		E[j] = i;
	}

	m(0, n-1);
	_m(0, n-1);	

	stringstream ss;
	j = 0;
	for(i = 0; i < n; ++i){
		if(chosen[i]){
			ss << i << ' ' << chosen[i] << '\n';
			++j;
			chosen[chosen[i]] = 0;
		}
	}
	fout << j << '\n';
	fout << ss.str();
}
