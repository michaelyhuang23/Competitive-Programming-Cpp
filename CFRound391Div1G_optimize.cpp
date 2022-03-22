// #include "debughelp.hpp"
#pragma GCC optimize("O2")
#pragma GCC target("avx2")

#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 100000000000000000LL

llong n, q;
vector<llong> A;


const llong max_depth = 25;
const llong modder = 1<<30;

vector<vector<pair<llong,llong>>> adj;
vector<llong> subtreesize;
vector<bool> mask;
llong dist2ancestor[200002][max_depth];
vector<llong> parent;
vector<llong> depth;
vector<vector<pair<llong,llong>>> S, C, Cp;
tuple<llong,llong,llong> pq[400002];


void find_size(llong cur, llong par){
	llong csize = 0;
	for(auto& edge : adj[cur]){
		llong son = edge.first;
		if(son == par || mask[son]) continue;
		find_size(son, cur);
		csize += subtreesize[son];
	}
	csize++;
	subtreesize[cur] = csize;
}


llong find_centroid(llong cur, llong par, llong n){
	for(auto& edge : adj[cur]){
		llong son = edge.first;
		if(son == par || mask[son]) continue;
		if(subtreesize[son]*2 > n) return find_centroid(son, cur, n);
	}
	return cur;
}


void compute_dist(llong cur, llong par, llong h, llong d=0){
	for(auto& edge : adj[cur]){
		llong son = edge.first; llong w = edge.second;
		if(son == par || mask[son]) continue;
		compute_dist(son, cur, h, d+w);
	}
	dist2ancestor[cur][h] = d;
}

void compute_dist(llong st, llong h){
	llong f=0, b=0;
	pq[b++] = mt(st,0,st);
	while(f!=b){
		auto ret = pq[f++]; 
		llong c = get<0>(ret);
		llong d = get<1>(ret);
		llong fa = get<2>(ret);
		dist2ancestor[c][h] = d;
		for(auto& edge : adj[c]){
			llong son = edge.first; llong w = edge.second;
			if(son == fa || mask[son]) continue;
			pq[b++]=mt(son, d+w, c);
		}
	}
}


llong build_centroid_tree(llong cur, llong par){
	find_size(cur, par);
	llong c = find_centroid(cur, par, subtreesize[cur]);

	if(cur == par && cur == 0) {
		parent[c] = c;
		depth[c] = 0;
	}else{
		parent[c] = par;
		depth[c] = depth[par]+1;
		// if(depth[c]>=max_depth){
		// 	print("too high");
		// }
		// assert(depth[c]<max_depth);
	}

	compute_dist(c, depth[c]);

	mask[c] = true;
	llong csize = 0;
	for(auto& edge : adj[c]){
		llong son = edge.first;
		if(mask[son]) continue;
		csize += build_centroid_tree(son, c);
	}
	csize++;

	C[c].reserve(csize);
	S[c].reserve(csize);
	Cp[c].reserve(csize);

	return csize;
}


void insert_node(llong c, llong x, llong i){
	llong L = depth[c]; // use map for S, C, Cp

	llong prev_val = 0;
	if(!S[c].empty()) prev_val = S[c].back().second;
	S[c].pb(mp(i, prev_val + 1));

	prev_val = 0;
	if(!C[c].empty()) prev_val = C[c].back().second;
	C[c].pb(mp(i, prev_val + dist2ancestor[x][L]));
	
	if(L>0){
		prev_val = 0;
		if(!Cp[c].empty()) prev_val = Cp[c].back().second;
		Cp[c].pb(mp(i, prev_val + dist2ancestor[x][L-1]));
	}
}

void update_node_both(llong c, llong i){
	llong L = depth[c]; // use map for S, C, Cp

	auto it = lower_bound(S[c].begin(), S[c].end(), mp(i,0LL));
	llong id = distance(S[c].begin(), it);
	//assert(id+1LL<S[c].size()); // it should have both


	C[c][id].second -= dist2ancestor[A[i]][L];
	C[c][id].second += dist2ancestor[A[i+1]][L];

	if(L>0){
		Cp[c][id].second -= dist2ancestor[A[i]][L-1];
		Cp[c][id].second += dist2ancestor[A[i+1]][L-1];
	}

}


void update_node_left(llong c, llong i){
	llong L = depth[c]; // use map for S, C, Cp

	auto it = lower_bound(S[c].begin(), S[c].end(), mp(i,0LL));
	llong id = distance(S[c].begin(), it);
	S[c][id].first = i+1;
	C[c][id].first = i+1;
	if(L>0) Cp[c][id].first = i+1;

}


void update_node_right(llong c, llong i){
	llong L = depth[c]; // use map for S, C, Cp

	auto it = lower_bound(S[c].begin(), S[c].end(), mp(i+1,0LL));
	llong id = distance(S[c].begin(), it);
	S[c][id].first = i;
	C[c][id].first = i;
	if(L>0) Cp[c][id].first = i;

}


llong query(llong c, llong l, llong r, llong v){ // l, r should be indexed from 0
	llong sum = 0;
	llong L = depth[c];
	auto get_le = [&](vector<pair<llong,llong>>& m, llong i){ // return value at <=i
		auto it = upper_bound(m.begin(),m.end(), mp(i,inf));
		return distance(m.begin(), it) - 1LL;
	};

	llong back = get_le(S[c], r);
	llong front = get_le(S[c], l-1);
	llong fS = 0, fCp = 0, fC = 0;
	llong bS = 0, bCp = 0, bC = 0;

	if(front>=0) {
		fS = S[c][front].second;
		fCp = Cp[c][front].second;
		fC = C[c][front].second;
	}
	if(back>=0){
		bS = S[c][back].second;
		bCp = Cp[c][back].second;
		bC = C[c][back].second;
	}

	llong SS = (bS - fS);
	if(L>0){ // presubtract
		sum -= bCp - fCp; 
		sum -= dist2ancestor[v][L-1] * SS;
	}
	sum += bC - fC;
	sum += dist2ancestor[v][L] * SS;
	return sum;
}



void solve(){
	cin >> n >> q;
	A = vector<llong>(n);
	for(llong i=0;i<n;i++) cin>>A[i];
	for(llong i=0;i<n;i++) A[i]--;

	adj = vector<vector<pair<llong,llong>>>(n);

	for(llong i=0;i<n-1;i++){
		llong a,b,w; cin >> a >> b >> w; a--; b--;
		adj[a].pb(mp(b, w));
		adj[b].pb(mp(a,w));
	}

	mask = vector<bool>(n,0);
	parent = vector<llong>(n);
	depth = vector<llong>(n,0);
	subtreesize = vector<llong>(n,0);
	iota(parent.begin(), parent.end(), 0);

	S = vector<vector<pair<llong,llong>>>(n);
	C = vector<vector<pair<llong,llong>>>(n);
	Cp = vector<vector<pair<llong,llong>>>(n);

	build_centroid_tree(0,0);

	// print("tree built");
	// all good here

	for(llong i=0;i<n;i++){
		llong x = A[i];
		for(llong c = x; true; c = parent[c]){
			insert_node(c, x, i);
			if(c==parent[c]) break;
		}
	}

	//deb(S)

	// print("pre-updates");

	// looks mostly good here

	auto get_lca = [&](llong x, llong y){
		if(depth[x]<depth[y]) swap(x,y);
		while(depth[x]>depth[y]) x = parent[x];
		if(x==y) return x;
		while(x != y){
			x = parent[x];
			y = parent[y];
		}
		return x;
	};

	llong prevans = 0;
	for(llong i=0;i<q;i++){
		llong type; cin >> type;
		if(type == 1){ // query
			llong l,r,v; cin >> l >> r >> v;
			l = (prevans % modder) ^ l;
			r = (prevans % modder) ^ r;
			v = (prevans % modder) ^ v;
			l--; r--; v--;

			llong total = 0;
			for(llong c = v; true; c = parent[c]){
				total += query(c, l, r, v);
				if(c==parent[c]) break;
			}

			print(total);
			prevans = total;
		}else{
			llong j; cin >> j;
			j = (prevans % modder) ^ j;
			j--;
			// swap A[j] with A[j+1]

			llong lca = get_lca(A[j],A[j+1]);

			// deb(mt(A[j],A[j+1],lca))

			for(llong c = lca; true; c = parent[c]){ // for nodes that contain both
				update_node_both(c, j);
				if(c==parent[c]) break;
			}

			// optional: only do if it doesn't contain the other one. 

			for(llong c = A[j]; c != lca; c = parent[c]){ // update left
				update_node_left(c, j);
				if(c==parent[c]) break;
			}

			for(llong c = A[j+1]; c != lca; c = parent[c]){ // remove from j+1
				update_node_right(c, j);
				if(c==parent[c]) break;
			}

			swap(A[j], A[j+1]);
		}
	}
}










































int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}