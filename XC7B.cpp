#include<iostream>
#include<assert.h>
#include<vector>
#include<algorithm>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple

int n;
vector<llong> weights;
vector<vector<int>> adj;
vector<pair<int,int>> depth;

int find_depth(int cur, int par){
	int d = 0;
	for(int son : adj[cur]){
		if(son == par) continue;
		d = max(d,find_depth(son, cur));
	}
	depth[cur] = d+1;
	return depth[cur];
}

void find_dia(int cur, int par){
	for(int son : adj[cur]){
		if(son == par) continue;
		find_dia(son, cur);
	}
}

void solve(){
	cin >> n; n++;
	weights = vector<llong>(n-1);
	for(int i=0;i<n-1;i++){
		cin >> weights[i];
	}
	adj = vector<vector<int>>(n);
	for(int i=0;i<n-1;i++){
		int u, v; cin >> u >> v;
		u--; v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--){
		solve();
	}
}


/*

first find the diameter of tree using a dfs

Then, use a 3D interval DP on the diameter.

*/