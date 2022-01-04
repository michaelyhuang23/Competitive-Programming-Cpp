#include <iostream>
#include <fstream>
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

ofstream fout("balancing.out");
ifstream fin("balancing.in");

// tuple<iint,iint,iint,iint> getCounts(iint x, iint y, iint* xs, iint* ys, iint n){
// 	iint lt = 0, rt = 0, lb = 0, rb = 0;
// 	For(i,n){
// 		if(xs[i]<x && ys[i]<y)
// 			lb++;
// 		else if(xs[i]>x && ys[i]<y)
// 			rb++;
// 		else if(xs[i]<x && ys[i]>y)
// 			lt++;
// 		else if(xs[i]>x && ys[i]>y)
// 			rt++;
// 		else
// 			assert(false);
// 	}
// 	return make_tuple(lb,rb,lt,rt);
// }
struct SegTree
{
	iint pow_up(iint num){
		For(i,65) if(1<<i >= num) return 1<<i;
		return -1;
	}
	iint* tree;
	iint n;
	SegTree(iint* arr, iint n_){
		n = pow_up(n_);
		tree = new iint[n*2];
		copy(arr, arr+n_, tree+n);
		fill(tree+n+n_, tree+2*n, 0);
		build();
	}
	inline void build(){
		for(iint i=n-1; i>=1; i--) pullup(i);
	}
	inline void pullup(iint idx){
		tree[idx] = tree[idx<<1] + tree[idx<<1|1];
	}
	inline void change(iint idx, iint val){
		tree[idx+n] += val;
		for(iint i=(idx+n)>>1; i>=1; i>>=1) pullup(i);
	}
	inline iint get_range(iint left, iint right){
		left+=n, right+=n;
		iint sum = 0;
		for(;left<=right;left>>=1,right>>=1){
			if(left&1) 
				sum+=tree[left++];
			if(!(right&1))
				sum+=tree[right--];
			if(left==right) break;
		}
		return sum;
	}
};

int main(){
	// fout<<"h1"<<endl;
    ios_base::sync_with_stdio(0);
    fin.tie(0);
    iint n;
    const iint m = 1000005;
    fin >> n;
    iint* arrr = new iint[m]; fill(arrr,arrr+m,0);
    pair<iint,iint>* prts = new pair<iint,iint>[n];
    // fout<<"h2"<<endl;
    For(i,n) {
    	iint x,y;
    	fin >> x >> y;
    	arrr[y]+=1;
    	prts[i] = make_pair(x,y);
    }
    sort(prts,prts+n);
    iint* arrl = new iint[m]; fill(arrl,arrl+m,0);
    SegTree ltr(arrl,m);
    SegTree rtr(arrr,m);
    iint curx = -1;
    iint minVal = inf;
    for(iint i=0;i<n;i++){
    	// we stop to evaluate after each x
    	curx = get<0>(prts[i]);
    	while(get<0>(prts[i])==curx){ 
    		rtr.change(get<1>(prts[i]),-1);
    		ltr.change(get<1>(prts[i]),1);
    		i++;
    	}
    	i--;
    	iint bot = 0, top = 500001;
    	while(bot<=top){
    		iint mid = ((bot+top)/2);
    		iint botl = ltr.get_range(0, mid*2);
    		iint topl = i+1-botl;
    		iint botr = rtr.get_range(0, mid*2);
    		iint topr = n-i-1-botr;
    		iint topa = max(topl, topr);
    		iint bota = max(botl, botr);
    		if(bota >= topa){
    			minVal = min(minVal,bota);
    			top=mid-1;
    		}else{
    			minVal = min(minVal,topa);
    			bot=mid+1;
    		}
    	}
    }
    fout<<minVal<<endl;
}

/*
sweep line over x, do binary search over y. But how to count points?
segtree!: we need point updates, range query. so let's do binary search within segtree. 

*/









