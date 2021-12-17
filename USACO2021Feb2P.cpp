#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
#include <vector>
#include <set>
#include <queue>

#include "debughelp.hpp"

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple


int n, m;
vector<vector<int> > badj;
bool hasSelf = false;

/*
first try Kruskal MST, realized MST doesn't guarantee min distance
then try Prim modification, realized it doesn't guarantee MST
then try BST get subgraph --> reduce to DAG --> use Kruskal modification on it, realized the problem is not building MST on bi-graph, but which MST transfer best to old graph
now try greedy edge sort --> self edge is last, each vtx ideally links one --  graph matching
give up
*/

set<pair<int,int> > build_mst(){
	vector<int> fr;
	fr.pb(0);
	vector<int> vs(2*n,-1);
	vs[0] = 0;
	if(hasSelf && n>=2) {
		fr.pb(n);
		vs[n] = 1;
	}else{
		vs[n] = 1;
	}
	vector<pair<int, int> > edges;
	while(!fr.empty()){
		vector<int> dest;
		for(int cur : fr){
			for(int child : badj[cur]) if(vs[child] == -1) 
		}
		int cur = pq.front(); pq.pop();
		for(int child : badj[cur]){
			if(vs[child] < vs[cur]+1) continue;
			vs[child] = vs[cur]+1;
			pq.push(child);
			edges.pb(mp(cur, child));
		}
	}
	return ue;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--){
		cin >> n >> m;
		badj = vector<vector<int> >(2*n);
		for(int i=0;i<2*n;i++) badj[i] = vector<int>();
		hasSelf = false;
		vector<int> selfL;
		for(int i=0; i<m; i++){
			int a, b; cin >> a >> b;
			a --; b --;
			if(a == b) {
				if(a==0) hasSelf = true;
				selfL.pb(a);
				continue;
			}
			badj[a].pb(b+n);
			badj[b+n].pb(a);
			badj[a+n].pb(b);
			badj[b].pb(a+n);
		}
		for(int a : selfL){
			badj[a].pb(a+n);
			badj[a+n].pb(a);
		}
		deb(badj);
		set<pair<int,int> > mst = build_mst();
		deb(mst);
		cout<<mst.size()<<endl;
	}
}
