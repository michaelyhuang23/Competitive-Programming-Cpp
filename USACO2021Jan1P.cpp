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

#include "debughelp.hpp"


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


tuple<vector<llong>, vector<llong>, vector<llong>, vector<llong> > process_graph(iint n, iint m){
	vector<vector<iint> > adj(n);
	vector<bool> loop(n,0);
	For(i,n) adj[i] = vector<iint>();
	For(i,m) {
		iint a, b; cin >> a >> b; a--; b--;
		if(a==b){ loop[a] = true; continue; }
		adj[a].pb(b);
		adj[b].pb(a);
	}
	vector<vector<iint> > fReach(n); // reachable by 0,0
	For(i,n) { fReach[i] = vector<iint>(2); fReach[i][0]=inf/2*2; fReach[i][1]=inf/2*2-1; }
	fReach[0][0] = 0;
	// fReach[i][2] vtx i first reachable in even and odd?
	for(iint t=0; t<n+5; t++){
		for(iint i=0; i<n; i++){
			for(iint o : adj[i]){
				if(!loop[o]){// if loop i, that's fine, it doesn't output
					fReach[i][0] = min(fReach[i][0], fReach[o][1]+1);
					fReach[i][1] = min(fReach[i][1], fReach[o][0]+1);
				}
			}
		}
	}
	For(i,n) assert(fReach[i][0]%2 == 0);
	For(i,n) assert(fReach[i][1]%2 == 1);
	vector<vector<iint> > dReach(n); // reachable by 0,0
	For(i,n) { dReach[i] = vector<iint>(2); dReach[i][0]=inf/2*2; dReach[i][1]=inf/2*2-1; }
	for(iint i = 0; i<n; i++){
		if(loop[i]){
			dReach[i][0] = fReach[i][0];
			dReach[i][1] = fReach[i][1];
		}
	}
	// dReach[i][2] vtx i first reachable in even and odd passing loop?
	for(iint t=0; t<n+5; t++){
		for(iint i=0; i<n; i++){
			for(iint o : adj[i]){
				dReach[i][0] = min(dReach[i][0], dReach[o][1]+1);
				dReach[i][1] = min(dReach[i][1], dReach[o][0]+1);
			}
		}
	}

	For(i,n) assert(dReach[i][0]%2 == 0);
	For(i,n) assert(dReach[i][1]%2 == 1);

	iint si = n+5;
	vector<llong> peven(si,0);
	for(iint i = 0; i<n; i++) if(fReach[i][0] <si) peven[fReach[i][0]]++;
	for(iint i = 1; i<si; i++) peven[i] = peven[i-1] + peven[i];
	vector<llong> podd(si,0);
	for(iint i = 0; i<n; i++) if(fReach[i][1] <si) podd[fReach[i][1]]++;
	for(iint i = 1; i<si; i++) podd[i] = podd[i-1] + podd[i];

	vector<llong> deven(si,0);
	for(iint i = 0; i<n; i++) if(dReach[i][0] <si) deven[dReach[i][0]]++;
	vector<llong> dodd(si,0);
	for(iint i = 0; i<n; i++) if(dReach[i][1] <si) dodd[dReach[i][1]]++;

	vector<llong> pdeven(si,0);
	for(iint i = 1; i<si; i++) pdeven[i] = pdeven[i-1] + deven[i];
	vector<llong> pdodd(si,0);
	for(iint i = 1; i<si; i++) pdodd[i] = pdodd[i-1] + dodd[i];

	for(iint i=1; i<si; i++) podd[i] += pdodd[i];
	for(iint i=1; i<si; i++) peven[i] += pdeven[i];
	assert(peven[0] == 1);
	deb(peven);
	deb(podd);
	return make_tuple(peven, podd, deven, dodd);
}

int main() { // remember to add MOD!!!!
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint K; cin >> K;
    vector<vector<llong> > pevens;
    vector<vector<llong> > podds;
    vector<vector<llong> > devens;
    vector<vector<llong> > dodds;
    iint maxn = 0;
    For(i, K){
    	iint n, m;
    	cin >> n >> m;
    	maxn = max(maxn,n);
    	auto ret = process_graph(n,m);
    	pevens.pb(get<0>(ret));
    	podds.pb(get<1>(ret));
    	devens.pb(get<2>(ret));
    	dodds.pb(get<3>(ret));
    }
    maxn+=5;
    llong total = 0;
    for(iint d=1; d<maxn; d++){
    	llong result = 0;
    	if(d%2==0){
    		llong cur = 1;
    		llong pas = 1;
    		For(i,K){
    			llong ret = 1;
    			if(d >= pevens[i].size())
    				ret = pevens[i][pevens[i].size()-1];
    			else ret = pevens[i][d];
    			cur*=ret;
    			ret = 1;
    			if(d-2 >= pevens[i].size())
    				ret = pevens[i][pevens[i].size()-1];
    			else ret = pevens[i][d-2];
    			pas*=ret;
    		}
    		result = cur-pas;
    		llong oddS = 1;
    		For(i,K) oddS *= dodds[i][d-1];
    		result -= oddS;
    	}else{
    		llong cur = 1;
    		llong pas = 1;
    		if(d-2<1) pas = 0;
    		For(i,K){
    			llong ret = 1;
    			if(d >= podds[i].size())
    				ret = podds[i][podds[i].size()-1];
    			else ret = podds[i][d];
    			cur*=ret;
    			ret = 1;
    			if(d-2 >= podds[i].size())
    				ret = podds[i][podds[i].size()-1];
    			else ret = podds[i][d-2];
    			pas*=ret;
    		}
    		result = cur-pas;
    		llong evenS = 1;
    		For(i,K) evenS *= devens[i][d-1];
    		result -= evenS;
    	}
    	total += result*d;
    }
    cout<<total<<endl;
}

/*

dp count reachability for each graph (no self loops)

dp2 count reachability going through a self loop

states a distance x away is:

(reachable by x without self loop) + (reachable by x passing self loop) = reachable with or without self loop

multiply them --> all states reachable by x with or without self loop

- all states reachable by x-2 with or without self loop (also reachable by x)

= all states first reached by x or x-1 with or without self loop

- all states first reached by x-1 and passes through self loop

= all states first reached by x with or without self loop



*/











