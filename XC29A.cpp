#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update


#include<bits/stdc++.h>

using namespace std;
using namespace __gnu_pbds;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<'\n'
#define inf 1000000000

typedef long long llong;
typedef tree<pair<int,int>,null_type,less<pair<int,int>>,rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int cc = 0;
struct Node{
	ordered_set vals;
	Node(){}
	// void pull_up(Node& ll, Node& rr){
	// 	vals = ll.vals;
	// 	for(pair<int,int> item : rr.vals)
	// 		vals.insert(item);
	// }
	void update(int r){
		vals.insert(mp(r,cc++));
	}
	int query(int r){
		return vals.order_of_key(mp(r,inf));
	}
};

struct segtree{
	static llong pow_up(llong num){
		for(llong i=0;i<32;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<Node> tree;
	llong n;
	segtree(llong size){
		n = pow_up(size);
		tree = vector<Node>(n*2);
		//build();
	}
	// void build(){
	// 	for(llong i = n-1; i>=1; i--) tree[i].pull_up(tree[i<<1], tree[i<<1|1]);
	// }
	void update(llong idx, llong val){
		tree[n+idx].update(val);
		// change parent
		for(llong i = (n+idx)>>1; i >= 1; i>>=1) {
			tree[i].update(val);
			//tree[i].pull_up(tree[i<<1], tree[i<<1|1]);
		}
	}
	llong query(llong left, llong right){
		// both inclusive
		llong total = 0;
		int ll = left, rr = right;
		left+=n, right+=n;
		for(;left<=right;left>>=1,right>>=1){
			if(left&1) {
				total += tree[left++].query(rr);
			}
			if(!(right&1)){
				total += tree[right--].query(rr);
			} 
			if(left==right) break; 
		}
		//end condition is correct because only 1 of these 2 can be true then
		return total;
	}
};

void solve(){
	int n, q; cin >> n >> q;
	vector<int> lefts(n), rights(n);
	vector<tuple<int, bool, int>> ptrs;
	// k value, is it interval, id
	// this should ensure intervals are traversed first when we sort in decreasing order
	for(int i=0;i<n;i++){
		cin >> lefts[i]; cin >> rights[i];
		int k = rights[i] - lefts[i];
		ptrs.pb(mt(k, true, i));
	}

	vector<int> Ls(q), Rs(q), ans(q,-1);
	for(int i=0;i<q;i++){
		int L, R, K; cin >> L >> R >> K;
		Ls[i] = L;
		Rs[i] = R;
		ptrs.pb(mt(K, false, i));
	}

	sort(ptrs.rbegin(), ptrs.rend());

	segtree tracker(n+2);

	for(auto& ptr : ptrs){
		int k = get<0>(ptr);
		bool isint = get<1>(ptr);
		int id = get<2>(ptr);
		if(isint){
			tracker.update(lefts[id], rights[id]);
		}else{
			int L = Ls[id];
			int R = Rs[id];
			ans[id] = tracker.query(L, R); // range [L,R] <=R
		}
	}

	for(int i=0;i<q;i++) print(ans[i]);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
	//print(cc);
}