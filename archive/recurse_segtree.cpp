//#pragma once
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
#define For(i, j) for (int i = 0 ; i < j ; i ++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

struct SegTree
{
	static llong pow_up(int num){
		for(int i=0;i<65;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<llong> tree;
	vector<llong> pd;
	int n;
	SegTree(vector<llong>& arr,int size){
		n = pow_up(size);
		tree = vector<llong>(n*2);
		pd = vector<llong>(n*2);
		fill(pd.begin(),pd.end(),0);
		copy(arr.begin(), arr.begin()+size, tree.begin()+n);
		build();
	}
	inline void build(){
		for(int i = n-1; i>=1; i--) tree[i] = tree[i<<1] + tree[i<<1|1];
	}
	inline void update(int idx, int ts, int te, int left, int right, int val){
		//cout<<"call update: "<<idx<<" "<<ts<<" "<<te<<" "<<left<<" "<<right<<" "<<val<<endl; 
		if(left>right) return;
		if(ts == left && te == right){ tree[idx]+=val*(te-ts+1);/*only for sum*/ pd[idx]+=val; return;}
		push_down(idx, ts, te); //update to most current for backtrace reupdate
		int tm = (ts+te)>>1;
		if(left<=tm)
			update(idx<<1,ts,tm,left,min(right,tm),val);
		if(right>tm)
			update(idx<<1|1,tm+1,te,max(tm+1,left),right,val);
		// reupdate values upstream
		tree[idx] = tree[idx<<1] + tree[idx<<1|1];
	}
	inline void update(int left, int right, int val){ update(1,0,n-1,left,right,val); }
	inline void push_down(int idx, int ts, int te){
		if(idx>=n || pd[idx]==0) return;
		int tm = (ts+te)>>1;
		tree[idx<<1] += pd[idx]*(tm-ts+1);
		tree[idx<<1|1] += pd[idx]*(te-tm);
		pd[idx<<1] += pd[idx];
		pd[idx<<1|1] += pd[idx];
		pd[idx] = 0;
	}
	inline llong query(int idx, int ts, int te, int left, int right){
		// both inclusive; ts, te indicate the coverage of this index
		if(left>right) return 0;
		push_down(idx,ts,te);
		if(ts == left && te == right) return tree[idx];
		int tm = (ts+te)>>1;
		llong sum = 0;
		if(left<=tm)
			sum+=query(idx<<1,ts,tm,left,min(right,tm));
		if(right>tm)
			sum+=query(idx<<1|1,tm+1,te,max(tm+1,left),right);
		return sum;
	}
	inline llong query(int left, int right){ return query(1,0,n-1,left,right); }
};

int main(){
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // int n = 100000;
    // iint arr[n];
    // For(i,n) arr[i]=rand()%1000000;
    // SegTree tr1(arr,n);
    // For(i,10000){
    // 	iint queryL = rand()%n;
    // 	iint queryR = rand()%n;
    // 	if(queryR<queryL) swap(queryR,queryL);
    // 	llong ret1 = tr1.query(queryL,queryR);
    // 	llong sum = 0;
    // 	for(iint i=queryL; i<=queryR; i++)
    // 		sum+=arr[i];
    // 	assert(ret1==sum);
    // 	iint updateL = rand()%n;
    // 	iint updateR = rand()%n;
    // 	if(updateR<updateL) swap(updateL,updateR);
    // 	iint updateVal = rand()%n;
    // 	//cout<<"change: "<<updatePos<<" "<<updateVal<<endl;
    // 	tr1.update(updateL, updateR, updateVal);
    // 	for(iint i=updateL;i<=updateR;i++)
    // 		arr[i] += updateVal;
    // }
}