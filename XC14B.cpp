// #pragma GCC optimize("O3")
// #pragma GCC target("avx2") 
// #include "debughelp.hpp"
#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define inf 20000000000000000LL
#define pb push_back
#define mp make_pair
#define mt make_tuple



struct NodeP{
	llong maxx, minn, maxp, minp;
	llong pd;
	NodeP():pd(0),maxx(-inf),minn(inf),maxp(-1),minp(-1){}
	NodeP(llong loc):pd(0),maxx(0),minn(0),maxp(loc),minp(loc){}
	void update(llong val){
		maxx+=val;
		minn+=val;
		pd+=val;
	}
	static NodeP merge(NodeP& ll, NodeP& rr){
		NodeP mm;
		if(ll.maxx>rr.maxx) {
			mm.maxx=ll.maxx;
			mm.maxp=ll.maxp;
		}else{
			mm.maxx=rr.maxx;
			mm.maxp=rr.maxp;
		}

		if(ll.minn<rr.minn){
			mm.minn=ll.minn;
			mm.minp=ll.minp;
		}else{
			mm.minn=rr.minn;
			mm.minp=rr.minp;
		}

		return mm;
	}
	void pull_up(NodeP& ll, NodeP& rr){
		(*this) = merge(ll,rr);
	}
	void push_down(NodeP& ll, NodeP& rr){
		ll.update(pd);
		rr.update(pd);
		pd = 0;
	}
};


struct BIT{
	vector<llong> bits; // index start from 1
	llong n;
	BIT(llong n_){
		n = n_+2;
		bits = vector<llong>(n,0);
	}
	llong lowbit(llong n){ return n&(-n); }
	void update(llong idx, llong val){
		idx+=2; // for safety
		for(llong i=idx; i<n; i+=lowbit(i)) bits[i]+=val;
	}
	llong get_sum(llong idx){
		idx+=2; // for safety
		llong sum = 0;
		for(llong i=idx; i>0; i-=lowbit(i)) sum += bits[i];
		return sum;
	}
};


template<typename Node>
struct segtreeRecurse{
	static llong pow_up(llong num){
		for(llong i=0;i<31;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<Node> tree;
	llong n;
	segtreeRecurse(){}
	segtreeRecurse(llong size, bool init){
		n = pow_up(size);
		tree = vector<Node>(n*2);
		for(llong i=n;i<n+size;i++) tree[i] = Node(i-n);
		build();
	}
	void build(){
		for(llong i = n-1; i>=1; i--) tree[i].pull_up(tree[i<<1], tree[i<<1|1]);
	}
	void update(llong idx, llong ts, llong te, llong left, llong right, llong val){
		// if(left>right) return;
		if(ts == left && te == right){ tree[idx].update(val); return;}
		tree[idx].push_down(tree[idx<<1], tree[idx<<1|1]); //update to most current for backtrace reupdate
		llong tm = (ts+te)>>1;
		if(left<=tm) update(idx<<1,ts,tm,left,min(right,tm),val);
		if(right>tm) update(idx<<1|1,tm+1,te,max(tm+1,left),right,val);
		tree[idx].pull_up(tree[idx<<1], tree[idx<<1|1]);
	}
	void update(llong left, llong right, llong val){ update(1,0,n-1,left,right,val); }
	Node query(llong idx, llong ts, llong te, llong left, llong right){
		// if(left>right) return Node();
		if(ts == left && te == right) return tree[idx];
		tree[idx].push_down(tree[idx<<1], tree[idx<<1|1]);
		llong tm = (ts+te)>>1;
		Node ll, rr;
		if(left<=tm)
		    ll=query(idx<<1,ts,tm,left,min(right,tm));
		if(right>tm)
		    rr=query(idx<<1|1,tm+1,te,max(tm+1,left),right);
		return Node::merge(ll,rr);
	}
	Node query(llong left, llong right){ return query(1,0,n-1,left,right); }
	int findlast(int idx, int ts, int te, int thres, Node rn){
		// deb(mt(idx,ts,te))
		// deb(mt(rn.minn,rn.maxx,rn.minp,rn.maxp))
		if(idx>=n){
			Node rnn = Node::merge(tree[idx],rn);
			if(rnn.maxx-rnn.minn>=thres) return idx-n;
			else return -1;
		}
		tree[idx].push_down(tree[idx<<1],tree[idx<<1|1]);
		int tm = (ts+te)>>1; // checker loc is tm+1
		// deb(mt(tree[idx<<1|1].maxx, tree[idx<<1|1].minn, tree[idx<<1|1].maxp))
		Node rnn = Node::merge(tree[idx<<1|1], rn);
		if(rnn.maxx-rnn.minn>=thres) return findlast(idx<<1|1,tm+1,te,thres,rn);
		else return findlast(idx<<1,ts,tm,thres,rnn);
	}
	int findlast(int thres){ return findlast(1,0,n-1,thres,Node()); }
};


llong n;
vector<llong> C;


vector<pair<llong,llong>> upds;
vector<vector<llong>> updx;

void solve(){
	cin >> n;
	C = vector<llong>(n);
	for(llong i=0;i<n;i++) cin >> C[i];

	llong m; cin >> m;
	updx = vector<vector<llong>>(n+1);
	upds = vector<pair<llong,llong>>(2*m);
	for(llong i=0;i<m;i++){
		llong l, r, v; cin >> l >> r >> v;
		upds[i*2] = mp(i+1,v);
		upds[i*2+1] = mp(i+1,-v);
		updx[l].pb(i*2);
		updx[r+1].pb(i*2+1);
	}

	segtreeRecurse<NodeP> tracker(m+1, true);
	BIT vals(m+1);
	for(llong x=0;x<n;x++){
		for(llong i : updx[x]){
			auto upd = upds[i];
			llong t = upd.first;
			llong v = upd.second;
			// deb(upd)
			tracker.update(t, m, v);
			vals.update(t,v);
		}
		llong ans=tracker.findlast(C[x]);
		// deb(ans)
		llong finalVal = -1;
		if(ans == -1){
			NodeP ret = tracker.query(0,m);
			llong lastt = ret.minp;
			// assert(ret.minn<=0);
			finalVal = vals.get_sum(m)-vals.get_sum(lastt);
			// assert(finalVal>=0 && finalVal<=C[x]);
			if(x==n-1)
				cout<<finalVal<<endl;
			else
				cout<<finalVal<<" ";
			continue;
		}
		// deb(ans)
		NodeP ret = tracker.query(ans,m);
		// deb(mt(ret.minn,ret.maxx,ret.minp,ret.maxp))
		llong lastt = max(ret.minp, ret.maxp);
		if(lastt==ret.minp){
			finalVal = vals.get_sum(m)-vals.get_sum(lastt);
		}else{
			finalVal = C[x] + vals.get_sum(m)-vals.get_sum(lastt);
		}
		// assert(finalVal>=0 && finalVal<=C[x]);
		if(x==n-1)
			cout<<finalVal<<endl;
		else
			cout<<finalVal<<" ";
	}
}






int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	// fread(Buf,1,BUFSIZE,stdin); 
	solve();
}