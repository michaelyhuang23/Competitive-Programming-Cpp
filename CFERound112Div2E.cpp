#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int  ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

struct SegTree{
	iint* tree;
	iint* lazy;
	iint n;
	iint pow_up(iint num){
		For(i,65) if(1<<i >= num) return 1<<i;
		return -1;
	}
	SegTree(iint* arr, iint n_){
		n = pow_up(n_);
		tree = new iint[2*n];
		lazy = new iint[2*n];
		fill(lazy,lazy+n,0);
		copy(arr, arr+n_, tree+n);
		fill(tree+n+n_,tree+2*n,inf);
		build();
	}
	inline void build(){
		for(iint i=n-1;i>=1;i--) pull_up(i);
	}
	inline void pull_up(iint vtx){
		tree[vtx] = min(tree[vtx<<1],tree[vtx<<1|1]);
	}
	inline void push_down(iint vtx){
		if(vtx>=n) return;
		tree[vtx<<1] += lazy[vtx];
		tree[vtx<<1|1] += lazy[vtx];
		lazy[vtx<<1] += lazy[vtx];
		lazy[vtx<<1|1] += lazy[vtx];
		lazy[vtx] = 0;
	}
	inline void update(iint vtx, iint le, iint re, iint l, iint r, iint val){
		if(l==le && r==re){
			tree[vtx]+=val; //update lazy as well!
			lazy[vtx]+=val;
			return;
		}
		//cout<<vtx<<" "<<le<<" "<<re<<" "<<l<<" "<<r<<endl;
		push_down(vtx);
		iint mide = (le+re)>>1;
		if(l<=mide)
			update(vtx<<1,le,mide,l,min(r,mide),val);
		if(r>mide)
			update(vtx<<1|1,mide+1,re,max(mide+1,l),r,val);
		pull_up(vtx);
	}
	inline void update(iint l, iint r, iint v){
		update(1,0,n-1,l,r,v);
	}
	inline iint query(iint vtx, iint le, iint re, iint l, iint r){
		if(l==le && r==re) return tree[vtx];
		push_down(vtx);
		iint mide = (le+re)>>1;
		iint mini = inf;
		if(l<=mide)
			mini=min(mini,query(vtx<<1,le,mide,l,min(r,mide)));
		if(r>mide)
			mini=min(mini,query(vtx<<1|1,mide+1,re,max(mide+1,l),r));
		return mini;
	}
	inline iint query(iint l, iint r){
		return query(1,0,n-1,l,r);
	}
	~SegTree(){
		delete[] tree; delete[] lazy;
	}
};

iint n,m;
tuple<iint,iint,iint>* segs;
iint find(){
	iint rp = 0, lp = 0;
	iint* empty = new iint[m]; fill(empty,empty+m,0);
	SegTree tr(empty,m);
	tr.update(get<1>(segs[0]),get<2>(segs[0]),1);
	iint mindiff = inf;
	while(rp<n){
		if(tr.query(0,m-1)>0){
			//cout<<rp<<" "<<lp<<endl;
			mindiff = min(mindiff,get<0>(segs[rp])-get<0>(segs[lp]));
			tr.update(get<1>(segs[lp]),get<2>(segs[lp]),-1);
			lp++;
			continue;
		}
		if(rp==n-1) break;
		rp++;
		tr.update(get<1>(segs[rp]),get<2>(segs[rp]),1);
	}
	//exit(0);
	return mindiff;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    m--;
    //cout<<"hello"<<endl;
    segs = new tuple<iint,iint,iint>[n];
    For(i,n){
    	iint l,r,v;
    	cin >> l >> r >> v;
    	segs[i] = make_tuple(v,l-1,r-2);
    }
    //cout<<"hello2"<<endl;
    sort(segs,segs+n);
    // iint lb = 0, rb = 1000001, ans = -1;
    //cout<<"hello3"<<endl;
    // while(lb<=rb){
    // 	iint mid = (lb+rb)>>1;
    // 	if(check(mid)){ ans=mid;rb = mid-1;}
    // 	else lb = mid+1;
    // 	//cout<<mid<<endl;
    // }
    //check(2);
    cout<<find()<<endl;
}

/*
Given n segments; find the min cost set of segments
that covers [1,m]. Mincost = min diff in segment's value

if seg i < seg j; then we still have to retain i

DP attempt:
sort segs by left prt: backtrack prev selected segment --> n^2
X

a graph of segs connectivity: not djikstra
X

in the process of construction: if bounds are established, segs that don't 
touch bounds can be ranked by range.

traverse the possible min diff values: as we increase the tolerable diff
we connect more segments by UFDS, until [1,m] are connected. 
X: we are talking about global max and global min

binary search min possible diff: use sliding window/two pointer on arr 
sorted by values. For connectivity check: segment tree: query if range 
is all > 0;
O(20*3*10^5*20)

*/







