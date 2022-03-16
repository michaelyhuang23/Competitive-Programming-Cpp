// #include "debughelp.hpp"

#include<bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl

#define DEPTH 30

int n, m;
vector<vector<int>> adj;
vector<int> subtreesize;
vector<bool> masks;
vector<int> dist2par;
vector<int> parent;
vector<int> reddist;
vector<int> depth;
vector<vector<int>> dist2ancestor;
int cc = 0;
void get_size(int cur, int par){
	//subtreesize[cur] = 0;
	for(int son : adj[cur]){
		if(son == par || masks[son]) continue;
		get_size(son, cur);
		subtreesize[cur] += subtreesize[son];
	}
	subtreesize[cur]++;
	cc += 100000000;
	assert(subtreesize[cur]<=inf);
}

int find_centroid(int cur, int par, int size){
	for(int son : adj[cur]){
		if(son == par || masks[son]) continue;
		if(subtreesize[son]*2>size) return find_centroid(son, cur, size);
	}
	return cur;
}

void compute_dist(int st, int h){
	queue<tuple<int,int,int>> pq;
	pq.push(mt(st, 0, st));
	while(!pq.empty()){
		auto ret = pq.front(); pq.pop();
		int c = get<0>(ret);
		int d = get<1>(ret);
		int fa = get<2>(ret);
		dist2ancestor[c][h] = d;
		for(int son : adj[c]){
			if(son == fa || masks[son]) continue;
			pq.push(mt(son, d+1, c));
		}
	}
}

void build_centroid_tree(int cur, int par){
	if(masks[cur]) return;

	get_size(cur, par);
	int c = find_centroid(cur, par, subtreesize[cur]);

	if(par == cur && cur == 0){
		parent[c] = c;
		depth[c] = 0;
	}else{
		parent[c] = par;
		depth[c] = depth[par]+1;
	}

	compute_dist(c, depth[c]);

	masks[c] = true;

	for(int son : adj[c])
		build_centroid_tree(son, c);
}


void solve(){
	cin >> n >> m;
	adj = vector<vector<int>>(n);
	for(int i=0;i<n-1;i++){
		int a, b; cin >> a >> b;
		a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	subtreesize = vector<int>(n,0);
	masks = vector<bool>(n,0);
	dist2par = vector<int>(n,0);
	parent = vector<int>(n,0);
	iota(parent.begin(), parent.end(), 0);

	depth = vector<int>(n,0);

	dist2ancestor = vector<vector<int>>(n, vector<int>(DEPTH, 0));

	build_centroid_tree(0,0);


	reddist = vector<int>(n, inf);

	int ci = 0;
	for(int h=depth[ci];h>=0;h--){
		reddist[ci] = min(reddist[ci], dist2ancestor[0][h]);
		ci = parent[ci];
	}
	// init node 1 or 0
	// deb(parent)
	// deb(dist2par)

	// you don't need to go through a parent to go to an ancestor


	for(int i=0;i<m;i++){
		int type, v; cin >> type >> v; v--;
		if(type == 1){ //update
			int ci = v;
			for(int h=depth[v];h>=0;h--){
				reddist[ci] = min(reddist[ci], dist2ancestor[v][h]);
				ci = parent[ci];
			}
		}else{ //query
			// deb(reddist)
			int minD = inf;
			int ci = v;
			for(int h=depth[v];h>=0;h--){
				minD = min(minD, reddist[ci] + dist2ancestor[v][h]);
				ci = parent[ci];
			}

			print(minD);
		}
	}

}




int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}