#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 100000000800LL
#define MOD 1000000007LL
#define print(x) cout<<x<<endl


llong n,m;
vector<vector<llong>> adj;

vector<vector<llong>> dist;
vector<vector<llong>> counter;

void BFS(llong source){
	dist = vector<vector<llong>>(n,vector<llong>(2,inf));
	counter = vector<vector<llong>>(n,vector<llong>(2,0));
	dist[source][0] = 0;
	counter[source][0] = 1;
	queue<pair<llong,llong>> pq;
	pq.push(mp(source,0));

	while(!pq.empty()){
		llong id = pq.front().first;
		llong parity = pq.front().second;
		llong oparity = (parity+1)%2;
		pq.pop();
		for(llong to : adj[id]){
			if(dist[to][oparity] > dist[id][parity] + 1){
				dist[to][oparity] = dist[id][parity] + 1;
				counter[to][oparity] = counter[id][parity];
				pq.push(mp(to, oparity));
			}else if(dist[to][oparity] == dist[id][parity] + 1){
				counter[to][oparity] += counter[id][parity];
				counter[to][oparity] %= MOD;
			}
		}
	}
}

void solve(){
	cin >> n >> m;
	adj = vector<vector<llong>>(n);

	llong s, t; cin >> s >> t; s--; t--;

	for(llong i=0;i<m;i++){
		llong a, b; cin >> a >> b;
		a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	BFS(s);

	llong total = 0;


	if(dist[t][0] < dist[t][1]){
		total += counter[t][0];
		if(dist[t][1] == dist[t][0]+1)
			total += counter[t][1];
		total %= MOD;
	}else{
		total += counter[t][1];
		if(dist[t][0] == dist[t][1]+1)
			total += counter[t][0];
		total %= MOD;
	}
	print(total);

}










int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	while(tt--) solve();
}