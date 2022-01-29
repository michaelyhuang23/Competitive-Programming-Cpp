#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 1000000000LL


struct NodeN{
	llong sum;
	llong p, s, a;
	NodeN(){sum = -inf; p = -inf; s = -inf; a = -inf;}
	NodeN(llong val){
		sum = val;
		p = val;
		s = val;
		a = val;
	}
	NodeN merge(NodeN r){
		NodeN m;
		m.sum = sum+r.sum;
		m.p = max(p, sum+r.p);
		m.s = max(r.s, r.sum+s);
		m.a = max({a,r.a,s+r.p});
		return m;
	}
};

struct NodeP{
	llong sum;
	llong p, a;
	NodeP(){sum = 0; p = -inf;}
	NodeP(llong val){
		sum = val;
		p = val;
		a = p;
	}
	NodeP merge(NodeP r){
		NodeP m;
		m.sum = sum+r.sum;
		m.p = max(p, sum+r.p);
		m.a = m.p;
		return m;
	}
};

struct NodeS{
	llong sum;
	llong s, a;
	NodeS(){sum = 0; s = -inf;}
	NodeS(llong val){
		sum = val;
		s = val;
		a = s;
	}
	NodeS merge(NodeS r){
		NodeS m;
		m.sum = sum+r.sum;
		m.s = max(r.s, r.sum+s);
		m.a = m.s;
		return m;
	}
};


template <class N>
struct segtree{
	vector<N> tree;
	llong n;
	llong pow_up(llong n){
		for(llong i=0;i<32;i++) if((1<<i)>=n) return 1<<i;
		return -1;
	}
	segtree(vector<llong>& arr, llong n_){
		n = pow_up(n_);
		tree = vector<N>(n*2);
		for(llong i=0;i<n_;i++){
			tree[n+i] = N(arr[i]);
		}
		build();
	}
	void pull_up(llong i){
		tree[i] = tree[i*2].merge(tree[i*2+1]);
	}
	void build(){
		for(llong i=n-1;i>=1;i--) pull_up(i);
	}
	llong query(llong l, llong r){
		N ll, rr;
		for(l+=n, r+=n; l<=r; l/=2, r/=2){
			if(l&1) ll = ll.merge(tree[l++]);
			if(!(r&1)) rr = tree[r--].merge(rr);
			if(l == r) break;
		}
		N mm = ll.merge(rr);
		return mm.a;
	}
};



llong tt;
llong N,M;
vector<llong> A;
vector<llong> pref;
void solve(){
	cin >> N;
	A = vector<llong>(N);
	pref = vector<llong>(N);
	for(llong i=0;i<N;i++) cin >> A[i];
	pref[0] = A[0];
	for(llong i=1;i<N;i++) pref[i]=pref[i-1]+A[i];
	cin >> M;
	segtree<NodeP> ptree(A,N);
	segtree<NodeS> stree(A,N);
	segtree<NodeN> ntree(A,N);

	//deb(stree.query(2,3))
	for(llong i=0;i<M;i++){
		llong x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		x1--; y1--; x2--; y2--;
		llong maxx = -inf;
		if(x2<=y1) {
			maxx = max(maxx,ntree.query(x2, y1));
			//deb(ntree.query(x2,y1));
			if(x1 != x2) maxx = max(maxx, stree.query(x1,x2-1) + ptree.query(x2,y2));
			//deb(stree.query(x1,x2-1) + ptree.query(x2,y2))
			if(y1 != y2) maxx = max(maxx, ptree.query(y1+1,y2) + stree.query(x1,y1));
			//deb(ptree.query(y1+1,y2) + stree.query(x1,y1))
		}else{
			maxx = max(maxx,pref[x2-1] - pref[y1] + stree.query(x1, y1) + ptree.query(x2, y2));
		}
		print(maxx);
	}
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cin >> tt;
	while(tt--){
		solve();
	}
}