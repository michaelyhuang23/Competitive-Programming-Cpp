#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unordered_set>
#include <unordered_map>
#include <assert.h>


using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int  ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

struct UFDS{
	iint* parents;
	iint* sizes;
	UFDS(iint n){
		parents = new iint[n];
		sizes = new iint[n];
		fill(sizes, sizes+n, 1);
		For(i,n) parents[i]=i;
	}
	iint find(iint idx){
		iint i = idx;
		while(parents[i]!=i) i=parents[i];
		for(iint j=idx;parents[j]!=j;j=parents[j]) parents[j]=i;
		return i;
	}
	void merge(iint a, iint b){
		iint pa = find(a);
		iint pb = find(b);
		if(pa != pb){
			parents[pb] = pa;
			sizes[pa] += sizes[pb];
		}
	}
};

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        return std::hash<T1>{}(p.first);
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint n,m1,m2;
    cin >> n >> m1 >> m2;
    UFDS finder1(n);
    UFDS finder2(n);
    For(i,m1){
    	iint u,v; cin >> u >> v; u--; v--;
    	finder1.merge(u, v);
    }
    For(i,m2){
    	iint u,v; cin >> u >> v; u--; v--;
    	finder2.merge(u, v);
    }
    unordered_set<iint> vtx1,vtx2;
    map<pair<iint, iint>, iint> edgeSet;
    unordered_set<pair<iint,iint>,pair_hash>* adj1=new unordered_set<pair<iint,iint>,pair_hash>[n];
    //unordered_set<iint>* adj2=new unordered_set<iint>[n];
    For(i,n){
    	iint u = finder1.find(i);
    	vtx1.insert(u);
    	iint v = finder2.find(i);
    	vtx2.insert(v);
    	pair<iint,iint> edgeP = make_pair(u,v);
    	adj1[u].insert(make_pair(v,i));
    	//if(adj2[v].insert(u).second) edge2id[edgeP]=i;
    	edgeSet[edgeP]=i;
    }
    // deb(vtx1); deb(vtx2);
    //For(i,n) deb(adj1[i]);
    queue<pair<pair<iint,iint>,iint > > edges;
    for(auto edge : edgeSet) edges.push(edge);
    vector<pair<iint,iint> > addEdge;
    while(!edges.empty()){
    	auto edgei = edges.front();
    	pair<iint,iint> edge = edgei.first;
    	edge.first = finder1.find(edge.first);
    	edge.second = finder2.find(edge.second);
    	// deb(edge);
    	edges.pop();
    	iint id1 = edgei.second;
    	bool suc=false;
    	for(iint v1 : vtx1){
    		if(finder1.find(v1)==finder1.find(edge.first)) continue;
    		for(pair<iint,iint> v2i : adj1[v1]){
    			iint v2 = v2i.first;
    			if(finder2.find(v2) == finder2.find(edge.second)) continue;
    			iint id2 = v2i.second;
    			// deb(make_pair(v1, v2));
    			// deb(id2);
    			finder1.merge(v1, edge.first);
    			finder2.merge(v2, edge.second);
    			iint head1 = finder1.find(v1);
    			iint head2 = finder2.find(v2);
    			adj1[head1].insert(adj1[edge.first].begin(), adj1[edge.first].end());
    			//adj2[head2].insert(adj2[edge.second].begin(), adj2[edge.second].end());
    			vtx1.erase(edge.first);
    			vtx2.erase(edge.second);
    			suc=true;
    			addEdge.pb(make_pair(id1,id2));
    			break;
    		}
    		if(suc) break;
    	}
    }
    cout<<addEdge.size()<<endl;
    For(i,addEdge.size()) cout<<addEdge[i].first+1<<" "<<addEdge[i].second+1<<endl;

}

/*

an edge can be added if they are from different components
edge cannot be added once it become a tree (so there's upperbound).

if there's (u,v) and they are in different components in both, 
adding it is fine

if adding it prevents some other edge from added, they are mutually exclusive,
so equal (because they link up to same component)

1. reduce to component tree
2. how to find an edge?

if when merging components, we merge the nodes and their edges?

we build implicit edges to indicate where nodes end up

two pairs of nodes can be connected if there's inter-implicit 
connections between them.

we just need to pick 2 edges that don't share vertex, and make connection

it's bipartite:
pick one node on oneside; choose one of its neighbor on the other side;
choose another node that isn't amongst its neighbor: 
bipartite inverted graph; once that node is picked; it picks any of its
neighbor

3. how to merge them
merge edges (both graph); rederive inverted edges between the two
others are fine





*/








