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
vector<llong> dist;

const llong modder = 1<<30;


void compute_dist(llong cur, llong par, llong d=0){
	for(auto& edge : adj[cur]){
		llong son = edge.first; llong w = edge.second;
		if(son == par) continue;
		compute_dist(son, cur, d+w);
	}
	dist[cur] = d;
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

	llong prevans = 0;
	for(llong i=0;i<q;i++){
		llong type; cin >> type;
		if(type == 1){ // query
			llong l,r,v; cin >> l >> r >> v;
			// l = (prevans % modder) ^ l;
			// r = (prevans % modder) ^ r;
			// v = (prevans % modder) ^ v;
			l--; r--; v--;

			dist = vector<llong>(n, inf);
			dist[v] = 0;

			compute_dist(v, v);

			llong total = 0;

			for(int i=l;i<=r;i++){
				total += dist[A[i]];
			}

			print(total);
			prevans = total;
		}else{
			llong j; cin >> j;
			// j = (prevans % modder) ^ j;
			j--;
			swap(A[j], A[j+1]);
		}
	}
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}