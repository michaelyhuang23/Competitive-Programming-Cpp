#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 1000000007

int n, m;
vector<vector<int>> adj;
vector<vector<int>> bin;
vector<int> depth;
vector<int> fa;

vector<vector<int>> memory;

void dfs_tree(int cur, int pa){
	if(cur==pa) depth[cur] = 0;
	else depth[cur] = depth[pa]+1;
	fa[cur] = pa;
	for(int son : adj[cur]){
		if(son == pa) continue;
		dfs_tree(son, cur);
	}
}

int find_lca(int a, int b, vector<vector<int> >& ancs, vector<int>& dep){
    if(dep[b]<dep[a]){ int tmp=b; b=a; a=tmp; }
    assert(dep[b]>=dep[a]);
    int diff = dep[b] - dep[a];
    for(int i=0; i<20; i++) if((diff>>i) & 1) b = ancs[i][b];
    // level to the same
    assert(dep[b]==dep[a]);
    if(a==b) return a;
    for(int i=19; i>=0; i--) if(ancs[i][b] !=  ancs[i][a]) {
        a = ancs[i][a];
        b = ancs[i][b];
    }
    a = ancs[0][a];
    b = ancs[0][b];
    assert(a==b);
    return a;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	adj = vector<vector<int>>(n);
	for(int i=0;i<n-1;i++) {
		int a, b; cin >> a >> b;
		a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
    
	depth = vector<int>(n,0);
	fa = vector<int>(n,0);
	dfs_tree(0,0);

	bin = vector<vector<int>>(20,vector<int>(n));
	bin[0] = fa;
	for(int i=1;i<20;i++)
		for(int j=0;j<n;j++) 
			bin[i][j]=bin[i-1][bin[i-1][j]];

	memory = vector<vector<int>>(m, vector<int>(n,0));
	int last = 0;
	int total = 0;
	int pc = 0;

	for(int ii=0;ii<m;ii++){
		string type; cin >> type;
		if(type == "change"){
			total++;
			memory[total] = memory[pc];
			int u,v,a,b; cin >> u >> v >> a >> b;
			u = ((u+last)%n) + 1; 
			v = ((v+last)%n) + 1;
			u--; v--;
			int lca = find_lca(u,v,bin,depth);
			int i=0;
			for(int ui = u; ui != lca; ui = fa[ui]){
				memory[total][ui] = memory[pc][ui] + a+i*b;
				i++;
			}
			memory[total][lca] = memory[pc][lca] + a+i*b;
			int len = depth[v] - depth[lca];
			i += len;
			for(int vi = v; vi != lca; vi = fa[vi]){
				memory[total][vi] = memory[pc][vi] + a+i*b;
				i--;
			}
			pc = total;
			//deb(memory[pc])
		}
		if(type == "query"){
			//deb(pc)
			//deb(memory[pc])
			int u, v; cin >> u >> v;
			u = ((u+last)%n) + 1; 
			v = ((v+last)%n) + 1;
			u--; v--;
			int lca = find_lca(u,v,bin,depth);
			int i=0;
			int ans = 0;
			for(int ui = u; ui != lca; ui = fa[ui]){
				ans += memory[pc][ui];
			}
			ans += memory[pc][lca];
			for(int vi = v; vi != lca; vi = fa[vi]){
				ans += memory[pc][vi];
			}
			last = ans;
			print(last);
		}
		if(type == "roll"){
			int w; cin >> w;
			w = (w+last)%(total+1);
			pc = w;
		}
	}
}




















