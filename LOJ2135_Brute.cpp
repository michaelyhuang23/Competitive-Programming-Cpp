#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl


int n;
vector<vector<pair<int,int>>> adj;
vector<int> weights, depth;


void dfs_process(llong cur, llong par){
	if(cur==par) depth[cur]=0;
	for(auto& edge : adj[cur]){
		llong son = edge.first;
		if(son == par) continue;
		depth[son]=depth[cur]+edge.second;
		dfs_process(son, cur);
	}
}


void solve(){
	int q; cin >> n >> q;
	adj = vector<vector<pair<int,int>>>(n);
	weights = vector<int>(n,0);
	depth = vector<int>(n,0);
	for(int i=0;i<n-1;i++){
		int a, b, c; cin >> a >> b >> c; a--; b--;
		adj[a].pb(mp(b,c));
		adj[b].pb(mp(a,c));
	}
	dfs_process(0,0);
	int rcost = 0;
	for(int i=0;i<q;i++){
		int u, e; cin >> u >> e; u--;
		weights[u]+=e;
		int ans = inf;
		for(int v=0;v<n;v++){
			depth = vector<int>(n,0);
			dfs_process(v,v);
			int cost = 0;
			for(int j=0;j<n;j++) cost+=depth[j]*weights[j];
			ans = min(ans, cost);
		}
		print(ans);
	}
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}