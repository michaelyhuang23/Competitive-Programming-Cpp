#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>
#include<assert.h>
#include<fstream>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define mt make_tuple

int N, K, Q;
vector<int> A;
vector<pair<int,int> > queries;
vector<vector<int> > vecK;
vector<int> nxt;
vector<int> lst;
vector<int> ans;


void midsum(int l, int r, vector<int>& qq){
    //deb(mp(l,r))
    //deb(qq)
    if(l==r){
        for(int q : qq){
            ans[q] = 2;
        }
        return;
    }
	int m = (l+r)/2;
	//deb(mt(l,m,r))
	int ll = N;
	int rr = -1;
	vector<int> lq, rq, mq;
	for(int q : qq){
		if(queries[q].second <= m) lq.pb(q);
		else if(queries[q].first > m) rq.pb(q);
		else{ mq.pb(q); ll=min(ll,queries[q].first); rr=max(queries[q].second,rr);}
	}
	//deb(lq) deb(rq) deb(mq)
	if(lq.size()>0) midsum(l, m, lq);
	if(rq.size()>0) midsum(m+1, r, rq);
	if(mq.size()==0){
		return;
	}

	// [l,m], [m+1,r]
	vector<vector<vector<llong> > > dprs;
	dprs.pb(vector<vector<llong> >(r-m, vector<llong>(21,1))); // this is for empty
	for(int pk=1;pk<=K;pk++){
		vector<vector<llong> > dpr(r-m, vector<llong>(21,0));
		// we first exclude emptyset
		int i = *lower_bound(vecK[pk].begin(), vecK[pk].end(), m+1); // last should be N+1
		if(i>=N) {dprs.pb(dpr); continue;}
		for(;i<=r;i=nxt[i]){
			for(int k=pk;k<21;k++) dpr[i-m-1][k]=1;
		}
		// end at at most k
		for(int i=1;i<r-m;i++){
			int j = m+1 + i; 
			for(int k=0;k<=K;k++){
				int pi = i-1;
				int c = A[j];
				if(c == k){
					dpr[i][k]+=dpr[pi][k]+dpr[pi][k];
				}else if(c>k){
					dpr[i][k]+=dpr[pi][k];
				}else {
					dpr[i][k]+=dpr[pi][c]+dpr[pi][k];
				}
				if(dpr[i][k]>=MOD) dpr[i][k]-=MOD;
				if(dpr[i][k]>=MOD) dpr[i][k]-=MOD;
				//dpr[i][k]%=MOD;
			}
		}
		dprs.pb(dpr);
	}

	// deb(dprs[1])
	// deb(dprs[2])

	vector<vector<vector<llong> > > dpls;
	dpls.pb(vector<vector<llong> >(m-l+1, vector<llong>(21,1))); // this is for empty
	for(int pk=1;pk<=K;pk++){
		vector<vector<llong> > dpl(m-l+1, vector<llong>(21,0));
		// exclude emptyset
		auto ret = upper_bound(vecK[pk].begin(), vecK[pk].end(), m); // first elem is -1
		ret--;
		int i = *ret;
		if(i<0) {dpls.pb(dpl); continue;}
		for(;i>=l;i=lst[i]){
			for(int k=pk;k>=0;k--) dpl[m-i][k]=1;
		}
		// start at at least k
		for(int i=1;i<m-l+1;i++){
			int j = m-i; 
			int c = A[j];
			int pi = i-1;
			for(int k=0;k<=K;k++){
				if(c == k){
					dpl[i][k]+=dpl[pi][k]+dpl[pi][k];
				}else if(c>k){
					dpl[i][k]+=dpl[pi][k]+dpl[pi][c];
				}else {
					dpl[i][k]+=dpl[pi][k];
				}
				if(dpl[i][k]>=MOD) dpl[i][k]-=MOD;
				if(dpl[i][k]>=MOD) dpl[i][k]-=MOD;
			}
		}
		dpls.pb(dpl);
	}

	// deb(dpls[3])
	// deb(dpls[2])
	// deb(dpls[1])

	for(int pk=1;pk<=K;pk++)
		for(int i=0;i<dpls[pk].size();i++){ // sum only last
			dpls[pk][i][0] += dpls[pk-1][i][0];
			dpls[pk][i][0] %= MOD;
		}

	for(int q : mq){
		int a = queries[q].first;
		int b = queries[q].second;
		llong sum = 0;
		for(int pk=1;pk<=K;pk++){ // mind start
			sum += (dprs[pk][b-m-1][K]*dpls[pk][m-a][0])%MOD;
			sum %= MOD;
		}
		sum += dpls[K][m-a][0]; // this is for right hand side = empty
		sum %= MOD;
		ans[q] = sum;
	}

}


int main(){
	ios_base::sync_with_stdio(0);
	ifstream fin("nondec.in");
	ofstream fout("nondec.out");
	fin.tie(0);
	fin >> N >> K;
	A = vector<int>(N);
	for(int i=0;i<N;i++) fin >> A[i];

	vecK = vector<vector<int> >(21, {-1});
	for(int i=0;i<N;i++) vecK[A[i]].pb(i);
	for(int i=0;i<21;i++) vecK[i].pb(N+1);

	nxt = vector<int>(N,N+1);
	lst = vector<int>(N,-1);

	for(int i=0;i<N;i++){
		auto ret = lower_bound(vecK[A[i]].begin(), vecK[A[i]].end(), i);
		ret++; nxt[i] = *ret;
	}

	for(int i=0;i<N;i++){
		auto ret = lower_bound(vecK[A[i]].begin(), vecK[A[i]].end(), i);
		ret--; lst[i] = *ret;
	}

    //deb(nxt) deb(lst) deb(vecK)

	fin >> Q;
	ans = vector<int>(Q,-1);
    queries = vector<pair<int,int> >(Q);
	// How do we keep the queries? 
	// if we iterate through them at each level, we have additional Qlog(Q)
	for(int i=0;i<Q;i++){
		int a,b; fin >> a >> b; a--; b--;
		queries[i] = mp(a,b);
	}
	vector<int> qq(Q);
	for(int i=0;i<Q;i++) qq[i] = i;
	midsum(0, N-1, qq);
	for(int i=0;i<Q;i++) fout<<ans[i]<<endl;

	fout.close();
}


