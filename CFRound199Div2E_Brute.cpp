#include<bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl

#define DEPTH 30


int n, m; 
vector<vector<int>> adj;
vector<bool> red;

int bfs_dist(int st){
	queue<int> pq;
	pq.push(st);
	vector<int> dist(n,inf);
	dist[st]=0;
	while(!pq.empty()){
		int c = pq.front(); pq.pop();
		for(int son : adj[c]){
			if(dist[son] < inf/2) continue;
			dist[son] = dist[c] + 1;
			pq.push(son);
		}
	}

	int minD = inf;
	for(int i=0;i<n;i++){
		if(red[i]) minD = min(minD, dist[i]);
	}

	return minD;
}

void solve(){
	cin >> n >> m;
	adj = vector<vector<int>>(n);
	for(int i=0;i<n-1;i++){
		int a, b; cin >> a >> b; a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	red = vector<bool>(n,0);
	red[0] = 1;

	for(int i=0;i<m;i++){
		int type, v; cin >> type >> v; v--;
		if(type == 1){ //update
			red[v] = 1;
		}else{ //query
			int minD = bfs_dist(v);
			print(minD);
		}
	}

}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}