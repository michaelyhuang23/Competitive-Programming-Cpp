
#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl

llong n, m;
const llong max_depth = 25;
const llong d = 60;
vector<vector<llong>> adj;
vector<llong> subtreesize;
vector<llong> depth;
vector<llong> parent;
vector<bool> mask;
vector<vector<vector<llong>>> basis2ancestor;
vector<llong> arr;

void insert_vector(vector<llong>& basis, llong x){
	for(llong i=d-1;i>=0;i--){
		if(!(x&(1LL<<i))) continue;
		if(!basis[i]){
			basis[i] = x;
			break;
		}
		x ^= basis[i]; // maintains reversed echelon form
	}
}

void compute_size(llong cur, llong par){
	subtreesize[cur] = 0;
	for(llong son : adj[cur]){
		if(par == son || mask[son]) continue;
		compute_size(son, cur);
		subtreesize[cur] += subtreesize[son];
	}
	subtreesize[cur]++;
}

llong find_centroid(llong cur, llong par, llong n){
	for(llong son : adj[cur]){
		if(par == son || mask[son]) continue;
		if(subtreesize[son]*2 > n) return find_centroid(son, cur, n);
	}
	return cur;
}

void compute_basis(llong cur, llong par, llong h){
	basis2ancestor[cur][h] = basis2ancestor[par][h];
	insert_vector(basis2ancestor[cur][h], arr[cur]);
	for(llong son : adj[cur]){
		if(par == son || mask[son]) continue;
		compute_basis(son, cur, h);
	}
}

void build_centroid_tree(llong cur, llong par){
	compute_size(cur, par);
	llong c = find_centroid(cur, par, subtreesize[cur]);

	if(cur == par){
		parent[c] = c;
		depth[c] = 0;
	}else{
		parent[c] = par;
		depth[c] = depth[par] + 1;
	}

	compute_basis(c, c, depth[c]);

	mask[c] = true;

	for(llong son : adj[c]) if(!mask[son]) build_centroid_tree(son, c);
}


void solve(){
	cin >> n >> m;
	adj = vector<vector<llong>>(n);
	arr = vector<llong>(n);

	for(llong i=0;i<n;i++) cin >> arr[i];

	for(llong i=0;i<n-1;i++){
		llong a, b; cin >> a >> b; a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	subtreesize = vector<llong>(n, -1);
	depth = vector<llong>(n, 0);
	parent = vector<llong>(n, -1);
	mask = vector<bool>(n, 0);
	basis2ancestor = vector<vector<vector<llong>>>(n, vector<vector<llong>>(max_depth, vector<llong>(d, 0)));
	build_centroid_tree(0,0);


	auto get_lca = [&](llong u, llong v){
		if(depth[u]<depth[v]) swap(u, v);
		while(depth[u]>depth[v]) u = parent[u];
		while(u != v){
			u = parent[u];
			v = parent[v];
		}
		return u;
	};

	for(llong i=0;i<m;i++){
		llong u, v; cin >> u >> v;
		u--; v--;

		llong lca = get_lca(u, v);
		// deb(mp(u,v))
		llong hlca = depth[lca];
		// deb(mp(lca, hlca))

		vector<llong> leftBasis = basis2ancestor[u][hlca];
		vector<llong> rightBasis = basis2ancestor[v][hlca];

		// deb(leftBasis)
		// deb(rightBasis)

		for(llong i=0;i<d;i++){
			if(!rightBasis[i]) continue;
			insert_vector(leftBasis, rightBasis[i]);
		}

		// deb(leftBasis)

		llong mask = 0;
		for(llong i=d-1;i>=0;i--){
			if(!leftBasis[i]) continue;
			if(mask & (1LL<<i)) continue;
			mask ^= leftBasis[i]; // have to take to maintain highest bit on
		}

		print(mask);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}