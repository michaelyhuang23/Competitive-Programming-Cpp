#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl


struct NodeP{
	llong val, l, r, pd;
	NodeP(){val = 0;l=inf;r=-inf;pd=0;}
	NodeP(llong val_,llong i){val = val_;l=i;r=i;}
	void update(llong val_){
		pd += val_;
		val += val_*(r-l+1);
	}
	NodeP updateC(llong val_){
		NodeP m = *this;
		m.pd += val_;
		m.val += val_*(r-l+1);
		return m;
	}
	NodeP merge(NodeP ll, NodeP rr){
		NodeP m;
		m.val = ll.val + rr.val;
		m.l = min(ll.l, rr.l);
		m.r = max(ll.r, rr.r);
		return m;
	}
	void push_down(NodeP& ll, NodeP& rr){
		ll.val += pd*(ll.r-ll.l+1);
		rr.val += pd*(rr.r-rr.l+1);
		ll.pd += pd;
		rr.pd += pd;
		pd = 0;
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
	segtree(llong n_, vector<llong>& arr){
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

int N,M;
vector<vector<int>> adj;
vector<int> weight;
vector<int> fa;
vector<int> troots;
segtree<NodeP> trs;
vector<vector<int>> bin;
vector<int> depth;

void dfs(int cur, int parent){
	fa[cur] = parent;
    int ans = trs.update(troots[parent], weight[cur], weight[cur], 1); 
	troots[cur] = ans;
	if(cur == parent) depth[cur] = 0;
	else depth[cur] = depth[parent]+1;
	for(int son : adj[cur]){
		if(son == parent) continue;
		dfs(son, cur);
	}
}

int get_lca(int a, int b){
    if(depth[b]<depth[a]){ swap(a,b); }
    int diff = depth[b] - depth[a];
    for(int i=0; i<20; i++) if((diff>>i) & 1) b = bin[i][b];
    // level to the same
    //assert(depth[b]==depth[a]);
    if(a==b) return a;
    for(int i=19; i>=0; i--) if(bin[i][b] !=  bin[i][a]) {
        a = bin[i][a];
        b = bin[i][b];
    }
    a = bin[0][a];
    b = bin[0][b];
    //assert(a==b);
    return a;
}

bool check(int a, int b, int lca, int mm, int k){
	int ta = trs.query(troots[a],0,mm);
	int tb = trs.query(troots[b],0,mm);
	int tlca = trs.query(troots[lca],0,mm);
	//deb(mt(ta,tb,tlca))
	int tt = ta + tb - tlca*2;
	if(weight[lca] <= mm) tt++;
	//deb(tt)
	return tt>=k;
}


void solve(){
	cin >> N >> M;
	weight = vector<int>(N);
	vector<int> ww(N);
	adj = vector<vector<int>>(N);
	troots = vector<int>(N,0);
	depth = vector<int>(N,0);
	for(int i=0;i<N;i++) cin >> weight[i];
	ww = weight;
    sort(ww.begin(), ww.end());
	ww.erase(unique(ww.begin(), ww.end()), ww.end());
	unordered_map<int,int> wi;
	for(int i=0;i<ww.size();i++) wi[ww[i]]=i;
	for(int i=0;i<N;i++) weight[i] = wi[weight[i]];
	for(int i=0;i<N-1;i++){
		int a, b; cin >> a >> b;
		a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	fa = vector<int>(N);
	for(int i=0;i<N;i++) fa[i]=i;
	vector<llong> ept(N,0);
	trs = segtree<NodeP>(N, ept);
	troots[0] = trs.root;

	dfs(0,0);

	// binary jumping
	bin = vector<vector<int>>(20, vector<int>(N));
	for(int i=0;i<N;i++) bin[0][i] = fa[i];
	for(int j=1;j<20;j++) for(int i=0;i<N;i++) bin[j][i] = bin[j-1][bin[j-1][i]];

	// query
	for(int i=0;i<M;i++){
		int a, b, k; cin >> a >> b >> k;
		a--; b--;
		int lca = get_lca(a,b);
		int ll = 0, rr = N, ans = 0;
		//deb(lca)
		//check(1,4,0,0,1);
		while(ll<=rr){
			int mm = (ll+rr)/2;
			if(check(a,b,lca,mm,k)) {ans = mm; rr = mm-1;}
			else ll = mm+1;
		}
		print(ww[ans]);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}

