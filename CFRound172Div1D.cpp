#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define mp make_pair
#define pb push_back
#define print(x) cout<<x<<endl
#define inf 1000000000000000LL

struct Node{
	llong sum;
	llong pmax, smax, amax;
	llong pmin, smin, amin;
	llong amaxl, amaxr, aminl, aminr;
	llong pmaxr, pminr, smaxl, sminl; 
	Node(int idx, llong val){
		sum=val;
		pmax=val; smax=val; amax=val;
		pmin=val; smin=val; amin=val;
		amaxl = amaxr = aminl = aminr = idx;
		pmaxr = pminr = smaxl = sminl = idx;
	}
	Node() : Node(-1,-inf) {}
	void flip(){
		sum = -sum;
		swap(pmax, pmin);
		pmax = -pmax;
		pmin = -pmin;
		swap(smax, smin);
		smax = -smax;
		smin = -smin;
		swap(amax, amin);
		amax = -amax;
		amin = -amin;
		swap(amaxl, aminl);
		swap(amaxr, aminr);
		swap(smaxl, sminl);
		swap(pmaxr, pminr);
	}
};
struct segtree{
	vector<Node> tree;
	vector<llong> mulp;
	llong n;
	llong pow_up(llong n){
		for(llong i=0;i<32;i++) if((1<<i)>=n) return 1<<i;
		return -1;
	}
	segtree(vector<llong>& arr, llong n_){
		n = pow_up(n_);
		tree = vector<Node>(n*2);
		mulp = vector<llong>(n*2,1);
		for(llong i=0;i<n_;i++){
			tree[n+i] = Node(i,arr[i]);
		}
		build();
	}
	Node merge(Node l, Node r){
		Node m;
		m.sum = l.sum+r.sum;

		if(l.pmax > l.sum + r.pmax){
			m.pmax = l.pmax;
			m.pmaxr = l.pmaxr;
		}else{
			m.pmax = l.sum + r.pmax;
			m.pmaxr = r.pmaxr;
		}

		if(r.smax > r.sum + l.smax){
			m.smax = r.smax;
			m.smaxl = r.smaxl;
		}else{
			m.smax = r.sum + l.smax;
			m.smaxl = l.smaxl;
		}

		m.amax = -inf;
		if(l.amax > m.amax){
			m.amax = l.amax;
			m.amaxl = l.amaxl;
			m.amaxr = l.amaxr;
		}
		if(r.amax > m.amax){
			m.amax = r.amax;
			m.amaxl = r.amaxl;
			m.amaxr = r.amaxr;
		}
		if(l.smax + r.pmax > m.amax){
			m.amax = l.smax + r.pmax;
			m.amaxl = l.smaxl;
			m.amaxr = r.pmaxr;
		}


		if(l.pmin < l.sum+r.pmin){
			m.pmin = l.pmin;
			m.pminr = l.pminr;
		}else{
			m.pmin = l.sum+r.pmin;
			m.pminr = r.pminr;
		}

		if(r.smin < r.sum+l.smin){
			m.smin = r.smin;
			m.sminl = r.sminl;
		}else{
			m.smin = r.sum+l.smin;
			m.sminl = l.sminl;
		}

		m.amin = inf;
		if(l.amin < m.amin){
			m.amin = l.amin;
			m.aminl = l.aminl;
			m.aminr = l.aminr;
		}
		if(r.amin < m.amin){
			m.amin = r.amin;
			m.aminl = r.aminl;
			m.aminr = r.aminr;
		}
		if(l.smin + r.pmin < m.amin){
			m.amin = l.smin + r.pmin;
			m.aminl = l.sminl;
			m.aminr = r.pminr;
		}
		return m;
	}
	void pull_up(llong i){
		tree[i] = merge(tree[i*2], tree[i*2+1]);
	}
	void push_down(llong i){
		if(i>=n || mulp[i]==1) return;
		tree[i*2].flip();
		tree[i*2+1].flip();
		mulp[i*2] *= mulp[i];
		mulp[i*2+1] *= mulp[i];
		mulp[i] = 1;
	}
	void build(){
		for(llong i=n-1;i>=1;i--) pull_up(i);
	}
	void update(int idx, int ts, int te, int vtx, llong val){
		push_down(idx);
		if(ts == vtx && te == vtx){
			tree[idx] = Node(vtx, val);
			return;
		}
		int tm = (ts+te)/2;
		if(vtx<=tm) update(idx*2,ts,tm,vtx,val);
		else update(idx*2+1,tm+1,te,vtx,val);
		pull_up(idx);
	}
	void update(int idx, llong val){update(1,0,n-1,idx,val);}
	void negate(int idx, int ts, int te, int ll, int rr){
		push_down(idx);
		if(ts == ll && te == rr){
			tree[idx].flip();
			mulp[idx] *= -1;
			return;
		}
		int tm = (ts+te)/2;
		if(ll<=tm) negate(idx*2,ts,tm,ll,min(rr,tm));
		if(rr>tm) negate(idx*2+1,tm+1,te,max(tm+1,ll),rr);
		pull_up(idx);
	}
	void negate(int ll, int rr){
		negate(1,0,n-1,ll,rr);
	}
	Node query(int idx, int ts, int te, int ll, int rr){
		if(ll>rr) return Node();
		push_down(idx);
		if(ts == ll && te == rr){
			return tree[idx];
		}
		int tm = (ts+te)/2;
		Node left,right;
		if(ll<=tm)
			left=query(idx*2,ts,tm,ll,min(rr,tm));
		if(rr>tm)
			right=query(idx*2+1,tm+1,te,max(tm+1,ll),rr);
		Node sum = merge(left, right);
		pull_up(idx);
		return sum;
	}
	Node query(llong l, llong r){
		return query(1, 0, n-1, l, r);
	}
};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong n; cin >> n;
	vector<llong> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];
	segtree tr(arr,n);
	int m; cin >> m;
	for(int i=0;i<m;i++){
		int type; cin >> type;
		if(type == 0){
			int idx, val; cin >> idx >> val; idx--;
			tr.update(idx, val);
		}else if(type == 1){
			int l, r, k; cin >> l >> r >> k; l--; r--;
			llong maxx = 0;
			llong sum = 0;
			stack<pair<int,int>> acts;
			for(int i=1;i<=k;i++){
				Node ret=tr.query(l,r);
				tr.negate(ret.amaxl, ret.amaxr);
				//deb(mp(ret.amaxl,ret.amaxr))
				sum += ret.amax;
				maxx = max(maxx, sum);
				acts.push(mp(ret.amaxl, ret.amaxr));
			}
			while(!acts.empty()){
				pair<int,int> act = acts.top();
				tr.negate(act.first, act.second);
				acts.pop();
			}
			print(maxx);
		}
	}
}





