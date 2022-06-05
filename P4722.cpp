#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define inf 1000000000000000LL

llong n, m, s, t;
vector<vector<llong>> adj;
vector<llong> to, weight, rev;
vector<llong> level;
vector<llong> curp;


llong dfs(llong cur, llong minw){
	if(cur == t) return minw;
	for(int i=curp[cur]; i<adj[cur].size(); i++){
		curp[cur] = i;
		int ei = adj[cur][i];
		if(weight[ei] == 0 || level[cur]+1!=level[to[ei]]) continue;
		llong ret = dfs(to[ei], min(weight[ei], minw));
		if(ret!=0) {
			weight[ei] -= ret;
			weight[rev[ei]] += ret;
			return ret;
		}
	}
	return 0;
}

bool bfs(llong st){
	level = vector<llong>(n, inf); level[st] = 0;
	queue<llong> pq; pq.push(st);
	while(!pq.empty()){
		llong cur = pq.front(); pq.pop();
		for(llong ei : adj[cur]){
			if(level[to[ei]] != inf || weight[ei] == 0) continue;
			level[to[ei]] = level[cur]+1;
			pq.push(to[ei]);
		}
	}
	return level[t] < inf;
}

void max_flow(){
	level = vector<llong>(n, inf);
	while(bfs(s)){
		llong minw = 0;
		curp = vector<llong>(n, 0);
		do{
			minw = dfs(s, inf);
		}while(minw != 0);
	}
}

void solve(){
	cin >> n >> m >> s >> t; s--; t--;
	adj = vector<vector<llong>>(n);
	to = vector<llong>(m*2);
	weight = vector<llong>(m*2);
	rev = vector<llong>(m*2);

	llong ei = -1;
	
	auto add_edge =
		[&](llong a, llong b, llong c)
		{
			if(a == b) return;
			adj[a].pb(++ei);
			to[ei] = b;
			weight[ei] = c;
			rev[ei] = ei+1;

			adj[b].pb(++ei);
			to[ei] = a;
			weight[ei] = 0;
			rev[ei] = ei-1;
		};


	for(llong i=0;i<m;i++){
		llong a, b, c; cin >> a >> b >> c; a--; b--;
		add_edge(a, b, c);
	}

	max_flow();
	llong total = 0;
	for(llong ei : adj[t]) if(ei&1) total += weight[ei];
	cout<<total<<endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}
