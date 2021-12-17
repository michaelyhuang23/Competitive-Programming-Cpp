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
//#include "debughelp.hpp"

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
#define MOD 998244353LL

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint n;
    cin >> n;
    vector<tuple<llong,llong,bool> > portals(n);
    For(i,n){
    	llong x,y;
    	bool s;
    	cin >> x >> y >> s;
    	portals[i] = make_tuple(y,x,s);
    }
    auto sortSec = [&](tuple<llong,llong,bool> t1, tuple<llong,llong,bool> t2) -> bool{
    	return get<1>(t1) < get<1>(t2);
    };
    sort(portals.begin(),portals.end(),sortSec);
    vector<llong> dp(n);
    // wasted time to cross ith portal if all active
    dp[0] = (get<1>(portals[0]) - get<0>(portals[0]))%MOD;
    //deb(dp[0]);
    for(iint i = 1; i<n; i++){
    	auto backptr = lower_bound(portals.begin(), portals.end(), make_tuple(0,get<0>(portals[i]),false), sortSec);
    	iint idx = distance(portals.begin(), backptr) - 1;
    	//deb(idx); deb(i);
    	//cout << get<0>(portals[i]) << " "<< get<1>(portals[i]) << endl;
    	llong fcut = idx>=0 ? dp[idx] : 0;
    	dp[i] = dp[i-1] + get<1>(portals[i]) - get<0>(portals[i]) + (dp[i-1] - fcut);
    	dp[i] %= MOD;
    }
    //deb(dp);
    llong waste = 0;
    for(iint i=0; i<n; i++){
    	if(get<2>(portals[i])){
    		//cout << get<0>(portals[i]) << " "<< get<1>(portals[i]) << endl;
    		auto backptr = lower_bound(portals.begin(), portals.end(), make_tuple(0,get<0>(portals[i]),false), sortSec);
    		iint idx = distance(portals.begin(), backptr) - 1;
    		if(i==0)
    			waste+=get<1>(portals[i]) - get<0>(portals[i]);
    		else{
	    		llong fcut = idx>=0 ? dp[idx] : 0;
	    		llong fadd = i>0 ? dp[i-1] : 0;
	    		waste += fadd - fcut + get<1>(portals[i]) - get<0>(portals[i]);
	    	}
	    	waste %= MOD;
	    	if(waste<0){
	    		waste = (waste + MOD)%MOD;
	    	}
    	}
    }
    // deb(1ll + get<1>(portals[n-1]));
    // deb(waste);
    //assert(1ll + get<1>(portals[n-1]) >= 0);
    llong totalDist = (1ll + get<1>(portals[n-1]) + waste)%MOD;
    //assert(totalDist>=0);
    cout<<(MOD+totalDist)%MOD<<endl;
}






