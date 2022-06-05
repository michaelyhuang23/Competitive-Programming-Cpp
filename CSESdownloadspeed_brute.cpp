#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define inf 10000000000000LL


// reemember to convert to llong
llong n, m;
vector<vector<llong>> adj;
vector<llong> to, weight, rev;
vector<bool> visited;

llong dfs(llong cur, llong par, vector<llong>& edges){
	if(cur == n-1) return inf;
	visited[cur] = true;
	for(llong ei : adj[cur]){
		if(to[ei] == par || visited[to[ei]] || weight[ei]==0){ continue;}
		llong ret = dfs(to[ei], cur, edges);
		if(ret == 0) continue;
		else{
			edges.pb(ei);
			return min(weight[ei], ret);
		}
	
	}
	return 0;		
}


void max_flow(){
	while(true){
		vector<llong> edges;
		visited = vector<bool>(n, false);
		llong minw = dfs(0,0, edges);
		
		if(minw == 0) break;
		for(llong ei : edges){
			weight[ei] -= minw;
			weight[rev[ei]] += minw;
		}

	}
	
}

void solve(){
	cin>>n>>m;
	adj = vector<vector<llong>>(n);
	to = vector<llong>(2*m);
	weight = vector<llong>(2*m);
	rev = vector<llong>(2*m);
	
	for(llong i=0;i<m;i++){
		llong a, b, c; cin >> a >> b >> c; a--; b--;
		adj[a].pb(i*2);
		to[i*2] = b;
		weight[i*2] = c;
		rev[i*2] = i*2+1;

		adj[b].pb(i*2+1);
		to[i*2+1] = a;
		weight[i*2+1] = 0;
		rev[i*2+1] = i*2;
	}
	max_flow();

	llong tflow = 0;
	for(llong ei : adj[n-1]){
		if(ei & 1) tflow += weight[ei]; // only add if it's a reverse edge
	}

	cout<<tflow<<endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}
