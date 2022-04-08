#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl

const llong HEIGHT = 25;
llong N,M;
vector<vector<llong>> adj;
vector<llong> subtreesize,parent,depth;
vector<vector<llong>> dist2ancestor;
vector<bool> mask;


vector<llong> valE,valO,countE,countO,val2parE,val2parO, count2parE, count2parO;

void compute_size(llong cur, llong par){
	subtreesize[cur] = 1;
	for(llong son : adj[cur]){
		if(son == par) continue;
		compute_size(son, cur);
		subtreesize[cur] += subtreesize[son];
	}
}


llong find_centroid(llong cur, llong par, llong n){
	for(llong son : adj[cur]){
		if(par == son || mask[son]) continue;
		if(subtreesize[son]*2 > n) return find_centroid(son, cur, n);
	}
	return cur;
}

void compute_dist(llong cur, llong par, llong h, llong d=0){
	for(llong son : adj[cur]){
		if(son == par || mask[son]) continue;
		compute_dist(son, cur, h, d+1);
	}
	dist2ancestor[cur][h] = d;
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

	assert(depth[c] < HEIGHT);

	compute_dist(c,c,depth[c]);

	mask[c] = true;

	for(llong son : adj[c]) if(!mask[son]) build_centroid_tree(son, c);
}



void update(llong cur, llong orig, llong x){
	llong d = dist2ancestor[orig][depth[cur]];


	if(d % 2 == 0){
		countE[cur] += x;
		valE[cur] += d*x;
	}else{
		countO[cur] += x;
		valO[cur] += d*x;
	}

	if(parent[cur] == cur) return;

	llong pd = dist2ancestor[orig][depth[parent[cur]]];

	if(pd % 2 == 0){
		val2parE[cur] += pd*x;
		count2parE[cur] += x;
	}else{
		val2parO[cur] += pd*x;
		count2parO[cur] += x;
	}

	update(parent[cur],orig,x);
}

llong query(llong cur, llong orig){
	if(parent[cur] == cur) return 0;

	llong dp = dist2ancestor[orig][depth[parent[cur]]];
	llong sum = 0;


	int d = 0;
	d = dist2ancestor[orig][depth[cur]];

	if(dp % 2 == 0){ // the other is even
		sum += valE[parent[cur]]-val2parE[cur] + dp*(countE[parent[cur]]-count2parE[cur]);
	}else{ // the other is odd
		// deb(valO[parent[cur]])
		// deb(val2parO[cur])
		sum += valO[parent[cur]]-val2parO[cur] + dp*(countO[parent[cur]]-count2parO[cur]);
	}

	return sum + query(parent[cur], orig);
}

void solve(){
	cin >> N >> M;
	adj = vector<vector<llong>>(N);
	dist2ancestor = vector<vector<llong>>(N, vector<llong>(HEIGHT,0));
	mask = vector<bool>(N,false);
	parent = vector<llong>(N,0);
	depth = vector<llong>(N,0);
	subtreesize = vector<llong>(N,0);

	for(llong i=0;i<N-1;i++){
		llong a,b; cin >> a >> b; a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	build_centroid_tree(0,0);

	valE = vector<llong>(N,0);
	valO = vector<llong>(N,0);
	countE = vector<llong>(N,0);
	countO = vector<llong>(N,0);
	val2parE = vector<llong>(N,0);
	val2parO = vector<llong>(N,0);
	count2parE = vector<llong>(N,0);
	count2parO = vector<llong>(N,0);

	// deb(parent)
	// deb(dist2ancestor)

	for(llong i=0;i<M;i++){
		llong type; cin >> type;
		if(type == 1){
			llong a,x; cin >> a >> x; a--;
			update(a,a,x);
		}else{
			llong a; cin >> a; a--;
			llong ret = query(a,a);
			print(ret);
		}
	}
}









int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}