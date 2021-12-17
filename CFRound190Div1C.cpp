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

vector<vector<iint> > adj;
vector<bool> used;
vector<iint> counter;
vector<iint> cfa;
vector<iint> cdepth;
vector<vector<iint> > cadj;

void get_count(iint cur, iint father){
	counter[cur] = 1;
	for(iint son : adj[cur]){
		if(son == father || used[son]) continue;
		get_count(son, cur);
		counter[cur] += counter[son];
	}
}

iint find_centroid(iint cur, iint father, iint root){
	iint sumdown = 0;
	for(iint son : adj[cur]){
		if(son == father || used[son]) continue;
		if(counter[son]*2 > counter[root]) return find_centroid(son, cur, root);
		sumdown += counter[son];
	}
	iint up = counter[root]-1-sumdown;
	assert(up*2 <= counter[root]);
	return cur;
}

iint build_centree(iint n, iint cur){
	get_count(cur, cur);
	iint centroid = find_centroid(cur, cur, cur);
    used[centroid] = true;
	for(iint son : adj[centroid])
		if(!used[son]) cfa[build_centree(n, son)] = centroid;
	return centroid;
}

void dfs(iint cur, iint father){
	if(cur==father) cdepth[cur] = 0;
	else cdepth[cur] = cdepth[father]+1;
	for(iint son : cadj[cur])
		if(son!=father) dfs(son, cur);
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint n; cin >> n;
    adj = vector<vector<iint> >(n);
    used = vector<bool>(n,0);
    For(i, n-1){
    	iint a, b; cin >> a >> b; a--; b--;
    	adj[a].pb(b); adj[b].pb(a);
    }
    counter = vector<iint>(n, 0);
    cfa = vector<iint>(n, 0);
    iint croot = build_centree(n, 0);
    cfa[croot] = croot;
    cdepth = vector<iint>(n,0);
    cadj = vector<vector<iint> >(n);
    For(i, n){
    	cadj[i].pb(cfa[i]);
    	cadj[cfa[i]].pb(i);
    }
    dfs(croot, croot);
    For(i, n-1){
    	cout<<(char)(cdepth[i] + 'A') <<" ";
    }
    cout<<(char)(cdepth[n-1] + 'A') <<endl;
}

/*

If we do centroid decomposition

on the centroid tree, we rank nodes by their depth. 

Now any two nodes (a,b) with same depth must be connected through their LCA on centroid tree which has lower depth

1. centroid tree building
	a. subtree size counting
	b. centroid finding

*/