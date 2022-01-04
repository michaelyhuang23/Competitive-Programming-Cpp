#include<iostream>
#include<assert.h>
#include<vector>
#include<tuple>
#include<unordered_map>
#include<set>

#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define MOD 998244353
#define pb push_back
#define mp make_pair
#define mt make_tuple

struct segtree
{
	static llong pow_up(int num){
		for(int i=0;i<65;i++) if(1<<i >= num) return 1<<i;
	}
	vector<llong> tree;
	vector<llong> pd;
	vector<llong> mul;
	int n;
	segtree(int size){
		n = pow_up(size);
		tree = vector<llong>(n*2, 0);
		pd = vector<llong>(n*2,0);
		mul = vector<llong>(n*2,1);
		build();
	}
	inline llong op(llong l, llong r){ return l + r; }
	inline void build(){
		for(int i = n-1; i>=1; i--) tree[i] = op(tree[i<<1],tree[i<<1|1]);
	}
	inline void update(int idx, int ts, int te, int left, int right, int val){
        //deb(mt(idx, ts, te)) deb(mt(left,right,val))
		if(left>right) return;
		if(ts == left && te == right){ tree[idx]+=val*(te-ts+1);/*only for sum*/ pd[idx]+=val; return;}
		push_down(idx, ts, te); //update to most current for backtrace reupdate
		int tm = (ts+te)>>1;
		if(left<=tm)
			update(idx<<1,ts,tm,left,min(right,tm),val);
		if(right>tm)
			update(idx<<1|1,tm+1,te,max(tm+1,left),right,val);
		tree[idx] = op(tree[idx<<1], tree[idx<<1|1]);
	}
	inline void update(int left, int right, int val){ update(1,0,n-1,left,right,val); }
	inline void multiply(int idx, int ts, int te, int left, int right, int val){
		if(left>right) return;
		if(ts == left && te == right){ tree[idx]*=val; mul[idx]*=val; pd[idx]*=val; return;}
		push_down(idx, ts, te); //update to most current for backtrace reupdate
		int tm = (ts+te)>>1;
		if(left<=tm)
			update(idx<<1,ts,tm,left,min(right,tm),val);
		if(right>tm)
			update(idx<<1|1,tm+1,te,max(tm+1,left),right,val);
		tree[idx] = op(tree[idx<<1], tree[idx<<1|1]);
	}
	inline void multiply(int left, int right, int val){ multiply(1,0,n-1,left,right,val); }
	inline void push_down(int idx, int ts, int te){
        //deb(mt(idx,ts,te))
		if(idx>=n || pd[idx]==0 && mul[idx]==1) return;
		int tm = (ts+te)>>1;
		tree[idx<<1] *= mul[idx];
		tree[idx<<1] += pd[idx]*(tm-ts+1);
		tree[idx<<1|1] *= mul[idx];
		tree[idx<<1|1] += pd[idx]*(te-tm);
		pd[idx<<1] *= mul[idx];
		pd[idx<<1] += pd[idx];
		pd[idx<<1|1] *= mul[idx];
		pd[idx<<1|1] += pd[idx];
		mul[idx<<1] *= mul[idx];
		mul[idx<<1|1] *= mul[idx]; 
		pd[idx] = 0;
		mul[idx] = 1;
	}
	inline llong query(int idx, int ts, int te, int left, int right){
		// both inclusive; ts, te indicate the coverage of this index
		if(left>right) return 0;
		push_down(idx,ts,te);
		if(ts == left && te == right) return tree[idx];
		int tm = (ts+te)>>1;
		llong sum = 0;
		if(left<=tm)
			sum=op(sum,query(idx<<1,ts,tm,left,min(right,tm)));
		if(right>tm)
			sum=op(sum,query(idx<<1|1,tm+1,te,max(tm+1,left),right));
		return sum;
	}
	inline llong query(int left, int right){ return query(1,0,n-1,left,right); }
};

int n;
vector<int> A;


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	A = vector<int>(n+1);
	for(int i=1;i<=n;i++) cin>>A[i];
	set<int> B(A.begin()+1, A.end());
	
	unordered_map<int,int> val2id;
	vector<int> id2val(B.size());
	int idc = 0;
	for(int elem : B){
		id2val[idc] = elem;
		val2id[elem] = idc++;
	}

	segtree dp(idc+1);
    deb("update") deb(mt(0,val2id[A[1]],1))
	dp.update(0,val2id[A[1]],1);

	// init condition here
	for(int i=2;i<=n;i++){
		llong sum = dp.query(0, idc);
		int id = val2id[A[i]];
		dp.multiply(id+1, idc, 0);
		dp.multiply(0, id, -1);
        deb("update") deb(mt(0,id,sum))
		dp.update(0, id, sum);
	}

	llong total = dp.query(0,idc);
	cout<<total<<endl;
}

/*

This doesn't work because discretization doesn't work and we don't have enough memory and sparse segtree doesn't work!



Consider the reverse, if we are given a list of adjacent elements that are linked (same value), how can we count that
It's easy to count. For each connected component, we are free to set a value that is <= its upper-bound. 

Now we want nothing to be linked, so we subtract all with one connection, add 2 connections, - 3 connections...

Can we use a dp to count how many single link?

dp[i][j] = on to the ith one, j links -- how many counts


Do we need to know how many links? or just the parity of counts
dp[i][0/1] = dp[j][0/1] + s(i,j) (use [i,j] as a connected component)

Notice that s(i,j) doesn't change alot, only when you encounter a smaller one
So we can keep an increasing ordered stack of minimums. 

For each range [i, j] we can keep its sum (it's unchanging). 
We can even compute the total sum and when we add a new one in, keep that total sum


*/



