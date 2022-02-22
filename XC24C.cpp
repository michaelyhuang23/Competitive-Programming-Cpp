#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl


struct NodeP{
	llong val;
	NodeP(){val = 0;}
	NodeP(llong val_){val = val_;}
	void update(llong val_){
		val = val_;
	}
	NodeP updateC(llong val_){
		return NodeP(val_);
	}
	static NodeP merge(NodeP ll, NodeP rr){
		NodeP m(ll.val + rr.val);
		return m;
	}
	void push_down(NodeP& ll, NodeP& rr){
		;
	} 
	void pull_up(NodeP ll, NodeP rr){
		(*this) = merge(ll,rr);
	}
	llong ans(){ return val; }
};

template<class Node>
struct segtree{
	llong n;
	vector<Node> base;
	vector<Node> tree;
	llong root;
	vector<llong> lc, rc;
	llong cc;
	static llong pow_up(llong num){
		for(llong i=0;i<32;i++) if((1<<i) >= num) return 1<<i;
		return -1;
	}
	segtree(){}
	segtree(llong n_, vector<llong> arr){
		n = pow_up(n_);
		cc = 0;
		base = vector<Node>(n);
		tree = vector<Node>(2*n+6400000);
		lc = vector<llong>(2*n+6400000,-1);
		rc = vector<llong>(2*n+6400000,-1);
		for(llong i=0;i<n_;i++) base[i] = Node(arr[i],i);
		root = build(0, n-1);
	}
	llong build(llong ts, llong te){
		llong cur = cc++;
		if(ts==te) {tree[cur] = base[ts]; return cur;}
		llong tm = (ts+te)/2;
		lc[cur] = build(ts, tm);
		rc[cur] = build(tm+1, te);
		tree[cur].pull_up(tree[lc[cur]], tree[rc[cur]]); 
		return cur;
	}
	llong update(llong idx, llong ts, llong te, llong ll, llong rr, llong val){
        //deb(mt(idx, ts, te))
		if(ll>rr) return idx;
        if(lc[idx]>-1 && rc[idx]>-1) tree[idx].push_down(tree[lc[idx]], tree[rc[idx]]);
		if(ts == ll && te == rr){
			tree[cc] = tree[idx].updateC(val);
			return cc++;
		}
		llong tm = (ts+te)/2;
		int nidx = cc++;
		if(ll<=tm) lc[nidx] = update(lc[idx], ts, tm, ll, min(rr, tm), val); else lc[nidx] = lc[idx];
		if(rr>tm) rc[nidx] = update(rc[idx], tm+1, te, max(tm+1, ll), rr, val); else rc[nidx] = rc[idx];
		tree[nidx].pull_up(tree[lc[nidx]], tree[rc[nidx]]);
		return nidx;
	}
	llong update(llong rt, llong ll, llong rr, llong val){
		return update(rt, 0, n-1, ll, rr, val);
	}
	Node query(llong idx, llong ts, llong te, llong ll, llong rr){
		if(ll>rr) return Node();
        if(lc[idx]>-1 && rc[idx]>-1) tree[idx].push_down(tree[lc[idx]], tree[rc[idx]]);
		if(ts == ll && te == rr){return tree[idx];}
		llong tm = (ts+te)/2;
		Node left, right;
		if(ll<=tm) left = query(lc[idx], ts, tm, ll, min(rr, tm));
		if(rr>tm) right = query(rc[idx], tm+1, te, max(tm+1, ll), rr);
		tree[idx].pull_up(tree[lc[idx]], tree[rc[idx]]);
		return left.merge(left, right);
	}
	llong query(llong rt, llong ll, llong rr){
		Node ret = query(rt, 0, n-1, ll, rr);
		return ret.ans();
	}
};


void solve(){
	int n, m; cin >> n >> m;
	vector<llong> heights(n);
	for(int i=0;i<n;i++) cin >> heights[i];

	unordered_set<llong> distinctHeights(heights.begin(), heights.end());

	unordered_map<llong,int> val2id;
	int c = 0;
	for(llong h : distinctHeights) val2id[h] = c++;
	vector<int> newH(n);
	for(int i=0;i<n;i++){
		newH[i] = val2id[heights[i]]*2;
	}

	int H = distinctHeights.size()*2;

	segtree<NodeN> front(H, vector<llong>(H,0));
	vector<int> froots; froots.pb(front.root);
	for(int i=0;i<n;i++){
		int maxLen = front.query(froots.back(), 0, newH[i]-1);
		int nroot = front.update(froots.back(), newH[i], newH[i], maxLen);
		froots.pb(nroot);
	}

	segtree<NodeN> back(H, vector<llong>(H,0));
	vector<int> broots; broots.pb(back.root);
	for(int i=n-1;i>=0;i--){
		int maxLen = back.query(broots.back(), newH[i]+1, H);
		int nroot = back.update(broots.back(), newH[i], newH[i], maxLen);
		broots.pb(nroot);
	}

	for(int i=0;i<m;i++){
		int id, val; cin >> id >> val;
		id--;
		int h = 0;
		auto ret = distinctHeights.lower_bound(val);
		if(ret == distinctHeights.end()) h = H-1;
		else if(distinctHeights.find(*ret) != distinctHeights.end()){
			h = distance(distinctHeights.begin(), ret)*2;
		}else{
			h = distance(distinctHeights.begin(), ret)*2-1;
		}
		
	}





	

}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}