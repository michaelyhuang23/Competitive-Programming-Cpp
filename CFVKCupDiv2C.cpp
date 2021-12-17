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

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint tt; cin >> tt;
    while(tt--){
    	iint n; cin >> n;
    	vector<pair<iint,iint> > caves(n);
    	For(i,n){
    		iint k; cin >> k;
    		iint maxPow=0;
    		for(iint j=0;j<k;j++){
    			iint a; cin >> a;
    			maxPow = max(maxPow, a-j);
    		}
    		caves[i] = make_pair(maxPow, k);
    	}
    	sort(caves.begin(), caves.end());
    	iint maxPow = 0;
    	iint prefixSum = 0;
    	for(iint i=0; i<n; i++){
    		maxPow = max(maxPow, caves[i].first - prefixSum);
    		prefixSum+=caves[i].second;
    	}
    	cout<<maxPow+1<<endl;
    }
}

/*

binary search power

each cave: compute min required power

sort in ascending order

*/




