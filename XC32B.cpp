
#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl


struct Line{
	llong k,b;
	Line() : k(0),b(0){}
	Line(llong k_, llong b_) : k(k_),b(b_) {}
	Line operator+(Line other){ return Line(k+other.k,b+other.b); }
	bool operator==(Line other){ return k==other.k && b==other.b; }
	Line mul(llong s){ return Line(k*s,b*s); }
	llong eval(llong x){return x*k+b;} // x intercept is the critical rotating point
};

struct NodeS{
	Line ln, pd;
	NodeS():ln(),pd(){}
	void update(Line& ln_, llong ts, llong te){
		ln = ln + ln_.mul(te-ts+1);
		pd = pd + ln_;
	}
	static NodeS merge(NodeS& ll, NodeS& rr){
		NodeS mm;
		mm.ln = ll.ln + rr.ln;
		return mm;
	}
	void pull_up(NodeS& ll, NodeS& rr){
		(*this)=merge(ll,rr);
	}
	void push_down(NodeS& ll, NodeS& rr, llong ts, llong te){
		if(pd==Line()) return;
		llong tm = (ts+te)/2;
		ll.update(pd,ts,tm);
		rr.update(pd,tm+1,te);
		pd = Line();
	}
	Line ans(){return ln;}
};

template<typename Node>
struct segtreeRecurse{
	static llong pow_up(llong num){
		for(llong i=0;i<65;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<Node> tree;
	llong n;
	segtreeRecurse(){}
	segtreeRecurse(llong size, vector<llong>& arr){
		n = pow_up(size);
		tree = vector<Node>(n*2);
		for(llong i=n;i<n+size;i++) tree[i].ln = Line(0,arr[i-n]);
		build();
	}
	void build(){
		for(llong i = n-1; i>=1; i--) tree[i].pull_up(tree[i<<1], tree[i<<1|1]);
	}
	void update(llong idx, llong ts, llong te, llong left, llong right, Line val){
		if(left>right) return;
		if(ts == left && te == right){ tree[idx].update(val,ts,te); return;}
		tree[idx].push_down(tree[idx<<1], tree[idx<<1|1], ts, te); //update to most current for backtrace reupdate
		llong tm = (ts+te)>>1;
		if(left<=tm) update(idx<<1,ts,tm,left,min(right,tm),val);
		if(right>tm) update(idx<<1|1,tm+1,te,max(tm+1,left),right,val);
		tree[idx].pull_up(tree[idx<<1], tree[idx<<1|1]);
	}
	void update(llong left, llong right, Line val){ update(1,0,n-1,left,right,val); }
	Node query(llong idx, llong ts, llong te, llong left, llong right){
		if(left>right) return Node();
		if(ts == left && te == right) return tree[idx];
		tree[idx].push_down(tree[idx<<1], tree[idx<<1|1], ts, te);
		llong tm = (ts+te)>>1;
		Node ll, rr;
		if(left<=tm)
			ll=query(idx<<1,ts,tm,left,min(right,tm));
		if(right>tm)
			rr=query(idx<<1|1,tm+1,te,max(tm+1,left),right);
		return Node::merge(ll,rr);
	}
	Line query(llong left, llong right){ return query(1,0,n-1,left,right).ans(); }
};


llong n,m;
vector<llong> arr,psum;
void solve(){
	cin >> n;
	arr = vector<llong>(n,0);
	for(llong i=0;i<n;i++) cin >> arr[i];
	psum = vector<llong>(n,0);
	psum[0] = arr[0];
	for(llong i=1;i<n;i++) psum[i] = psum[i-1]+arr[i];

	cin >> m;

	segtreeRecurse<NodeS> stree(n,arr);
	for(llong i=0;i<m;i++){
		llong type; cin >> type;
		if(type == 1){
			llong l,r,x; cin >> l >> r >> x; l--; r--;
			Line val(x,-i*x);
			stree.update(l,r,val);
		}else{
			llong l,r; cin >> l >> r; l--; r--;
			Line ret=stree.query(l,r);
			print(ret.eval(i));
		}
	}
}





















int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}