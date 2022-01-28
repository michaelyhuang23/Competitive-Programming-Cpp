#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl

struct Node{
	llong sum;
	bool saturate;
	Node(){ sum=0; saturate=0; }
};

struct segtree{
	vector<Node> tree;
	vector<llong> rc;
	llong n;
	llong pow_up(llong num){
		for(llong i=0;i<32;i++) if((1<<i)>=num) return 1<<i;
		return -1;
	}
	segtree(llong n_, vector<llong>& arr){
		n = pow_up(n_);
		tree = vector<Node>(n*2);
		rc = vector<llong>(n*2,0);
		for(llong i=0;i<n_;i++){
			tree[i+n].sum = arr[i];
			if(tree[i+n].sum == 1) tree[i+n].saturate=true;
		}
		build();
	}
	Node merge(Node l, Node r){
		Node m;
		m.sum = l.sum + r.sum;
		m.saturate = l.saturate & r.saturate;
		return m;
	}
	void pull_up(llong i){
		tree[i] = merge(tree[i*2], tree[i*2+1]);
	}
	void build(){
		for(llong i=n-1;i>=1;i--) pull_up(i);
	}
	void root(llong idx, llong ts, llong te, llong l, llong r){
		if(l>r) return;
		if(ts == te) {
			tree[idx].sum = (llong)sqrt((long double)tree[idx].sum); // risky!!!
			if(tree[idx].sum == 1) tree[idx].saturate = 1;
			return;
		}
		if(ts == l && te == r){
			if(tree[idx].saturate) return;
		}
		llong tm = (ts+te)/2;
		if(l<=tm) root(idx*2, ts, tm, l, min(r,tm));
		if(r>tm) root(idx*2+1, tm+1, te, max(l, tm+1), r);
		pull_up(idx);
	}
	void root(llong l, llong r){
		root(1, 0, n-1, l, r);
	}
	Node query(llong idx, llong ts, llong te, llong ll, llong rr){
		if(ll>rr) return Node();
		if(ts == ll && te == rr) {
			return tree[idx];
		}
		llong tm = (ts+te)/2;
		Node left, right;
		if(ll<=tm) left=query(idx*2, ts, tm, ll, min(rr, tm));
		if(rr>tm) right=query(idx*2+1, tm+1, te, max(ll, tm+1), rr);
		Node sum = merge(left, right);
		return sum;
	}
	llong query(llong l, llong r){
		Node ret = query(1, 0, n-1, l, r);
		return ret.sum;
	}
}; 



llong N, M; 
void solve(llong t){
	vector<llong> arr(N);
	for(llong i=0;i<N;i++) cin >> arr[i];
	cin >> M;
	segtree tr(N, arr);
	cout<<t<<endl;
	for(llong i=0;i<M;i++){
		llong type; cin >> type;
		if(type==0){
			llong x, y; cin >> x >> y; x--; y--;
			if(x>y) swap(x,y);
			tr.root(x, y);
		}else{
			llong x, y; cin >> x >> y; x--; y--;
			if(x>y) swap(x,y);
			llong sum = tr.query(x, y);
			print(sum);
		}
	}
	cout<<endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	llong t = 0;
	while(cin >> N) solve(++t);
}




