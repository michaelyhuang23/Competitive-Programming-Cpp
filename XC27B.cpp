#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000

struct Node{
	int minn; // track min of this
	int maxx; // track max of this
	int pd;
	Node() : minn(inf), maxx(-inf), pd(0) {}
	Node(int val_) : minn(val_), maxx(val_), pd(0){}
	static Node merge(Node ll, Node rr){
		Node m;
		m.minn = min(ll.minn, rr.minn);
		m.maxx = max(ll.maxx, rr.maxx);
		return m;
	}
	void pull_up(Node& ll, Node& rr){
		(*this) = merge(ll, rr);
	}
	void update(int v){
		int c = min(v, 0-maxx); // clamping down
		maxx += c;
		minn += c;
		pd += c;
	}
	void push_down(Node& ll, Node& rr){
		ll.update(pd);
		rr.update(pd);
		pd = 0;
	}
	int ans(){
		return minn;
	}
};


struct segtree{
	int n;
	vector<Node> tree;
	int pow_up(int num){
		for(int i=0;i<32;i++) if((1<<i)>=num) return 1<<i;
		return -1;
	}

	segtree(int n_, vector<int>& arr){
		n = pow_up(n_);
		tree = vector<Node>(2*n);
		for(int i=0;i<n_;i++){ // be mindful of overflow
			tree[i+n].val = arr[i] + tree[i+n-1].val;
		}
		for(int i=n_;i<n;i++)
			tree[i+n].val = tree[i+n-1].val;
		build();
	}

	void build(){
		for(int i=n-1;i>=1;i--) tree[i].pull_up(tree[i*2], tree[i*2+1]);
	}

	void update(int idx, int ts, int te, int ll, int rr, int val){
		if(ll>rr) return;
		if(ts == ll && te == rr){
			tree[idx].update(val);
			return;
		}
		tree[idx].push_down(tree[idx*2], tree[idx*2+1]);

		int tm = (ts+te)/2;

		if(ll<=tm)
			update(idx*2, ts, tm, ll, min(rr,tm), val);
		if(rr>tm)
			update(idx*2+1, tm+1, te, max(ll,tm+1), rr, val);
		tree[idx].pull_up(tree[idx*2], tree[idx*2+1]);
	}

	void update(int ll, int rr, int val) { update(1,0,n-1,ll,rr,val); }

	Node query(int idx, int ts, int te, int ll, int rr){
		if(ll>rr) return Node();
		if(ts == ll && te == rr) return tree[idx];
		tree[idx].push_down(tree[idx*2], tree[idx*2+1]);
		int tm = (ts+te)/2;
		Node L, R;
		if(ll<=tm)
			L = query(idx*2, ts, tm, ll, min(rr, tm));
		if(rr>tm)
			R = query(idx*2+1, tm+1, te, max(ll,tm+1), rr);
		tree[idx].pull_up(tree[idx*2], tree[idx*2+1]);
		return Node::merge(L, R);
	}

	int query(int ll, int rr){  return query(1,0,n-1,ll,rr).ans(); }
};


void solve(){
	int n, q; cin >> n >> q;
	vector<int> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];

	segtree tracker(n, arr);
	for(int i=0;i<q;i++){
		int T; cin >> T;
		if(T == 1){
			int l, r, x; cin >> l >> r >> x; l--; r--;
			// use Lamb Respite in [l,r]
			// start with health x

		}else{
			int id, x; cin >> id >> x; id--;
			// change id to x
			int cur = tracker.query(id, id);
			int diff = x-id;
			tracker.update(id,n-1,diff);
		}
	}
}





int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}














