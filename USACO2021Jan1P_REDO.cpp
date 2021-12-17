#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<assert.h>
#include<unordered_set>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define mt make_tuple


struct Graph{
	int n,m;
	vector<vector<int> > badj;
	vector<int> od;
	vector<int> ed;
	vector<int> md;
	Graph(){
		cin >> n >> m;
		badj = vector<vector<int> >(2*n);
		ed = vector<int>(n,-1);
		od = vector<int>(n,-1);
		for(int i=0;i<m;i++){
			int a,b; cin >> a >> b;
			a--; b--;
			badj[a].pb(b+n);
			badj[b+n].pb(a);
			badj[b].pb(a+n);
			badj[a+n].pb(b);
		}
		BFS(0);
		md = vector<int>(n);
		for(int i=0;i<n;i++) {
			if(ed[i] == -1 || od[i] == -1) md[i] = -1;
			else md[i] = max(ed[i], od[i]);
		}
	}
	void BFS(int root){
		queue<int> pq;
		pq.push(root);
		ed[root] = 0;
		while(!pq.empty()){
			int cur = pq.front(); pq.pop();
			for(int nei : badj[cur]){
				if(nei>=n){
					if(od[nei-n] != -1) continue;
					assert(cur<n);
					od[nei-n] = ed[cur]+1;
				}else{
					if(ed[nei] != -1) continue;
					assert(cur>=n);
					ed[nei] = od[cur-n]+1;
				}
				pq.push(nei);
			}
		}
	}
};

llong modulo_pow(llong base,llong exp) {
    llong result=1;
    while(exp > 0){
        if(exp%2 == 1){
            result=(result*base)%MOD; //getting rid of the odd term
        }
        base = (base*base)%MOD; // squaring the base
        exp /= 2;
    }
    return (llong) result%MOD;
}

llong inv(llong num){
	if(num==0) return 1;
	return modulo_pow(num, MOD-2);
}


int K;
vector<Graph> graphs;
vector<tuple<int, int, int> > evens, odds, maxs;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> K;

	for(int i=0;i<K;i++){
		graphs.pb(Graph());
	}

	for(int k=0;k<K;k++){
		auto& G = graphs[k];
		for(int i=0;i<G.n;i++)
			if(G.ed[i]>-1) evens.pb(mt(G.ed[i], k, i));
	}

	for(int k=0;k<K;k++){
		auto& G = graphs[k];
		for(int i=0;i<G.n;i++)
			if(G.od[i]>-1) odds.pb(mt(G.od[i], k, i));
	}

	for(int k=0;k<K;k++){
		auto& G = graphs[k];
		for(int i=0;i<G.n;i++)
			if(G.md[i]>-1) maxs.pb(mt(G.md[i], k, i));
	}

	sort(odds.begin(), odds.end());
	sort(evens.begin(), evens.end());
	sort(maxs.begin(), maxs.end());

	//deb(odds) deb(evens) deb(maxs)

	llong prod = 0; // prod across all graphs
	unordered_set<int> active;
	vector<llong> histE(K,0);
	llong ecounts = 0;
	for(int i=0;i<evens.size();i++){
		int ed = get<0>(evens[i]);
		int k = get<1>(evens[i]);
		int j = get<2>(evens[i]);
		//deb(active)deb(prod)
		if(active.size() != K){
			active.insert(k);
			if(active.size() != K) {histE[k]++; continue;} 
			else {
				prod = 1;
				for(int t=0;t<K;t++) if(histE[t]!=0) prod *= histE[t];
			}
		}
		//deb(prod) deb(histE)
		llong cc = (prod * inv(histE[k]))%MOD;
		//deb(cc)
		ecounts += cc * ed;
		ecounts %= MOD;
		histE[k]++;
		prod = (cc * histE[k])%MOD;
	}
	//deb(ecounts)


	prod = 0; // prod across all graphs
	active = unordered_set<int>();
	vector<llong> histO(K,0);
	llong ocounts = 0;
	for(int i=0;i<odds.size();i++){
		int od = get<0>(odds[i]);
		int k = get<1>(odds[i]);
		int j = get<2>(odds[i]);
		//deb(active)deb(prod)
		if(active.size() != K){
			active.insert(k);
			if(active.size() != K) {histO[k]++; continue;} 
			else {
				prod = 1;
				for(int t=0;t<K;t++) if(histO[t]!=0) prod *= histO[t];
			}
		}
		//deb(prod) deb(histO)
		llong cc = (prod * inv(histO[k]))%MOD;
		//deb(cc)
		ocounts += cc * od;
		ocounts %= MOD;
		histO[k]++;
		prod = (cc * histO[k])%MOD;
	}
	//deb(ocounts)


	prod = 0; // prod across all graphs
	active = unordered_set<int>();
	vector<llong> histM(K,0);
	llong mcounts = 0;
	for(int i=0;i<maxs.size();i++){
		int md = get<0>(maxs[i]);
		int k = get<1>(maxs[i]);
		int j = get<2>(maxs[i]);
		//deb(active)deb(prod)
		if(active.size() != K){
			active.insert(k);
			if(active.size() != K) {histM[k]++; continue;} 
			else {
				prod = 1;
				for(int t=0;t<K;t++) if(histM[t]!=0) prod *= histM[t];
			}
		}
		//deb(prod) deb(histM)
		llong cc = (prod * inv(histM[k]))%MOD;
		//deb(cc)
		mcounts += cc * md;
		mcounts %= MOD;
		histM[k]++;
		prod = (cc * histM[k])%MOD;
	}
	//deb(mcounts)

	llong total = (ocounts + ecounts - mcounts + MOD)%MOD;
	cout<<total<<endl;
}









