#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 1000000007


struct segtree
{
	static int pow_up(int num){
		for(int i=0;i<65;i++) if(1<<i >= num) return 1<<i;
	}
	vector<map<int,int>> tree;
	vector<int> pd;
	vector<int> mul;
	int n;
	int v;
	segtree(int size){
		n = pow_up(size);
		v = 0;
		tree = vector<map<int,int>>(n*2,{{0,0}});
		pd = vector<int>(n*2,0);
		mul = vector<int>(n*2,1);
		build();
	}
	inline int op(int l, int r){ return l + r; }
	inline void build(){
		for(int i = n-1; i>=1; i--) tree[i][0] = op(tree[i<<1][0],tree[i<<1|1][0]);
	}
	inline void update(int idx, int ts, int te, int left, int right, int p, int c){
        //deb(mt(idx, ts, te)) deb(mt(left,right,val))
		if(left>right) return;
		if(ts == left && te == right){ tree[idx]+=c*(te-ts+1)+p*(te-ts)*(te-ts+1)/2; pd[idx]+=c; mul[idx]+=p; return;}
		push_down(idx, ts, te); //update to most current for backtrace reupdate
		int tm = (ts+te)>>1;
		if(left<=tm)
			update(idx<<1,ts,tm,left,min(right,tm),p,c);
		if(right>tm)
			update(idx<<1|1,tm+1,te,max(tm+1,left),right,p,c+(tm+1-ts)*p);
		tree[idx][v] = op(tree[idx<<1][v], tree[idx<<1|1][v]);
	}
	inline void update(int left, int right, int p, int c){ update(1,0,n-1,left,right,p,c); }
	inline void push_down(int idx, int ts, int te){
        //deb(mt(idx,ts,te))
		if(idx>=n || pd[idx]==0 && mul[idx]==1) return;
		int tm = (ts+te)>>1;
		tree[idx<<1] += mul[idx]*(tm-ts)*(tm-ts+1)/2;
		tree[idx<<1] += pd[idx]*(tm-ts+1);
		tree[idx<<1|1] += mul[idx]*(te-tm-1)*(te-tm)/2;
		tree[idx<<1|1] += pd[idx]*(te-tm);
		pd[idx<<1] += pd[idx];
		pd[idx<<1|1] += (tm+1-ts)*mul[idx];
		pd[idx<<1|1] += pd[idx];
		mul[idx<<1] += mul[idx];
		mul[idx<<1|1] += mul[idx]; 
		pd[idx] = 0;
		mul[idx] = 0;
	}
	inline int query(int idx, int ts, int te, int left, int right){
		// both inclusive; ts, te indicate the coverage of this index
		if(left>right) return 0;
		push_down(idx,ts,te);
		if(ts == left && te == right) return tree[idx];
		int tm = (ts+te)>>1;
		int sum = 0;
		if(left<=tm)
			sum=op(sum,query(idx<<1,ts,tm,left,min(right,tm)));
		if(right>tm)
			sum=op(sum,query(idx<<1|1,tm+1,te,max(tm+1,left),right));
		return sum;
	}
	inline int query(int left, int right){ return query(1,0,n-1,left,right); }
};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

}




















