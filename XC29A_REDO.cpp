#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2") 

#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define print(x) cout<<x<<'\n'

// struct NodeS{
// 	int val;
// 	NodeS() : val(0) {}
// 	void update(int val_){
// 		val += val_;
// 	}
// 	static NodeS merge(NodeS& ll, NodeS& rr){
// 		NodeS mm;
// 		mm.val = ll.val + rr.val;
// 		return mm;
// 	}
// 	void pull_up(NodeS& ll, NodeS& rr){
// 		(*this) = merge(ll, rr);
// 	}
// 	int ans(){ return val; }
// };

// template<typename Node>
struct segtree{
	static int pow_up(int num){
		for(int i=0;i<32;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<int> tree;
	int n;
	segtree(int size){
		n = pow_up(size);
		tree = vector<int>(n*2,0);
		// build();
	}
	void build(){
		for(int i = n-1; i>=1; i--) tree[i] = (tree[i<<1]+tree[i<<1|1]);
	}
	void rebuild(){
		fill(tree.begin(), tree.end(), 0);
	}
	void update(int idx, int val){
		tree[n+idx] += val;
		for(int i = (n+idx)>>1; i >= 1; i>>=1) tree[i] = (tree[i<<1] + tree[i<<1|1]);
	}
	int query(int left, int right){
		// both inclusive
		int sum = 0;
		left+=n, right+=n;
		for(;left<=right;left>>=1,right>>=1){
			if(left&1) sum += tree[left++];
			if(!(right&1)) sum += tree[right--];
			if(left==right) break; 
		}
		return sum;
	}
};


struct Point{
	int l, r, k;
	bool query;
	int c1, c2, c3, c4;
	int i;
	Point(int l_, int r_) : l(l_), r(r_), k(r_-l_), query(false), c1(0), c2(0), c3(0), c4(0) {}
	Point(int l_, int r_, int k_, int i_) : l(l_), r(r_), k(k_), query(true), c1(0), c2(0), c3(0), c4(0), i(i_) {}
	Point(){}
};


int n, q; 
int RANGE;
vector<Point> ptrs;

void solve(){
	scanf("%d%d", &n, &q);
	// cin >> n >> q;
	RANGE = segtree::pow_up(n+5);
	ptrs = vector<Point>(n+q); 
	for(int i=0;i<n;i++){
		int l, r; 
		scanf("%d%d", &l, &r);
		ptrs[i] = Point(l,r);
	}

	for(int i=0;i<q;i++){
		int l,r,k; 
		scanf("%d%d%d", &l, &r, &k);
		ptrs[n+i] = Point(l,r,k,i);
	}


	auto comp1 = [&](Point& p1, Point& p2){
		if(p1.r == p2.r){
			return p1.query < p2.query;
		}
		return p1.r < p2.r;
	};

	sort(ptrs.begin(), ptrs.end(), comp1);

	segtree tracker(RANGE);
	for(Point& ptr : ptrs){
		if(ptr.query){
			ptr.c1 += tracker.query(ptr.l, RANGE-1);
		}else{
			tracker.update(ptr.l, 1);
		}
	}



	auto comp2 = [&](Point& p1, Point& p2){
		if(p1.k == p2.k){
			return p1.query > p2.query;
		}
		return p1.k < p2.k;
	};

	sort(ptrs.begin(), ptrs.end(), comp2);

	tracker.rebuild();
	for(Point& ptr : ptrs){
		if(ptr.query){
			ptr.c2 += tracker.query(ptr.l, RANGE-1);
		}else{
			tracker.update(ptr.l, 1);
		}
	}


	tracker.rebuild();
	for(Point& ptr : ptrs){
		if(ptr.query){
			ptr.c3 += tracker.query(0, ptr.r);
		}else{
			tracker.update(ptr.r, 1);
		}
	}


	int counter = 0;
	for(Point& ptr : ptrs){
		if(ptr.query){
			ptr.c4 += counter;
		}else{
			counter++;			
		}
	}


	vector<int> ans(q,-1);

	for(Point& ptr : ptrs){
		if(ptr.query){
			if(ptr.k > ptr.r - ptr.l) ans[ptr.i] = 0;
			else ans[ptr.i] = ptr.c1 - ptr.c2 - ptr.c3 + ptr.c4;
		}
	}

	for(int i=0;i<q;i++) {
		// assert(ans[i]>-1);
		printf("%d\n",ans[i]);
	}
}















int main(){
	// ios_base::sync_with_stdio(0);
	// cin.tie(0);
	solve();
}