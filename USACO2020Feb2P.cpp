#include<iostream>
#include<algorithm>
#include<assert.h>
#include<vector>
#include<fstream>

//#include "debughelp.hpp"

using namespace std;

#define mp make_pair
#define pb push_back
#define mt make_tuple

vector<vector<bool> > mat;
vector<pair<int,int> > ptrs;
vector<vector<int> > hori, verti;

bool cmp(pair<int,int> l, pair<int,int> r){
	if(l.second==r.second) return l.first<r.first;
	else return l.second<r.second;
}

int main(){
	ios_base::sync_with_stdio(0);
	ifstream fin("triangles.in");
	ofstream fout("triangles.out");
	fin.tie(0);
	int n; fin >> n;
	int N = 2*n;
	ptrs = vector<pair<int,int> >();
	mat = vector<vector<bool> >(N);
	for(int i=0;i<N;i++) mat[i] = vector<bool>(N,0);
	for(int r=0; r < n; r++){
		string ss; fin >> ss;
		for(int c=0; c<n; c++){
			if(ss[c] == '*'){
				int rp = r+c;
				int cp = r-c+n;
				assert(rp<N);
				assert(cp>=0);
				assert(cp<N);
				ptrs.pb(mp(rp,cp));
				mat[rp][cp] = true;
			}
		}
	}

    //deb(mat);
    //deb(ptrs);

	hori = vector<vector<int> >(N);
	verti = vector<vector<int> >(N);
	for(int i=0;i<N;i++) hori[i] = vector<int>(N,0);
	for(int i=0;i<N;i++) verti[i] = vector<int>(N,0);
	for(int r=0;r<N;r++) {
		hori[r][0] = mat[r][0];
		for(int c=1;c<N;c++) hori[r][c] = hori[r][c-1] + mat[r][c];
	}
	for(int c=0;c<N;c++){
		verti[0][c] = mat[0][c];
		for(int r=1;r<N;r++) verti[r][c] = verti[r-1][c] + mat[r][c];
	}
	sort(ptrs.begin(),ptrs.end(),cmp);
    //cout<<"start"<<endl;
	long long counter = 0;
	for(auto pp : ptrs){
		int r = pp.first;
		int c = pp.second;
		for(int cc = c-1; cc>=0; cc--){
			if(!mat[r][cc]) continue;
			int dist = c-cc;
			int rt = r+dist;
			int rb = r-dist;
            //deb(r); deb(c); deb(cc); deb(rt); deb(rb);
			if(rt<N){
                int back = 0;
                if(cc>=1) back = hori[rt][cc-1];
                counter += hori[rt][c] - back;
            }
			if(rb>=0){
                int back = 0;
                if(cc>=1) back = hori[rb][cc-1];
                counter += hori[rb][c] - back;
            }
		}
	}
    //cout<<"start2"<<endl;
	sort(ptrs.begin(),ptrs.end());
	for(auto pp : ptrs){
		int r = pp.first;
		int c = pp.second;
		for(int rr = r-1; rr>=0; rr--){
			if(!mat[rr][c]) continue;
			int dist = r-rr;
			int ct = c+dist;
			int cb = c-dist;
            //deb(r); deb(c); deb(rr); deb(ct); deb(cb);
			if(ct<N){
                int back = 0;
                if(rr>=1) back = verti[rr-1][ct];
                counter += verti[r][ct] - back;
            }
			if(cb>=0){
                int back = 0;
                if(rr>=1) back = verti[rr-1][cb];
                counter += verti[r][cb] - back;
            }
		}
	}
    for(auto pp : ptrs){
        int r = pp.first;
        int c = pp.second;
        for(int i = 1; i < N; i++){
            if(r+i>=N || c+i>=N) break;
            if(mat[r][c+i] && mat[r+i][c]) counter--;
        }
        for(int i = 1; i < N; i++){
            if(r+i>=N || c-i<0) break;
            if(mat[r][c-i] && mat[r+i][c]) counter--;
        }
        for(int i = 1; i < N; i++){
            if(r-i<0 || c+i>=N) break;
            if(mat[r][c+i] && mat[r-i][c]) counter--;
        }
        for(int i = 1; i < N; i++){
            if(r-i<0 || c-i<0) break;
            if(mat[r][c-i] && mat[r-i][c]) counter--;
        }
    }
	fout<<counter<<endl;
	fout.close();
}


