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

void dfs(iint father, iint cur, iint depth, vector<vector<iint> >& adj, vector<iint>& fa, vector<iint>& dep){
	for(iint son : adj[cur]){
		if(father == son) continue;
		dfs(cur, son, depth+1, adj, fa, dep);
	}
	dep[cur] = depth;
	fa[cur] = father;
}

iint find_lcs(iint a, iint b, vector<vector<iint> >& ancs, vector<iint>& dep){
	if(dep[b]<dep[a]){ iint tmp=b; b=a; a=tmp; }
	assert(dep[b]>=dep[a]);
	iint diff = dep[b] - dep[a];
	for(iint i=0; i<20; i++) if((diff>>i) & 1) b = ancs[i][b];
	// level to the same
	assert(dep[b]==dep[a]);
    if(a==b) return a;
	for(iint i=19; i>=0; i--) if(ancs[i][b] !=  ancs[i][a]) {
		a = ancs[i][a];
		b = ancs[i][b];
	}
	a = ancs[0][a];
	b = ancs[0][b];
	assert(a==b);
	return a;
}

iint countMax = 0;

iint dfs_count(iint father,iint cur,vector<vector<iint> >& adj,vector<iint>& lcas, vector<iint>& isQ){
	iint count = 0;
	for(iint son : adj[cur]){
		if(father == son) continue;
		count += dfs_count(cur, son, adj, lcas, isQ);
	}
	count+=isQ[cur];
	count-=lcas[cur]; // this gives the correct current count
	countMax = max(countMax, count);
	count-=lcas[cur]; // this gives the correct branch count of parent
	return count;
}

int main() {
    ios_base::sync_with_stdio(0);
    ifstream fin("maxflow.in");
    ofstream fout("maxflow.out");
    fin.tie(0);
    iint N, K;
    fin >> N >> K;
    vector<vector<iint> > adj(N);
    For(i,N-1){
    	iint a, b;
    	fin >> a >> b;
    	a--; b--;
    	adj[a].pb(b);
    	adj[b].pb(a);
    }
    vector<iint> fa(N);
    vector<iint> dep(N);
    dfs(0, 0, 0, adj, fa, dep);
    vector<vector<iint> > ancs(20);
    For(i,20) ancs[i] = vector<iint>(N);
    For(i,N) ancs[0][i] = fa[i];

    for(iint i=1; i<20; i++) For(j,N) ancs[i][j] = ancs[i-1][ancs[i-1][j]];

    vector<iint> lcas(N);
	vector<iint> isQ(N);
    For(i,K){
    	iint a,b;
    	fin >> a >> b; a--; b--;
    	isQ[a] ++;
    	isQ[b] ++;
    	iint lcm = find_lcs(a,b,ancs,dep);
    	lcas[lcm]++;
    }
    dfs_count(0,0,adj,lcas,isQ);
    fout<<countMax<<endl;
    fout.close();
}

/*

the max point can only occur at LCMs. So we find the LCM for each path
then count how many times each LCM appears


this is actually completely wrong
*/