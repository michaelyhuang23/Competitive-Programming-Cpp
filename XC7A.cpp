#include<iostream>
#include<assert.h>
#include<vector>
#include<algorithm>
#include<unordered_set>


using namespace std;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl


vector<vector<tuple<int,int,int>>> adj;
vector<bool> svtx;
vector<int> estate; // 0: not traversed; 1: ok; -1: fail
vector<bool> fail;
int sv = 0;

int dfs(int cur, int par){
	fail[cur] = true;
	if(svtx[cur]){
		int total = 1;
		for(auto& edge : adj[cur]){
			if(get<0>(edge) == par) {
				if(get<1>(edge) != 1) return -1;
				continue;
			}
			if(estate[get<2>(edge)] == 0)
				estate[get<2>(edge)] = dfs(get<0>(edge), cur);
			if(estate[get<2>(edge)]==-1) {total = -1; break;}
		}
		return total;
	}else{
		int total = 1;
		for(auto& edge : adj[cur]){
			if(get<0>(edge) == par) continue;
			if(estate[get<2>(edge)] == 0)
				estate[get<2>(edge)] = dfs(get<0>(edge), cur);
			if(estate[get<2>(edge)]==-1) {total = -1; break;}
		}
		return total;
	}
}


void solve(){
	int n; cin >> n;
	sv = 0;
	svtx = vector<bool>(n,0);
	estate = vector<int>(2*n,0);
	fail = vector<bool>(n,0);
	adj = vector<vector<tuple<int,int,int>>>(n);
	for(int i=0;i<n-1;i++){
		int a, b; char c; cin >> a >> b >> c;
		a--; b--;
		adj[a].pb(mt(b,c-'a',i));
		adj[b].pb(mt(a,c-'a',i+n-1));
	}
	bool suc = true;
	for(int i=0;i<n;i++){
		vector<int> counter(26,0);
		for(auto& edge : adj[i]) counter[get<1>(edge)]++;
		int pairs = 0;
		for(int c : counter) pairs+=max(0,c-1);
		if(pairs>1) suc = false;
		if(pairs == 1){
			for(auto& edge : adj[i]){
				if(counter[get<1>(edge)] == 2) get<1>(edge) = 1;
				else get<1>(edge) = 0;
			}
			sv++;
			svtx[i]=true;
		}
	}
	if(!suc){print(0); return;}
	for(int i=0;i<n;i++){
		if(svtx[i]){
			for(auto& edge : adj[i]){
				if(estate[get<2>(edge)] == 0 && get<1>(edge)==0){
					estate[get<2>(edge)] = dfs(get<0>(edge),i);
					if(estate[get<2>(edge)] == -1) suc=false;
				}
			}
		}
	}
	if(!suc){print(0); return;}
	int cc = 0;
	for(int i=0;i<n;i++){
		if(svtx[i] || fail[i]) continue;
		cc++;
	}
	print(cc);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;

	while(tt--){
		solve();
	}
}






/*

if all edges out of all vertices are different, then it's a valid trie
no matter where we root it. 

A vertex can only be a valid subroot if non of its children edges are equal

A trie is valid if all of its subroots are valid.

So given a vertex with 3 edges equal, it's a fail no matter how we root it.

Given a set of vertices with 2 edges equal. it only works, if we root the tree
such that one of these two edge is a parent edge. 

Now say we find one such vertex, root the tree there
Then all other such vertices must be in the two subtrees that have equal edge
In fact, they must be in the same subtree. 

*/