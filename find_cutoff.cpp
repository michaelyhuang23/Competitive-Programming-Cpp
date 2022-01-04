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

static iint up_pow(iint num){
	for(int i=0;i<=64;i++)
		if((1<<i)>num)
			return 1<<i;
	return -1;
}

struct SegTree
{
	static const iint N = 100000;
	iint tree[N*2];
	iint n;
	SegTree(iint* arr, iint size){
		n = up_pow(size);
		copy(arr,arr+size,tree+n);
		build();
	}
	inline void build(){
		for(iint i=n-1; i>=1; i--) tree[i] = max(tree[i<<1],tree[i<<1|1]);
	}
	inline void change(iint idx, iint val){
		tree[idx+n]=val;
		for(iint i=(idx+n)>>1; i>=1; i>>=1) tree[i] = max(tree[i<<1],tree[i<<1|1]);
	}
	inline iint search(iint cutoff){
		if(tree[1]<cutoff)
			return -1;
		iint i;
		for(i=2;i<2*n;i<<=1)
			if(tree[i]<cutoff) i++;
		i>>=1;
		return i-n;
	}
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    iint arr[n];
    For(i,n) cin>>arr[i];
    // now we want to find the first value larger than some cutoff within the array
    /*
		each node stores the first number larger than the query (but the query changes) X
		each node stores the largest number; (just a binary search tree with info about ranges);
		then in a search, for recursive solution: if left interval contains it then go there, else go to the right.

		To implement this in for loop:
		for( i ...){
			if tree[i<<1] > cutoff:
				i = i<<1
			else
				i = i<<1+1
		}
    */
    SegTree tr(arr,n);
    int q;
    cin >> q;
    For(i,q){
    	iint c;
    	cin>>c;
    	cout<<tr.search(c)<<'\n';
    }
}
























