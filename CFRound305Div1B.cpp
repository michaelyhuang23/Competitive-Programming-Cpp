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
#include <unordered_map>

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

struct UFDS{
	iint* parents;
	iint* sizes;
	iint max_size;
	UFDS(iint n){
		parents = new iint[n];
		sizes = new iint[n];
		max_size = 1;
		fill(sizes, sizes+n, 1);
		For(i,n) parents[i]=i;
	}
	iint find(iint idx){
		iint i = idx;
		while(parents[i]!=i) i=parents[i];
		for(iint j=idx;parents[j]!=j;j=parents[j]) parents[j]=i;
		return i;
	}
	void merge(iint a, iint b){
		iint pa = find(a);
		iint pb = find(b);
		if(pa != pb){
			if(sizes[pa]>sizes[pb]){
				parents[pb] = pa;
				sizes[pa] += sizes[pb];
				max_size = max(max_size,sizes[pa]);
			}else{
				parents[pa] = pb;
				sizes[pb] += sizes[pa];
				max_size = max(max_size,sizes[pb]);
			}
		}
	}
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint n;
    cin >> n;
    iint* heights=new iint[n];
    bool* active = new bool[n];
    fill(active,active+n,false);
    For(i,n) cin >> heights[i];
    iint* sortedH = new iint[n];
    copy(heights,heights+n,sortedH);
    sort(sortedH, sortedH+n);
    unordered_map<iint, vector<iint>> h2vtx;
    For(i,n) h2vtx[heights[i]].pb(i);
    UFDS finder(n);
    iint* sizes = new iint[n+1];
    fill(sizes,sizes+n+1,0);
    iint max_size = 0;
    for(iint i=n-1; i>=0; i--){
    	iint h = sortedH[i];
    	// cout<<h << " " <<finder.max_size <<endl;
    	// For(j,n) cout<< finder.find(j) <<" ";
    	// cout<<endl;
    	for(iint vtx : h2vtx[h]){
    		active[vtx]=true;
    		if(vtx>0 && active[vtx-1]) finder.merge(vtx-1,vtx);
    		if(vtx<n-1 && active[vtx+1]) finder.merge(vtx+1,vtx);
    	}
    	for(iint s = max_size+1; s<=finder.max_size; s++)
    		sizes[s] = h;
    	max_size = finder.max_size;
    }
    for(iint i=1; i<n; i++) cout<<sizes[i]<<" ";
    cout<<sizes[n]<<endl;
}


/*
iterate from max strength to min strength
We only keep points >= max strength active; so as we iterate, more points become active
We connect them using UFDS. Query the max contagious interval size
for all intervals <= that max size --> we update its value
*/



