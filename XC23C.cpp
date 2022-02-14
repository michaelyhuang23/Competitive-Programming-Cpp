#include<bits/stdc++.h>


using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define MOD 1000000007LL
#define inf 10000000
#define inff 10000000000000000LL
#define print(x) cout<<x<<endl



vector<vector<pair<int,int>>> adj;
vector<vector<int>> mat;
vector<int> dist0;
vector<vector<int>> fa0;
vector<int> taxes;
int n, m;

llong minCost;


pair<vector<int>, vector<vector<int>>> special_bfs(int source){
	vector<int> dist(n, inf);
	vector<vector<int>> fa(n);
	vector<bool> visited(n, false);
	queue<int> pq;
	pq.push(source);
	dist[source] = 0;

	while(!pq.empty()){
		int id = pq.front(); pq.pop();
		if(visited[id]) continue;
		visited[id]=true;
		for(auto& edge : adj[id]){
			int to = edge.first;
			if(dist[id]+1 < dist[to]){
				dist[to] = dist[id]+1;
				fa[to] = {id};
				pq.push(to);
			}else if(dist[id]+1 == dist[to]){
				fa[to].pb(id);
			}

		}
	}

	return mp(dist, fa);
}


void dfs(int cur, vector<int>& compOcc, llong cost){
	if(fa0[cur].empty()){
		minCost = min(minCost, cost);
		return;
	}
	for(int fath : fa0[cur]){
		int c = mat[cur][fath];
		compOcc[c]++;
		dfs(fath, compOcc, cost + taxes[c]*compOcc[c]);
		compOcc[c]--;
	}
}

void solve(){
	cin >> n >> m;
	taxes = vector<int>(m);
	for(int i=0;i<m;i++) cin >> taxes[i];
	adj = vector<vector<pair<int,int>>>(n);
	mat = vector<vector<int>>(n, vector<int>(n,0));
	for(int i=0;i<m;i++){
		int a,b,c; cin >> a >> b >> c;
		a--; b--; c--;
		adj[a].pb(mp(b,c));
		adj[b].pb(mp(a,c));
		mat[a][b] = c;
		mat[b][a] = c;
	}

	auto ret = special_bfs(0);
	dist0 = ret.first;
	fa0 = ret.second;

	for(int k=1;k<n;k++){
		minCost = inff;
		vector<int> compOcc(m,0);
		dfs(k, compOcc, 0);
		print(minCost);
	}
}




int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}