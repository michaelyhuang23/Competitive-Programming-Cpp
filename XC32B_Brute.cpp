
#include<bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl

struct NodeS{
	int val,pd;
	NodeS():val(0),pd(0){}
	NodeS(int val_):val(val_),pd(0){}
	void update(int val_, int ts, int te){
		val += val_*(te-ts+1);
		pd += val_;
	}
	static NodeS merge(NodeS& ll, NodeS& rr){
		return NodeS(ll.val+rr.val);
	}
	void pull_up(NodeS& ll, NodeS& rr){
		(*this)=merge(ll,rr);
	}
	void push_down(NodeS& ll, NodeS& rr, int ts, int te){
		if(pd==0) return;
		int tm = (ts+te)/2;
		ll.update(pd,ts,tm);
		rr.update(pd,tm+1,te);
		pd = 0;
	}
	int ans(){return val;}
};

template<typename Node>
struct segtreeRecurse{
	static int pow_up(int num){
		for(int i=0;i<65;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<Node> tree;
	int n;
	segtreeRecurse(){}
	segtreeRecurse(int size, vector<int>& arr){
		n = pow_up(size);
		tree = vector<Node>(n*2);
		for(int i=n;i<n+size;i++) tree[i]=Node(arr[i-n]);
		build();
	}
	void build(){
		for(int i = n-1; i>=1; i--) tree[i].pull_up(tree[i<<1], tree[i<<1|1]);
	}
	void update(int idx, int ts, int te, int left, int right, int val){
		if(left>right) return;
		if(ts == left && te == right){ tree[idx].update(val,ts,te); return;}
		tree[idx].push_down(tree[idx<<1], tree[idx<<1|1], ts, te); //update to most current for backtrace reupdate
		int tm = (ts+te)>>1;
		if(left<=tm) update(idx<<1,ts,tm,left,min(right,tm),val);
		if(right>tm) update(idx<<1|1,tm+1,te,max(tm+1,left),right,val);
		tree[idx].pull_up(tree[idx<<1], tree[idx<<1|1]);
	}
	void update(int left, int right, int val){ update(1,0,n-1,left,right,val); }
	Node query(int idx, int ts, int te, int left, int right){
		if(left>right) return Node();
		if(ts == left && te == right) return tree[idx];
		tree[idx].push_down(tree[idx<<1], tree[idx<<1|1], ts, te);
		int tm = (ts+te)>>1;
		Node ll, rr;
		if(left<=tm)
			ll=query(idx<<1,ts,tm,left,min(right,tm));
		if(right>tm)
			rr=query(idx<<1|1,tm+1,te,max(tm+1,left),right);
		return Node::merge(ll,rr);
	}
	int query(int left, int right){ return query(1,0,n-1,left,right).ans(); }
};




int n,m;
vector<int> arr;
vector<tuple<int,int,int>> ops;
void solve(){
	cin >> n;
	arr = vector<int>(n);
	for(int i=0;i<n;i++) cin >> arr[i];
	cin >> m;
	segtreeRecurse<NodeS> stree(n, arr);
	for(int i=0;i<m;i++){
		int type; cin >> type;
		if(type == 1){
			int l,r,x; cin >> l >> r >> x; l--; r--;
			ops.pb(mt(l,r,x));
		}else{
			int l,r; cin >> l >> r; l--; r--;
			print(stree.query(l,r));
		}
		for(auto& op : ops){
			int l = get<0>(op);
			int r = get<1>(op);
			int x = get<2>(op);
			stree.update(l,r,x);
		}
	}
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}