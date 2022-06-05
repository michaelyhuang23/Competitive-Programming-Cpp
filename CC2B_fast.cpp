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
vector<llong> level, curp;

bool bfs(llong st){
	level = vector<llong>(N,inf); level[st] = 0;
	queue<llong> pq; pq.push(st);
	while(!pq.empty()){
		llong cur = pq.front(); pq.pop();
		for(int ei : adj[cur]){
			if(level[to[ei]] != inf || weight[ei] == 0) continue;
			level[to[ei]] = level[cur] + 1;
			pq.push(to[ei]);
		}
	}

	return level[N-1] < inf;
}

llong dfs(llong cur, llong minw){
	if(cur == N-1) return minw;
	for(int i=curp[cur];i<adj[cur].size();i++){
		curp[cur] = i;
		llong ei = adj[cur][i];
		if(level[to[ei]] != level[cur]+1 || weight[ei]==0) continue;
		llong ret = dfs(to[ei], min(minw, weight[ei]));
		if(ret != 0) {
			assert(ret <= weight[ei]);
			weight[ei] -= ret;
			weight[rev[ei]] += ret;
			return ret;
		}
	}
	return 0;
}

void max_flow(){
	while(bfs(0)){
		curp = vector<llong>(N,0);
		while(dfs(0,inf));
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
