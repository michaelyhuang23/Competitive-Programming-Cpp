#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define mp make_pair
#define pb push_back
#define print(x) cout<<x<<endl
#define inf 1000000000000000LL

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


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong n; cin >> n;
	vector<llong> arr(n);
	for(llong i=0;i<n;i++) cin >> arr[i];
	segtree<NodeN> tr(arr, n);
	llong m; cin >> m;
	for(llong i=0;i<m;i++){
		llong x, y; cin >> x >> y;
		x--; y--;
		llong ans = tr.query(x,y);
		print(ans);
	}
}









/*

segtree with D&C? No need for segtree exactly, just merging. All merging can be framed as segtree?


*/