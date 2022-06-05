#include<bits/stdc++.h>

using namespace std;

#define inf 1000
#define pb push_back
#define mp make_pair

int N;
vector<vector<int>> adj;
vector<int> weight, to, rev;
vector<bool> visited;

int dfs(int cur, vector<int>& edges){
	visited[cur] = true;
	if(cur == N-1) return inf;
	for(int ei : adj[cur]){
		if(visited[to[ei]] || weight[ei] == 0) continue;
		int ret = dfs(to[ei], edges);
		if(ret != 0) {
			edges.pb(ei);
			return min(weight[ei], ret);
		}
	}
	return 0;
}

void max_flow(){
	while(true){
		visited = vector<bool>(N, 0);
		vector<int> edges;
		int minw = dfs(0,edges);
		if(minw == 0) break;
		for(int ei : edges){
			weight[ei] -= minw;
			weight[rev[ei]] += minw;
		}
	}
}

void solve(){
	int n, m, k; cin >> n >> m >> k;
	N = n+m+2;
	adj = vector<vector<int>>(N);
	weight = vector<int>(N*N);
	to = vector<int>(N*N);
	rev = vector<int>(N*N);
	int ei = -1;
	for(int i=1;i<=n;i++){
		adj[0].pb(++ei);
		to[ei] = i;
		weight[ei] = 1;
		rev[ei] = ei+1;

		adj[i].pb(++ei);
		to[ei] = 0;
		weight[ei] = 0;
		rev[ei] = ei-1;
	}

	for(int i=n+1;i<=n+m;i++){
		adj[i].pb(++ei);
		to[ei] = N-1;
		weight[ei] = 1;
		rev[ei] = ei+1;

		adj[N-1].pb(++ei);
		to[ei] = i;
		weight[ei] = 0;
		rev[ei] = ei-1;
	}

	int cei = ei+1;
	
	for(int i=0;i<k;i++){
		int a, b; cin >> a >> b; b+=n;
		adj[a].pb(++ei);
		to[ei] = b;
		weight[ei] = 1;
		rev[ei] = ei+1;

		adj[b].pb(++ei);
		to[ei] = a;
		weight[ei] = 0;
		rev[ei] = ei-1;
	}

	int eei = ei;

	max_flow();

	int total = 0;
	for(int i : adj[N-1]) total += weight[i];
	cout<<total<<endl;

	for(int i = cei; i<=eei; i++) if(i&1) {
			if(weight[i] == 1){
				cout<<to[i] << " " << to[rev[i]]-n<<endl;
			}
		}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}
