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

void merge(set<tuple<iint, iint, iint> >& a, set<tuple<iint,iint,iint> >& b){
    if(a.size()>b.size()){
        for(tuple<iint, iint, iint> ret : b){
            if(a.find(ret) != a.end()){ a.erase(ret); continue; }
            a.insert(ret);
        }
    }else{
        for(tuple<iint, iint, iint> ret : a){
            if(b.find(ret) != b.end()){ b.erase(ret); continue; }
            b.insert(ret);
        }
        a = std::move(b);
    }
}

set<tuple<iint,iint,iint> > search(iint cur, iint fa, vector<iint>& depth, vector<vector<iint> >& adj, vector<vector<tuple<iint, iint, iint> > >& adj2, vector<iint>& ans){
    set<tuple<iint,iint,iint> > orig;
    depth[cur] = depth[fa]+1;
    if(cur==fa) depth[cur]=0;
    for(iint son : adj[cur]){
        if(son == fa) continue;
        set<tuple<iint,iint,iint> > ret = search(son, cur, depth, adj, adj2, ans);
        merge(orig, ret);
    }
    set<tuple<iint,iint,iint> > temp;
    for(tuple<iint,iint,iint> ret : adj2[cur]) temp.insert(ret);
    merge(orig, temp);
    if(orig.size()==0) ans[cur]=-1;
    else ans[cur] = std::get<0>(*orig.begin());
    return orig;
}


int main() {
    ifstream fin("disrupt.in");
    ofstream fout("disrupt.out");
    ios_base::sync_with_stdio(0);
    fin.tie(0);
    iint N, M;
    fin >> N >> M;
    vector<vector<iint> > adj(N);
    vector<pair<iint, iint> > edgeList(N-1);
    For(i, N-1) {
    	iint a, b; fin >> a >> b;
    	a--; b--;
    	adj[a].pb(b);
    	adj[b].pb(a);
        edgeList[i] = make_pair(a,b);
    }
    vector<vector<tuple<iint, iint, iint> > > adj2(N);
    For(i, M){
    	iint a, b, c; fin >> a >> b >> c;
    	a--; b--;
    	adj2[a].pb(make_tuple(c, a, b));
    	adj2[b].pb(make_tuple(c, a, b));
    }

    vector<iint> ans(N);
    vector<iint> depth(N);

    search(0,0,depth,adj,adj2,ans);
    For(i,N-1){
        iint a = edgeList[i].first;
        iint b = edgeList[i].second;
        if(depth[a] > depth[b]) fout<<ans[a]<<endl;
        else fout<<ans[b]<<endl;
    }
    fout.close();
}


/*

Root the tree anywhere. Now, for each leaf, store all its 
paths to other nodes.

When we merge two subtrees, we merge all their paths, sorted by length
Paths between them are filtered when we merge the small to the large 
(remove from the large, just doubling the work, no complexity change)

Paths to the parent nodes are also removed obviously. 

*/




