#include<iostream>
#include<vector>
#include<tuple>
#include<assert.h>
#include<algorithm>
#include<climits>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 4611686018427387904LL

struct segtree{
	//llong* tree;
	llong tree[262164];
	//vector<llong> tree;
	llong n;
	llong pow_up(llong num){
		for(llong i=0;i<32;i++) if((1<<i) >= num) return 1<<i;
		//assert(false);
	}
	segtree(llong n_){
		n = pow_up(n_);
		//tree = new llong[2*n];
		fill(tree, tree+2*n, inf);
		//tree = vector<llong>(n*2, inf);
		build();
	}
	llong op(llong l, llong r){ return min(l,r); }
	void pull_up(llong idx){
		tree[idx] = op(tree[idx*2], tree[idx*2+1]);
	}
	void build(){
		for(llong i=n-1;i>=1;i--) pull_up(i);
	}
	void update(llong idx, llong val){
		idx+=n;
		tree[idx] = val;
		for(idx/=2;idx>=1;idx/=2) pull_up(idx);
	}
	llong query(llong l, llong r){
		llong minn = inf;
		for(l+=n, r+=n; l<=r; l/=2, r/=2){
			if(l&1) minn = op(minn, tree[l++]);
			if(!(r&1)) minn = op(minn, tree[r--]);
			if(l==r) break;
		}
		return minn;
	}
};

int N, K;
vector<tuple<int,int,int>> adj[100005]; // left, right, cost

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> K;
	//adj = vector<vector<tuple<int,int,int>>>(N);
	for(int i=0;i<K;i++){
		int c, p, a, b;
		cin >> c >> p >> a >> b;
		a--; b--; c--;
		adj[c].pb(mt(a,b,p));
	}
	segtree ll(N+5), rr(N+5), dp(N+5);

	ll.update(0,0);
	rr.update(N-1,0);
	for(int t=0;t<10*N+5;t++){
		bool update = false;
		for(int i=0;i<N;i++){
			llong minl = inf;
			llong minr = inf;

			llong oldl = ll.query(i,i);
			llong oldr = rr.query(i,i);

			for(auto edge : adj[i]){
				int a = get<0>(edge);
				int b = get<1>(edge);
				int p = get<2>(edge);
				llong retl = ll.query(a,b);
				llong retr = rr.query(a,b);
				minr = min(minr, retr+p);
				minl = min(minl,retl+p);
			}
			if(minl < oldl){
				ll.update(i,minl);
				update=true;
			}
			if(minr < oldr){
				rr.update(i,minr);
				update=true;
			}
		}
		if(!update) break;
	}

	for(int i=0;i<N;i++) {
		llong lc = ll.query(i,i);
		llong rc = rr.query(i,i);
		if(lc <inf/2 && rc < inf/2) dp.update(i, lc+rc);
	}

	for(int t=0;t<10*N+5;t++){
		bool update = false;
		for(int i=0;i<N;i++){
			llong mindp = inf;
			llong olddp = dp.query(i,i);

			for(auto edge : adj[i]){
				int a = get<0>(edge);
				int b = get<1>(edge);
				int p = get<2>(edge);
				llong retl = ll.query(a,b);
				llong retr = rr.query(a,b);
				llong retdp = dp.query(a,b);
				mindp = min(mindp, retdp+p);
				if(retl<inf/2 && retr<inf/2)
					mindp = min(mindp, retl+retr+p);
			}
			if(mindp < olddp){
				dp.update(i,mindp);
				update=true;
			}
		}
		if(!update) break;
	}

	for(int i=0;i<N;i++){
		llong ret = dp.query(i,i);
		//assert(ret >= 0);
		if(ret>=inf/2)
			cout<<-1<<endl;
		else 
			cout<<ret<<endl;
	}
}






