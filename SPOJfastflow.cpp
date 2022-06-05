#include<bits/stdc++.h>

int n, m;
vector<vector<int>> adj;
vector<int> to, weight, rev;
vector<int> level;

void max_flow(){
	level = vector<int>(n, inf);
	while(bfs(0)){
		int minw = 0;
		while(
	}
}

void solve(){
	cin >> n >> m;
	adj = vector<vector<int>>(n);
	to = vector<int>(m*2);
	weight = vector<int>(m*2);
	rev = vector<int>(m*2);

	int ei = -1;
	
	auto add_edge = [&](int a, int b, int c){
		adj[a].pb(++ei);
		to[ei] = b;
		weight[ei] = c;
		rev[ei] = ei+1;

		adj[b].pb(++ei);
		to[ei] = a;
		weight[ei] = 0;
		rev[ei] = ei-1;
	};


	for(int i=0;i<m;i++){
		int a, b, c; cin >> a >> b >> c; a--; b--;
		add_edge(a, b, c);
	}

	max_flow();
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}
