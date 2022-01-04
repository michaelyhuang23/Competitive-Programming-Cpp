#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl

int n,m;
const int N = 100005;
vector<unordered_set<int>> adjs;
vector<vector<int>> adj;
int maxLeaf[N];
bool visited[N];
bool connect[N];
int fa[N];
int cc;

int dfs_prep(int cur){
	if(!visited[cur]){
		visited[cur] = true;
		for(int son : adj[cur]){
			if(son <= cur) continue;
			maxLeaf[cur] = max(maxLeaf[cur], dfs_prep(son));
		}
	}
	return maxLeaf[cur];
}

void dfs_solve(int cur){
	if(adjs[cur].find(cur+1) == adjs[cur].end()) {
		if(!connect[cur+1]){
			cc++; // we might as well connect cur to cur+1, makes no diff which we connect to
			fa[cur+1] = cur;
		}else{
			for(int i=cur;i!=-1;i=fa[i]){
				if(adjs[i].find(cur+1) != adjs[i].end()){
					fa[cur+1] = i; // connect i to cur+1
					break;
				}
				if(maxLeaf[i]>=cur+1){
					cc++; // connect i to cur+1
					fa[cur+1] = i;
					break;
				}
			}
		}
	}else fa[cur+1] = cur;
	connect[cur+1] = true;
	for(int son : adj[cur]) connect[son] = true;
}

void solve(){
	cc = 0;
	cin >> n >> m;
	adj = vector<vector<int>>(n);
	adjs = vector<unordered_set<int>>(n);
	fill(visited, visited+n, 0);
	fill(connect, connect+n, 0);
	unordered_set<llong> edges;
	for(int i=0;i<m;i++){
		int a, b; cin >> a >> b; a--; b--;
		if(a==b) continue;
		if(a>b) swap(a,b);
		if(edges.find((llong)a*(n+1)+b) == edges.end()){
			adj[a].pb(b);
			adj[b].pb(a);
			adjs[a].insert(b);
			adjs[b].insert(a);
			edges.insert(a*(n+1)+b);
	    }
	}
	iota(maxLeaf, maxLeaf+n, 0);
	for(int i=0;i<n;i++)
		if(!visited[i]) dfs_prep(i);
	fill(fa, fa+n, -2);
	fa[0]=-1;
    connect[0] = true;
	for(int i=0;i<n-1;i++)
		dfs_solve(i);
	print(cc);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--) solve();
}
