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
#define inf (llong)1223372036854775807
#define PI 3.1415926
#define MOD 1000000007

iint n,k;
vector<llong> s,p;

llong cost(iint i, iint j){
	i--;
	return p[i]-p[j] - j*(s[i] - s[j]);
}

void compute_range(vector<vector<iint> >& dp, iint k, iint l, iint r, iint rl, iint rr){
	if(l>r) return;
	//cout<<k<<" "<<l<<" "<<r<<" "<<rl<<" "<<rr<<endl;
	iint mid = (l+r)/2; // all inclusive
	llong minC = inf;
	llong minI = 1;
	for(iint j=rl; j<=min(rr,mid-1); j++){
		llong co = dp[k-1][j] + cost(mid,j);
		if(co < minC){
			minC = co;
			minI = j;
		}
	}
	//assert(minI != -1);
	dp[k][mid] = minC;
	//cout<<mid<<" "<<minI<<endl;
	compute_range(dp, k, l, mid-1, rl, minI);
	compute_range(dp, k, mid+1, r, minI, rr);
}

llong process_line(vector<iint>& arr){
	s = vector<llong>(n+1,0);
	for(iint i = 1; i<=n; i++) s[i]=s[i-1]+arr[i];
	p = vector<llong>(n+1,0);
	for(iint i = 1; i<=n; i++) p[i]=p[i-1]+i*arr[i];
	vector<vector<iint> > dp(k+1);
	For(i, k+1) dp[i] = vector<iint>(n+1,inf/4);
	dp[1][1] = 0; // insert 1 open at the beginning by default.
	for(iint ki = 2; ki <= k; ki++){
		compute_range(dp, ki, 1, n, 1, n);
	}

	llong minV = inf;
	for(iint ki = 1; ki <= k; ki++)
		for(iint i = 1; i <= n; i++)
			minV = min(minV,dp[ki][i]+cost(n+1,i));

	assert(minV != inf);
	return minV;
}

int main() {
	ifstream fin("cbarn.in");
	ofstream fout("cbarn.out");
    ios_base::sync_with_stdio(0);
    fin.tie(0);
    fin >> n >> k;
    vector<iint> tar(n);
    For(i, n) fin >> tar[i];
    llong minV = inf;
    for(iint st = 0; st < n; st++){
    	vector<iint> line(n+1);
    	for(iint i=0; i<n; i++) line[i+1] = tar[(i+st)%n];
    	llong val = process_line(line);
    	minV = min(minV, val);
    }
    fout<<minV<<endl;
    fout.close();
}

/*

dp[k][i] = Mj dp[k-1][j] + C(i, j) such that j<i

Let f[k][i] give the min j value, then f is 
monotonically increasing as i increases

Thus, we can use D&C DP

First we compute 
dp[k][(1+m)/2]
then we compute the lower and upper halves (both will have limited search range)

*/



