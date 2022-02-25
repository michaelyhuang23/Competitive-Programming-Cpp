#include<bits/stdc++.h>
using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000LL

struct Node{
	int val, ll, rr;
	int min0;
	int pd;
	Node(int val_, int idx) : val(val_), pd(0), ll(idx), rr(idx) {
		if(val_ == 0) min0 = idx;
	}
	Node() : val(inf), pd(0), ll(inf), rr(-inf), min0(inf) {}
	void pull_up(Node left, Node right){
		(*this) = merge(left, right);
	}
	static Node merge(Node left, Node right){
		Node ret; ret.ll = min(left.ll, right.ll); ret.rr = max(right.rr, left.rr);
		ret.val = min(left.val, right.val); // this is min so we know if interval contains 0
		ret.min0 = min(left.min0, right.min0);
		return ret;
	}
	void push_down(Node left, Node right){
		left.val += pd;
		right.val += pd;
		left.pd += pd;
		right.pd += pd;
		pd = 0;
	}
	void change(int val_){
		val += val_;
		pd += val_;
	}
	llong ans(){ return min0; }
};

struct SegTree
{
	static llong pow_up(int num){
		for(int i=0;i<65;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<Node> tree;
	int n;
	SegTree(vector<llong>& arr,int size){
		n = pow_up(size);
		tree = vector<Node>(n*2);
		for(int i=0;i<n;i++) {
			if(i<size)
				tree[n+i] = Node(arr[i],i);
			else 
				tree[n+i] = Node(-inf, i);
		}
		build();
	}
	inline void build(){
		for(int i = n-1; i>=1; i--) tree[i].pull_up(tree[i<<1], tree[i<<1|1]);
	}
	inline void update(int idx, int ts, int te, int left, int right, int val){
		if(left>right) return;
		if(ts == left && te == right){ tree[idx].change(val); return;}
		tree[idx].push_down(tree[idx<<1], tree[idx<<1|1]);
		int tm = (ts+te)>>1;
		if(left<=tm)
			update(idx<<1,ts,tm,left,min(right,tm),val);
		if(right>tm)
			update(idx<<1|1,tm+1,te,max(tm+1,left),right,val);
		tree[idx].pull_up(tree[idx<<1], tree[idx<<1|1]);
	}
	inline void update(int left, int right, int val){ update(1,0,n-1,left,right,val); }
	inline Node query(int idx){
		// both inclusive; ts, te indicate the coverage of this index
		if(idx>=n) return tree[idx];
		tree[idx].push_down(tree[idx<<1], tree[idx<<1|1]);
		Node total;
		if(tree[idx<<1].val == 0)
			total = Node::merge(total, query(idx<<1));
		if(tree[idx<<1|1].val == 0)
			total = Node::merge(total, query(idx<<1|1));
		return total;
	}
	inline llong query(int left, int right){ return query(1).ans(); }
};



void solve(){
	int N, K; cin >> N >> K;
	vector<int> arr(N);
	for(int i=0;i<N;i++) cin >> arr[i];


	// preprocessing


}