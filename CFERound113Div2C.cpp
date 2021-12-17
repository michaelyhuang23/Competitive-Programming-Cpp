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
#include <unordered_map>
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
#define MOD 998244353

llong Pow(llong num, iint pow){
	if(pow==0) return 1;
	if(pow%2==0){
		llong inter = Pow(num, pow/2);
		return ((inter*inter)%MOD+MOD)%MOD;
	}else{
		return ((Pow(num, pow-1)*num)%MOD+MOD)%MOD;
	}
}

llong inverse(llong num){
	return Pow(num, MOD-2);
}

llong permutation(unordered_map<llong,iint>& hist){
	vector<iint> parts;
	for(auto const& pp : hist) parts.pb(pp.second);
	iint total = 0;
	for(iint i : parts) total+=i;
	llong numer = 1;
	for(iint i=1; i<=total; i++) numer=((numer*i)%MOD+MOD)%MOD;
	return ((numer)%MOD+MOD)%MOD;
}

llong choose(llong n, llong k){
	llong numer = 1;
	for(llong i=n; i>=n-k+1; i--) numer=((numer*i)%MOD+MOD)%MOD;
	llong denom = 1;
	for(llong i=k; i>=1; i--) denom=((denom*inverse(i))%MOD+MOD)%MOD;
	return ((numer*denom)%MOD+MOD)%MOD;
}

// int main(){
// 	cout<<choose(2,2)<<endl;

// }

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tt; cin >> tt;
    while(tt--){
    	iint n; cin >> n;
    	vector<llong> arr(n);
    	For(i,n) cin>>arr[i];
    	llong maxN=0;
    	llong maxS=0;
    	For(i,n) maxN = max(arr[i], maxN);
    	For(i,n) if(arr[i]!=maxN) maxS = max(arr[i], maxS);
    	iint maxC=0;
    	unordered_map<llong, iint> hist;
    	For(i,n) if(arr[i]==maxN) maxC++;
    	For(i,n){
    		if(hist.find(arr[i]) == hist.end()) hist[arr[i]]=1;
    		else hist[arr[i]]++;
    	}
    	if(maxC>1){
    		cout<<permutation(hist)<<endl;
    		continue;
    	}
    	if(maxN > maxS+1){
    		cout<<0<<endl;
    		continue;
    	}
    	unordered_map<llong, iint> histMax, histRest, histMax2;
    	histMax[maxN] = hist[maxN];
    	histMax[maxS] = hist[maxS];
    	histMax2[maxS] = hist[maxS];
    	llong maxCount = histMax[maxN] + histMax[maxS];
    	for(auto const& pp : hist){
    		if(pp.first == maxN || pp.first == maxS) continue;
    		histRest[pp.first] = pp.second;
    	}
    	llong count = 1;
    	count *= permutation(histMax)-permutation(histMax2);
    	count = ((count*permutation(histRest))%MOD+MOD)%MOD;
    	count = ((count * choose(n, maxCount))%MOD+MOD)%MOD; 
    	cout<<count<<endl;
    }
}

/*

if 1 num is 2+ the next largest,
it breaks: 0

if the largest is 1+ the next largest
it can't be at the end position 
(if has to be before some other next large int)

if largest is 0+ next largest, no problem

*/




