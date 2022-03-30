#include<bits/stdc++.h>

using namespace std;
#define print(x) cout<<x<<endl
#define pb push_back
#define mp make_pair
#define mt make_tuple

static int pow_up(int num){
	for(int i=0;i<32;i++) if(1<<i >= num) return 1<<i;
	return -1;
}


struct NodeM{
	int maxx;
	NodeM():maxx(0){}
	NodeM(int val):maxx(val){}
	static NodeM merge(NodeM& ll, NodeM& rr){
		return NodeM(max(ll.maxx, rr.maxx));
	}
	void update(int val){
		maxx += val;
	}
	void pull_up(NodeM& ll, NodeM& rr){
		(*this) = merge(ll,rr);
	}
	int ans(){return maxx;}
};

struct segtree{
	vector<NodeM> tree;
	int n;
	segtree(int size){
		n = pow_up(size);
		tree = vector<NodeM>(n*2);
		build();
	}
	void build(){
		for(int i=n-1;i>=1;i--) tree[i].pull_up(tree[i<<1],tree[i<<1|1]);
	}
	int query(int left, int right){
		NodeM ll, rr;
		left+=n, right+=n;
		for(;left<=right;left>>=1,right>>=1){
			if(left&1) ll=NodeM::merge(ll,tree[left++]);
			if(!(right&1)) rr=NodeM::merge(tree[right--],rr);
			if(left==right) break; 
		}
		return NodeM::merge(ll,rr).ans();
	}
	void update(int idx, int val){
		tree[n+idx].update(val);
		for(int i=(n+idx)>>1;i>=1;i>>=1) tree[i].pull_up(tree[i<<1],tree[i<<1|1]);
	}
};






void solve(){
	int n; cin >> n;
	vector<int> A(n+1);
	for(int i=1;i<=n;i++) cin >> A[i];
	string Ks; cin >> Ks;
	vector<int> K(Ks.size()+2,2);

	for(int i=0;i<Ks.size();i++)
		K[i+1] = (Ks[i]=='U') ? 1 : 0;

	vector<int> dp(n+1,0);

	segtree dpU(n+2), dpD(n+2);

	int maxKK = 0;

	for(int i=2;i<=n;i++){
		// update for U
		int maxku = dpU.query(0, A[i]-1)+1;
		// update for D
		int maxkd = dpD.query(A[i]+1, n+1)+1;

		int maxk = max(maxku, maxkd);
		// update segtree
		if(K[maxk+1] == 1){
			dpU.update(A[i], maxk);
		}
		if(K[maxk+1] == 0){
			dpD.update(A[i], maxk);
		}
		maxKK = max(maxKK, maxk);
	}

	print(maxKK);
}









int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}