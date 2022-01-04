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

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint n; llong MOD;
    cin >> n >> MOD;
    vector<llong> dp(n+1);
    dp[n] = 1;
    fill(dp.begin(), dp.end(), 0);
    vector<llong> postfix(n+1);
    postfix[n] = 1;
    for(iint i=n-1; i>=1; i--){
    	// addition
    	dp[i] = postfix[i+1];
    	// multiplication
    	for(iint mul = 2; mul*i<=n; mul++){
    		iint res = mul*i;
    		iint end = mul*(i+1);
    		llong endV = 0;
    		if(end<=n)
    			endV = postfix[end];
    		dp[i] += postfix[res] - endV;
    		dp[i] %= MOD;
    	}
    	postfix[i] = (postfix[i+1] + dp[i])%MOD;
    }
    //deb(dp);
    cout<<dp[1]%MOD<<endl;
}

/*
try all multiplications
log(n)? 

use prefix sum
*/

