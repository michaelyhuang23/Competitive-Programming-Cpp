#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <unordered_set>

// #include "debughelp.hpp"

using namespace std;

typedef long int iint;
typedef long long int llong;
#define For(i, j) for (int i=0 ; i<j ; i++)
#define mp make_pair
#define pb push_back
#define inf (int)2147483647
#define PI 3.1415926
#define MOD 1000000007

struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return (llong)v.first*300005LL+(llong)v.second;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m; cin >> n >> m;
    int q; cin >> q;
    // let n always be first and the small one
    bool rev = false;
    if(n>m){ swap(n, m); rev=true; }
    unordered_set<pair<int,int>, pair_hash> specials(q);
    For(i,q) {
    	int a, b; cin >> a >> b;
    	if(!rev) specials.insert(mp(a,b));
    	else specials.insert(mp(b,a));
    }
    // now n<m
    vector<vector<int> > dp(5);
    For(i,5) dp[i] = vector<int>(n+1,-inf);
    dp[0][1] = 1;
    dp.reserve(1000);
    int winT = -1;
    for(int t = 0; t < 300005; t++){
    	dp.pb(vector<int>(n+1,-inf));
    	for(int i=1; i<=n; i++){
    		int maxJ = dp[t][i]; // why care about lower j values? they are just worse!
    		if(maxJ <= 0) continue;
    		if(maxJ >= m && i==n) {winT = t; break;}
    		dp[t+1][i] = max(dp[t+1][i],dp[t][i]+i);
    		dp[t+1][min(n,i+maxJ)] = max(dp[t+1][min(n,i+maxJ)], maxJ);
    		if(specials.find(mp(i,maxJ)) != specials.end()){
    			dp[t+1][i] = max(dp[t+1][i],dp[t][i]+i+1);
    			dp[t+1][min(n,i+maxJ+1)] = max(dp[t+1][min(n,i+maxJ+1)], maxJ);
    		}
    	}
    	if(winT>-1)break;
    }
    //deb(dp);
    cout<<winT<<endl;
}