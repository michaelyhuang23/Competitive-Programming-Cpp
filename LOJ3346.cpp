#include<bits/stdc++.h>
#include "swap.h"

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 2000000000
#define print(x) cout<<x<<endl

struct UFDS{
	vector<int> finder;
	UFDS(vector<int>& arr){
		finder = arr;		
	}
	UFDS(int n){
		finder = vector<int>(n); 
		iota(finder.begin(), finder.end(), 0); // assumes 0th based
	}
	int find(int n){
		if(finder[n] == n) return n; // reaches root;
		int ret = find(finder[n]);
		finder[n] = ret; // path compression
		return ret;
	}
	void merge(int a, int b){
		int pa = find(a);
		int pb = find(b);
		if(pa == pb) return;
		finder[pb] = pa;
	}
};

struct Node{
	int pa;
	int weight;
	bool isChain; 
	int s1, s2; // the two end points
	int minFill; // minimum way to saturate the connected component this represents
	Node() : pa(-1), weight(inf), isChain(true), s1(-1), s2(-1), minFill(inf) {}
};

int N, M;
vector<tuple<int,int,int>> edges;
vector<Node> nodes;
vector<vector<int>> adj;
vector<int> depth;
vector<vector<int>> lift;

void get_depth(int cur, int parent){
	if(cur != parent) depth[cur] = depth[parent]+1;
	for(int son : adj[cur]){
		if(son == parent) continue;
		get_depth(son, cur);
	}
}

int get_lca(int u, int v){
	if(depth[u]<depth[v]) swap(u,v);
	int offset = depth[u]-depth[v];
	for(int i=19;i>=0;i--){
		if((1<<i) <= offset){
			offset -= (1<<i);
			u = lift[i][u];
		}
	}

	assert(depth[u] == depth[v]);

	if(u == v) return u;

	for(int i=19;i>=0;i--){
		if(lift[i][u] != lift[i][v]){
			u = lift[i][u];
			v = lift[i][v];
		}
	}

	return lift[0][u];
}

void init(int N_, int M_, vector<int> U, vector<int> V, vector<int> W){
	N = N_;
	M = M_;
	edges = vector<tuple<int,int,int>>(M);
	for(int i=0;i<M;i++){
		edges[i] = mt(W[i], U[i], V[i]);
	}

	sort(edges.begin(), edges.end());

	int K = 2*N-1;

	nodes = vector<Node>(K); // should be 2*N-1 nodes
	adj = vector<vector<int>>(K);

	UFDS cnn(K);
	int cc = N;

	for(int i=0;i<N;i++){
		nodes[i].isChain = true;
		nodes[i].s1 = nodes[i].s2 = i; 
		nodes[i].minFill = inf;
		nodes[i].weight = 0;
	}

	vector<tuple<int,int,int>> saturators;

	for(auto& edge : edges){
		int u = get<1>(edge); // numbered from 0
		int v = get<2>(edge);
		int w = get<0>(edge);

		int uu = cnn.find(u);
		int vv = cnn.find(v);
		if(uu == vv){
			// repeat!!! they must be connected on kruskal tree!!!
			// we build the tree first and deal with them later on the built tree
			// so that we can use binary lift lca
			saturators.pb(mt(w,u,v));
		}else{
			assert(cc<K);
			// deb("connect")
			// deb(mp(u,v))
			nodes[uu].pa = cc;
			nodes[vv].pa = cc;
			adj[uu].pb(cc);
			adj[vv].pb(cc);
			adj[cc].pb(uu);
			adj[cc].pb(vv);

			nodes[cc].weight = w;
			nodes[cc].isChain = false;
			if(nodes[uu].isChain && nodes[vv].isChain)
				if(u == nodes[uu].s1 || u == nodes[uu].s2)
					if(v == nodes[vv].s1 || v == nodes[vv].s2){
						nodes[cc].isChain = true;
						nodes[cc].s1 = (u==nodes[uu].s1) ? nodes[uu].s2 : nodes[uu].s1;
						nodes[cc].s2 = (v==nodes[vv].s1) ? nodes[vv].s2 : nodes[vv].s1;
					}

			cnn.merge(cc,uu);
			cnn.merge(cc,vv);
			cc++;
		}
	} 
	// higher the index, higher it's on the tree
	nodes[K-1].pa = K-1;

	depth = vector<int>(K,0);
	get_depth(K-1,K-1);

	//deb(depth)

	lift = vector<vector<int>>(20, vector<int>(K));
	for(int i=0;i<K;i++){
		lift[0][i] = nodes[i].pa;
	}
	//deb(lift[0])

	for(int i=1;i<20;i++){
		for(int j=0;j<K;j++){
			lift[i][j] = lift[i-1][lift[i-1][j]];
		}
	}




	for(auto& edge : saturators){
		int u = get<1>(edge); // numbered from 0
		int v = get<2>(edge);
		int w = get<0>(edge);

		int cc = get_lca(u,v);

		assert(nodes[cc].weight <= w);
		// we should find the highest ancestor with weight <= w to put it there
		for(int i=19;i>=0;i--){
			if(nodes[lift[i][cc]].weight <= w)
				cc = lift[i][cc];
		}

		nodes[cc].minFill = min(nodes[cc].minFill, w);
	}

	for(int i=0;i<K;i++){
		nodes[nodes[i].pa].minFill = min(nodes[nodes[i].pa].minFill, nodes[i].minFill);
	}


	// for(int i=0;i<K;i++)
	// 	print(nodes[i].minFill);
}

int get_val2(int idx) {
    // get value of the node
    if (nodes[idx].isChain) {
        if (nodes[idx].pa == idx){
        	print("1");
        	print(idx);
            return nodes[idx].minFill;
        }
        if(nodes[idx].minFill < inf/2+10){
        	print("2");
        	print(idx);
        	return nodes[idx].minFill;
        }
        return get_val2(nodes[idx].pa);
    } else {
    	print("3");
    	print(idx);
        return nodes[idx].weight;
    }
}


int get_val3(int idx) {
    // get value of the node
    if (nodes[idx].isChain) {
        if (nodes[idx].pa == idx){
        	print(idx);
            return nodes[idx].minFill;
        }
        int ret = get_val3(nodes[idx].pa);
        if(nodes[idx].minFill < ret){
        	print(idx);
        	return nodes[idx].minFill;
        }else
        	return ret;
    } else {
    	print("3");
    	print(idx);
        return nodes[idx].weight;
    }
}

int get_val(int idx){
	// get value of the node
	int minn = nodes[idx].weight; // ensure we at least reach there
	if(!nodes[idx].isChain) return minn;
	if(nodes[idx].minFill < inf/2+10) return max(minn,nodes[idx].minFill);
	for(int i=19;i>=0;i--){
		if(nodes[lift[i][idx]].isChain && nodes[lift[i][idx]].minFill > inf/2+10){
			idx=lift[i][idx];
		}
	}
	idx = lift[0][idx];
	if(!nodes[idx].isChain) return nodes[idx].weight;
	return max(nodes[idx].minFill, nodes[idx].weight); // you have to reach its weight at least
}


int getMinimumFuelCapacity(int x, int y){
	int lca = get_lca(x,y);
	int ret = get_val(lca);
	if(ret > inf/2+10) return -1;
	else return ret;
}


// int main(){
// 	ios_base::sync_with_stdio(0);
// 	cin.tie(0);
// 	int n, m; cin >> n >> m;
// 	vector<int> U(m), V(m), W(m);
// 	for(int i = 0; i < m; i++){
// 		cin >> U[i] >> V[i] >> W[i];
// 	}
// 	init(n,m,U,V,W);
// 	int tt; cin >> tt;
// 	while(tt--){
// 		int a, b; cin >> a >> b;
// 		print(getMinimumFuelCapacity(a,b));
// 	}
// }








