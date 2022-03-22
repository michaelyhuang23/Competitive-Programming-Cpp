// #include "debughelp.hpp"

#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 1000000000000000LL

llong n, q;
vector<llong> A;
vector<vector<pair<llong,llong>>> adj;
vector<llong> subtreesize;
vector<bool> mask;
vector<vector<llong>> dist2ancestor;
vector<llong> parent;
vector<llong> depth;
vector<map<llong,llong>> S, C, Cp;

const llong max_depth = 25;
const llong modder = 1<<30;

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


void build_centroid_tree(llong cur, llong par){
	find_size(cur, par);
	llong c = find_centroid(cur, par, subtreesize[cur]);

	if(cur == par && cur == 0) {
		parent[c] = c;
		depth[c] = 0;
	}else{
		parent[c] = par;
		depth[c] = depth[par]+1;
		assert(depth[c]<max_depth);
	}

	compute_dist(c, c, depth[c]);

	mask[c] = true;

	for(auto& edge : adj[c]){
		llong son = edge.first;
		if(mask[son]) continue;
		build_centroid_tree(son, c);
	}
}




void update_node(llong c, llong x, llong i, llong mul = 1){
	llong L = depth[c]; // use map for S, C, Cp

	auto it = S[c].find(i);
	auto updateS = [&](){
		if(it != S[c].end()){
			it->second+=1*mul;
			if(it->second == 0) S[c].erase(it);
		}else{
			// assert(mul == 1);
			llong prev_val = 0;
			auto it2 = S[c].upper_bound(i);
			if(it2 != S[c].begin()) prev_val = prev(it2)->second;
			S[c].insert(mp(i, prev_val + 1*mul));
		}
	};

	updateS();

	auto updateC = [&](){ // quite sketchy
		if(it != S[c].end()){
			C[c][i] += dist2ancestor[x][L]*mul; // this should be fine for building if we insert in increasing order
			if(it->second == 0) C[c].erase(i);
		}else{
			// assert(mul == 1);
			llong prev_val = 0;
			auto it2 = C[c].upper_bound(i);
			if(it2 != C[c].begin()) prev_val = prev(it2)->second;
			C[c].insert(mp(i, prev_val + dist2ancestor[x][L]*mul));
		}
	};

	updateC();

	auto updateCp = [&](){
		if(it != S[c].end()){
			Cp[c][i] += dist2ancestor[x][L-1]*mul; // this should be fine for building if we insert in increasing order
			if(it->second == 0) Cp[c].erase(i);
		}else{
			// assert(mul == 1);
			llong prev_val = 0;
			auto it2 = Cp[c].upper_bound(i);
			if(it2 != Cp[c].begin()) prev_val = prev(it2)->second;
			Cp[c].insert(mp(i, prev_val + dist2ancestor[x][L-1]*mul));
		}
	};

	if(L>0) updateCp();

}


llong query(llong c, llong l, llong r, llong v){ // l, r should be indexed from 0
	llong sum = 0;
	llong L = depth[c];
	auto get_le = [&](map<llong,llong>& m, llong i){ // return value at <=i
		auto it = m.upper_bound(i);
		if(it == m.begin()) return 0LL;
		else return prev(it)->second;
	};

	llong SS = (get_le(S[c], r) - get_le(S[c], l-1));
	if(L>0){ // presubtract
		sum -= get_le(Cp[c], r) - get_le(Cp[c], l-1);
		sum -= dist2ancestor[v][L-1] * SS;
	}
	sum += get_le(C[c], r) - get_le(C[c], l-1);
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

	dist2ancestor = vector<vector<llong>>(n, vector<llong>(max_depth, inf));
	mask = vector<bool>(n,0);
	parent = vector<llong>(n);
	depth = vector<llong>(n,0);
	subtreesize = vector<llong>(n,0);
	iota(parent.begin(), parent.end(), 0);

	build_centroid_tree(0,0);

	print("tree built");
	// all good here

	S = vector<map<llong,llong>>(n);
	C = vector<map<llong,llong>>(n);
	Cp = vector<map<llong,llong>>(n);

	for(llong i=0;i<n;i++){
		llong x = A[i];
		for(llong c = x; true; c = parent[c]){
			update_node(c, x, i, 1);
			if(c==parent[c]) break;
		}
	}

	print("pre-updates");

	// looks mostly good here

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
			for(llong c = A[j]; true; c = parent[c]){ // remove from j
				update_node(c, A[j], j, -1);
				if(c==parent[c]) break;
			}

			for(llong c = A[j+1]; true; c = parent[c]){ // add to j
				update_node(c, A[j+1], j, 1);
				if(c==parent[c]) break;
			}

			// optional: only do if it doesn't contain the other one. 

			for(llong c = A[j]; true; c = parent[c]){ // add to j+1
				if(S[c].find(j+1) != S[c].end()) break; // already occupied, no need to add
				update_node(c, A[j], j+1, 1);
				if(c==parent[c]) break;
			}

			for(llong c = A[j+1]; true; c = parent[c]){ // remove from j+1
				if(S[c].find(j) != S[c].end()) break; // already occupied, no need to remove
				update_node(c, A[j+1], j+1, -1);
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