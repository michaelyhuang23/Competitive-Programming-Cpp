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
#include <unordered_set>
#include <fstream>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

int main() {
	vector<iint> log2_val(1000000);
	log2_val[0] = -1;
	for(iint i = 1; i<1000000; i++) log2_val[i] = log2_val[i/2]+1;
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint n, m, q;
    cin >> n >> m >> q;
    vector<iint> perm(n);
    vector<iint> arr(m);
    For(i,n) cin >> perm[i];
    For(i,n) perm[i]--;
    vector<iint> loc(n);
    For(i,n) loc[perm[i]] = i;
    For(i,m) cin >> arr[i];
    For(i,m) arr[i]--;
    vector<vector<iint> > pos(n, vector<iint>());
    For(i,m) pos[arr[i]].pb(i);
    vector<iint> nxt(m);
    
    For(i,m){
    	iint l = (loc[arr[i]]+1)%n;
    	iint val = perm[l];
    	iint rp = lower_bound(pos[val].begin(), pos[val].end(), i) - pos[val].begin();
    	if(rp >= pos[val].size()) nxt[i] = m;
    	else nxt[i] = pos[val][rp]; // m means doesn't exist
    }

    vector<vector<iint> > ancs(20);
    For(i,20) ancs[i] = vector<iint>(m+1, m);
    For(i, m) ancs[0][i] = nxt[i]; ancs[0][m] = m;
    for(iint i=1; i<20; i++) For(j, m+1) ancs[i][j] = ancs[i-1][ancs[i-1][j]];

    vector<iint> nanc(m);
	For(i,m){
		iint l = n-1;
		iint pos = i;
		for(iint j=0; j<20; j++) if(((l>>j) & 1)) pos = ancs[j][pos];
		nanc[i] = pos; // m means doesn't exist
	}

	vector<vector<iint> > rmq(20);
	For(i,20) rmq[i] = vector<iint>(m, inf);
	For(j,m) rmq[0][j] = nanc[j];
	for(iint i=1; i<20; i++) For(j, m-(1<<i)+1) rmq[i][j] = min(rmq[i-1][j], rmq[i-1][j+(1<<(i-1))]);

    For(i,q){
    	iint l,r;
    	cin >> l >> r;
    	l--;
    	iint range = r-l;
    	iint logr = log2_val[range];
    	iint left = rmq[logr][l];
    	iint right = rmq[logr][r-(1<<logr)];
    	iint ans = min(left, right);
    	if(ans>=r) cout<<0;
    	else cout<<1;
    }
    cout<<endl;

}

/*

once first element is determined, we can determined the min length 
of the shifted permutation. Then query becomes querying containment of 
such an interval in the query intervals. 

DP problem:
dp[i] = dp[i+k]+1 where i+k gives the first occurrence of the next element
but what does DP store?

Let's formulate in graph instead
nxt[i] = i+k where i+k gives the first occurrence of the next element
nxt is computable in O(n). This forms a forest of course. 

Now for the query, we need to determine if a path of length n exists 
in the interval. 

For each position, we can simply compute its nth ancestor 
in total O(nlogn)

chug those values in RMQ or segtree. Now we can find the min in 
an interval

*/