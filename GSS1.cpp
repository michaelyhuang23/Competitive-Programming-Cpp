#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define mp make_pair
#define pb push_back
#define print(x) cout<<x<<endl
#define inf 1000000000000000LL

struct Node{
	llong sum;
	llong p, s, a;
	Node(){sum = -inf; p = -inf; s = -inf; a = -inf;}
	Node(llong sum_, llong p_, llong s_, llong a_){
		sum = sum_;
		p = p_;
		s = s_;
		a = a_;
	}
};
struct segtree{
	vector<Node> tree;
	llong n;
	llong pow_up(llong n){
		for(llong i=0;i<32;i++) if((1<<i)>=n) return 1<<i;
		return -1;
	}
	segtree(vector<llong>& arr, llong n_){
		n = pow_up(n_);
		tree = vector<Node>(n*2);
		for(llong i=0;i<n_;i++){
			tree[n+i].sum = arr[i];
			tree[n+i].p = arr[i];
			tree[n+i].s = arr[i];
			tree[n+i].a = arr[i];
		}
		build();
	}
	Node merge(Node l, Node r){
		Node m;
		m.sum = l.sum+r.sum;
		m.p = max(l.p, l.sum+r.p);
		m.s = max(r.s, r.sum+l.s);
		m.a = max({l.a,r.a,l.s + r.p});
		return m;
	}
	void pull_up(llong i){
		tree[i] = merge(tree[i*2], tree[i*2+1]);
	}
	void build(){
		for(llong i=n-1;i>=1;i--) pull_up(i);
	}
	llong query(llong l, llong r){
		Node ll, rr;
		for(l+=n, r+=n; l<=r; l/=2, r/=2){
			if(l&1) ll = merge(ll,tree[l++]);
			if(!(r&1)) rr = merge(tree[r--], rr);
			if(l == r) break;
		}
		Node mm = merge(ll,rr);
		return mm.a;
	}
};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong n; cin >> n;
	vector<llong> arr(n);
	for(llong i=0;i<n;i++) cin >> arr[i];
	segtree tr(arr, n);
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