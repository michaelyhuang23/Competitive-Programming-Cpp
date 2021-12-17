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

vector<iint> fa;
vector<vector<iint> > adj;
vector<vector<iint> > cadj;
vector<iint> counter;
vector<bool> used;
vector<iint> cfa;
vector<iint> depth;
vector<vector<iint> > binj;
vector<bool> active;
vector<pair<iint,iint> > maxlen;
vector<pair<iint,iint> > maxlen2;

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

iint build_centree(iint cur){
	get_count(cur, cur);
	iint centroid = find_centroid(cur, cur, cur);
    used[centroid] = true;
	for(iint son : adj[centroid])
		if(!used[son]) cfa[build_centree(son)] = centroid;
	return centroid;
}

void dfs(iint cur, iint par){
	if(cur == par) depth[cur] = 0;
	else depth[cur] = depth[par] + 1;
	for(iint son : adj[cur]) if(son != par) dfs(son, cur);
}

iint find_lca(iint a, iint b, vector<vector<iint> >& ancs, vector<iint>& dep){
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

iint dist(iint a, iint b){
	iint lca = find_lca(a,b,binj,depth);
	return depth[a] - depth[lca] + depth[b] - depth[lca];
}

int main() {
    ifstream fin("newbarn.in");
    ofstream fout("newbarn.out");
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint Q; cin>>Q;
    vector<iint> queries(Q);
    vector<bool> isU(Q);
    fa = vector<iint>();
    For(i, Q){
    	char type; cin >> type;
    	if(type=='B') isU[i] = true;
    	else isU[i] = false;
    	iint vtx; cin >> vtx; vtx--;
        if(isU[i]){
            queries[i] = fa.size();
            if(vtx<0) vtx = fa.size();
            fa.pb(vtx);
        }else{
            queries[i] = vtx;
        }
    }
    iint n = fa.size();
    adj = vector<vector<iint> >(n);
    For(i, n){
        if(i == fa[i]) continue;
    	adj[i].pb(fa[i]);
    	adj[fa[i]].pb(i);
    }
    active = vector<bool>(n,0);
    binj = vector<vector<iint> >(25);
    For(i, 25) binj[i] = vector<iint>(n);
    For(i, n) binj[0][i] = fa[i];
    for(iint i=1; i<25; i++) For(j, n) binj[i][j] = binj[i-1][binj[i-1][j]];

    cfa = vector<iint>(n, 0);
    counter = vector<iint>(n, 0);
    used = vector<bool>(n,0);
    maxlen = vector<pair<iint,iint> >(n, make_pair(0,-1));
    maxlen2 = vector<pair<iint,iint> >(n, make_pair(0,-1));
    For(i,n) maxlen[i] = make_pair(1, i);
    For(i,n) maxlen2[i] = make_pair(1, i);
    iint croot = build_centree(0);
	cfa[croot] = croot;
    depth = vector<iint>(n,0);
	dfs(0,0);


	cadj = vector<vector<iint> >(n);
	For(i, n){
        if(i==cfa[i]) continue;
    	cadj[i].pb(cfa[i]);
    	cadj[cfa[i]].pb(i);
    }

    For(i, Q){
    	if(isU[i]){ // update
    		iint vtx = queries[i];
    		active[vtx] = true;
    		iint prev = vtx;
            if(vtx != croot) {
                for (iint v = cfa[vtx]; true; v = cfa[v]) {
                    iint dd = dist(vtx, v) + 1;
                    if (dd >= maxlen[v].first) {
                        if (maxlen[v].second == prev) {
                            maxlen[v].first = dd;
                        } else {
                            maxlen2[v] = maxlen[v];
                            maxlen[v] = make_pair(dd, prev);
                        }
                    } else if (dd > maxlen2[v].first) {
                        if (prev != maxlen[v].second) {
                            maxlen2[v] = make_pair(dd, prev);
                        }
                    }
                    prev = v;
                    if (v == croot) break;
                }
            }
    	}else{ // query
    		iint vtx = queries[i];
    		iint maxdd = 0;
    		iint prev = vtx;
            if(vtx != croot) {
                for (iint v = cfa[vtx]; true; v = cfa[v]) {
                    if (active[v]) {
                        iint maxl = maxlen[v].first;
                        if (maxlen[v].second == prev) maxl = maxlen2[v].first;
                        // consider 0 case
                        iint dd = maxl + dist(vtx, v) - 1;
                        maxdd = max(maxdd, dd);
                    }
                    prev = v;
                    if (v == croot) break;
                }
            }else{
                maxdd = maxlen[croot].first-1;
            }
    		cout<<maxdd<<endl;
    	}
    }
}

/*

if we construct the centroid tree of the entire tree

And at each subtree we keep
the longest path length in the orig tree downward from that vertex

Notice that when vertices are added, centroid is added between the two sides
1. construct the entire tree
2. compute binary jumping distances
3. construct centroid tree
4. find remaining depth of nonempty vertices
4. each query take the max at each lca (and downwards)
5. each update change all its ancestors' data

*/