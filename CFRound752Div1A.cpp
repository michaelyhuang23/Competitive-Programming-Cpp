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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint tt; cin >> tt;
    while(tt--){
    	iint n; cin >> n;
    	vector<iint> arr(n);
    	For(i,n) cin >> arr[i];
    	vector<vector<iint> > rmq(18);
    	For(i,18) rmq[i] = vector<iint>(n+5);
    	For(i, n+5) rmq[0][i] = i;
    	for(iint i=1; i<18; i++)
    		for(iint j=0; j<n+5; j++)
    			if(j+(1<<i)<n+5) rmq[i][j] = lcm(rmq[i-1][j],rmq[i-1][min(n+4,j+(1<<(i-1)))]);
    	iint c = 0;
    	vector<bool> clear(n,0);
    	for(iint i = 0; i<n; i++){
    		if(arr[i]%(i+1) != 0){c++; clear[i]=1; continue;}
    		iint start = i-c+2;
    		iint end = i+2;
    		iint span = end-start+1;
    		iint result = 1;
    		iint pos = 0;
//            deb(start);
//            deb(end);
//            deb(arr[i]);
    		for(iint i = 0; i<18; i++){
    			if((1<<i)&span){
    				result = lcm(result,rmq[i][pos+start]);
    				pos+=1<<i;
    				if(pos == span) break;
    			}
    		}
    		if(arr[i]%result != 0){ c++; clear[i]=1; }
    	}
    	bool allClear = 1;
    	for(bool i : clear) allClear &= i;
    	if(!allClear) cout<<"NO"<<endl;
    	else cout<<"YES"<<endl;
    }
}




