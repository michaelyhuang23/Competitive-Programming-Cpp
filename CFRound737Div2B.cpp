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
    int t;
    cin >> t;
    while(t--){
    	iint n,k;
    	cin >> n >> k;
    	llong arr[n];
    	For(i,n) cin >> arr[i];
    	llong sorted[n];
    	copy(arr, arr+n, sorted);
    	sort(sorted,sorted+n);
    	llong* mirrorit = 0;
    	iint count = 0;
    	for(iint i=0;i<n;i++){
    		count++;
    		mirrorit = lower_bound(sorted, sorted+n, arr[i]);
    		assert(*mirrorit == arr[i]);
    		while(mirrorit<sorted+n && i<n && *mirrorit == arr[i]) i++, mirrorit++;
    		i--;
    	}
    	if(count<=k)
    		cout<<"YES"<<endl;
    	else
    		cout<<"NO"<<endl;
    }
}

/*

consecutive elements that are ascending and consecutive in sorted version can be a bucket





*/


