#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define infl 10000000000000000LL
#define inf 1000000000LL

llong n,N;
vector<vector<llong>> adj;
vector<llong> to, weight, rev;
vector<bool> visited;

llong dfs(llong cur, llong limit, vector<llong>& edges){
	visited[cur] = true;
	if(cur == N-1) return infl;
	for(llong ei : adj[cur]){
		if(visited[to[ei]] || weight[ei]<limit) continue;
		llong ret = dfs(to[ei], limit, edges);
		if(ret != 0) {
			edges.pb(ei);
			return min(weight[ei], ret);
		}
	}
	return 0;
}

void max_flow(){
	llong limit = infl;
	while(limit > 0){
		limit *= 2;
		vector<llong> edges;
		llong minw = 0;
		do{
			limit /= 2;
			visited = vector<bool>(N,0);
			minw = dfs(0, limit, edges);
//			cout<<minw<<" "<<limit<<endl;
		}while(minw == 0 && limit > 0);
		if(limit == 0) break;
//		cout<<minw<<endl;
		for(llong ei : edges){
			assert(weight[ei] >= minw);
			weight[ei] -= minw;
			weight[rev[ei]] += minw;
		}
	}
}


void solve(){
	cin >> n;
	vector<vector<llong>> map(n, vector<llong>(n, inf));
	vector<vector<llong>> cmap(n, vector<llong>(n, 0));
	for(llong r=0;r<n;r++) for(llong c=0;c<n;c++) {
			string x; cin >> x; if(x==".") continue;
			map[r][c] = stoll(x);
			cmap[r][c] = map[r][c];
		}


	llong sum = (n+1)*n/2;
	vector<llong> sumr(n, sum), sumc(n, sum);
	for(llong r=0;r<n;r++)
		for(llong c=0;c<n;c++) {
			if(map[r][c] < inf/2){
				sumr[r] -= map[r][c];
				sumc[c] -= map[r][c];
				map[r][c] = 0;
			}
		}

//	for(int r=0;r<n;r++) cout<<sumr[r]<<endl;
	
	// 0: source, N-1: sink, 1--n: rows, n+1--2n: cols
	N = 2*n+2;
	adj = vector<vector<llong>>(N);
	to = vector<llong>(N*N);
	weight = vector<llong>(N*N);
	rev = vector<llong>(N*N);
	llong ei = -1;
	for(llong i=1;i<=n;i++) {
		adj[0].pb(++ei);
		to[ei] = i;
		weight[ei] = sumr[i-1];
		rev[ei] = ei+1;

		adj[i].pb(++ei);
		to[ei] = 0;
		weight[ei] = 0;
		rev[ei] = ei-1;
	}

	for(llong i=n+1;i<=2*n;i++) {
		llong t = 2*n+1;
		adj[i].pb(++ei);
		to[ei] = t;
		weight[ei] = sumc[i-n-1];
		rev[ei] = ei+1;

		adj[t].pb(++ei);
		to[ei] = i;
		weight[ei] = 0;
		rev[ei] = ei-1;
	}
	int cei = ei+1;
	for(llong r=1;r<=n;r++){
		for(llong c=n+1;c<=2*n;c++){
			llong rr = r-1; llong cc = c-n-1;
			adj[r].pb(++ei);
			to[ei] = c;
			weight[ei] = map[rr][cc];
			rev[ei] = ei+1;

			adj[c].pb(++ei);
			to[ei] = r;
			weight[ei] = 0;
			rev[ei] = ei-1;
		}
	}


	int eei = ei;

//	for(int i=0;i<=eei;i++) cout<<weight[i]<<endl;

	max_flow();

	for(int ei=0;ei<cei;ei++) if(!(ei&1)) {
//			cout<<weight[ei]<<" "<<weight[rev[ei]]<<endl;
			assert(weight[ei]==0);
		}

	for(int ei = cei; ei<=eei; ei++){
		if(ei & 1) {
			int r = to[ei]-1;
			int c = to[rev[ei]]-n-1;
			cmap[r][c] += weight[ei];
		}
	}

//	for(int i=0;i<=eei;i++) cout<<weight[i]<<endl;

	for(int r=0;r<n;r++){
		for(int c=0;c<n-1;c++) cout<<cmap[r][c]<<" ";
		cout<<cmap[r][n-1]<<endl;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}
