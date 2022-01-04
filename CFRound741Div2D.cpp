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
#include "debughelp.hpp"

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
    int tt; cin >> tt;
    while(tt--){
    	iint n,q; cin >> n >> q;
    	vector<int> arr(n);
    	For(i,n) {
    		char c;
    		cin>>c;
    		if(c=='+')
    			arr[i]=1;
    		else
    			arr[i]=-1;
    	}
    	vector<iint> prefSep(n);
    	prefSep[0] = arr[0]; prefSep[1] = arr[1];
    	for(iint i=2; i<n; i++)
    		prefSep[i] = prefSep[i-2]+arr[i];
    	
    	vector<iint> pref(n);
    	pref[0] = arr[0];
    	for(iint i=1; i<n; i++){
    		if(i%2==0) pref[i] = pref[i-1] + arr[i];
    		else pref[i]=pref[i-1]-arr[i];
    	}
    	deb(arr);
    	deb(pref);
    	cout<<"hello1"<<endl;
    	unordered_map<iint, vector<iint> > val2pos;
    	val2pos[0]=vector<iint>();
    	val2pos[0].pb(-1);

    	For(i,n){
    		if(val2pos.find(pref[i]) == val2pos.end())
    			val2pos[pref[i]] = vector<iint>();
    		val2pos[pref[i]].pb(i);
    	}
    	cout<<"hello2"<<endl;
    	For(i,q){
    		iint l, r; cin >> l >> r;
    		l--; r--;
    		iint val = 0;
    		if(l-1>=0)
    			val = pref[l-1];
    		auto gg = upper_bound(val2pos[val].begin(), val2pos[val].end(), r);
    		cout<<"hello3"<<endl;
    		gg--;
    		cout<<"hello4"<<endl;
    		if((*gg)==r){
    			cout<<0<<endl;
    			continue;
    		}
    		if((*gg)>l-1){
    			cout<<1<<endl;
    			cout<<"found "<<*gg<<endl;
    			continue;
    		}
    		cout<<2<<endl;

    	}
    }
}

/*
-1+1+1-1 - 1-1+1 = v
1-1+1 - 1+1-1
-2v-1
+--++-+-++-++-
+--++-+++-++-
+--+-+++-++-

flip 1: the tail contribution flips

flip 2: the mid segment contribution flips

+-+-
-2v(-2/+2)
*/







