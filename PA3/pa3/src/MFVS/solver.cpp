#include<iostream>
#include<vector>
#include<utility>
#include "solver.h"

using namespace std;

typedef vector<pair<int, int> > Adj;

void dsolver::reduction() {
	print();
	in0(0);
	in0(6);
	print();
	out0(7);
	out0(5);
	print();
	out1(5);
	print();
	in1(4);
	print();
	loop(6);
	print();
}

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
void dsolver::in0(int i){
	if(!in[i].empty()) return;
	while(!out[i].empty()){
		Adj* p = &in[out[i][0].first];
		if(p->empty()) continue;
		for(int n = 0; n < p->size(); ++n){
//				cout << p->at(n).first << "\n";
			if(p->at(n).first == i){
				p->at(n) = p->at(p->size()-1);
				p->pop_back();
				break;
			}
		}
		out[i][0] = out[i][out[i].size()-1];
		out[i].pop_back();
	}
	out[i].resize(0);
}
void dsolver::out0(int i){
	if(!out[i].empty()) return;
	while(!in[i].empty()){
		Adj* p = &out[in[i][0].first];
		if(p->empty()) continue;
		for(int n = 0; n < p->size(); ++n){
//				cout << p->at(n).first << "\n";
			if(p->at(n).first == i){
				p->at(n) = p->at(p->size()-1);
				p->pop_back();
				break;
			}
		}
		in[i][0] = in[i][in[i].size()-1];
		in[i].pop_back();
	}
}
void dsolver::in1(int i){
	if(in[i].size()!=1) return;
	int j = in[i][0].first, wi = in[i][0].second;
	cout << j << ", " << i << ", " << wi << "\n";
	while(!out[i].empty()){
		cout << out[i][0].first << "\n";
		Adj* p = &in[out[i][0].first];
		int wo = 0;
		bool pre2suc = false;
		for(int m = 0; m < p->size(); ++m){
			if(p->at(m).first == j){
				pre2suc = true;
				break;
			}
			if(p->at(m).first == i){
				wo = p->at(m).second;
				p->at(m) = p->at(p->size()-1);
				p->pop_back();
				--m;
			}
		}
		if(!pre2suc){
			if(isWeighted()){
				p->push_back(pair<int, int>(j, wi+wo));
				out[j].push_back(pair<int, int>(out[i][0].first, wi+wo));
			}
			else{
				p->push_back(pair<int, int>(j, 1));
				out[j].push_back(pair<int, int>(out[i][0].first, 1));
			}
		}
		out[i][0] = out[i][out[i].size()-1];
		out[i].pop_back();
	}
	for(int m = 0; m < out[j].size(); ++m){
		if(out[j][m].first = i){
			out[j][m] = out[j][out[j].size()-1];
			out[j].pop_back();
			break;
		}
	}
	in[i].pop_back();
}
void dsolver::out1(int i){
	if(out[i].size()!=1) return;
	int j = out[i][0].first, wo = out[i][0].second;
//	cout << i << ", " << j << ", " << wo << "\n";
	while(!in[i].empty()){
//		cout << in[i][0].first << "\n";
		Adj* p = &out[in[i][0].first];
		int wi = 0;
		bool pre2suc = false;
		for(int m = 0; m < p->size(); ++m){
			if(p->at(m).first == j){
				pre2suc = true;
				break;
			}
			if(p->at(m).first == i){
				wi = p->at(m).second;
				p->at(m) = p->at(p->size()-1);
				p->pop_back();
				--m;
			}
		}
		if(!pre2suc){
			if(isWeighted()){
				p->push_back(pair<int, int>(j, wi+wo));
				in[j].push_back(pair<int, int>(in[i][0].first, wi+wo));
			}
			else{
				p->push_back(pair<int, int>(j, 1));
				in[j].push_back(pair<int, int>(in[i][0].first, 1));
			}
		}
		in[i][0] = in[i][in[i].size()-1];
		in[i].pop_back();
	}
	for(int m = 0; m < in[j].size(); ++m){
		if(in[j][m].first = i){
			in[j][m] = in[j][in[j].size()-1];
			in[j].pop_back();
			break;
		}
	}
	out[i].pop_back();
}
void dsolver::loop(int i){
	;
}
