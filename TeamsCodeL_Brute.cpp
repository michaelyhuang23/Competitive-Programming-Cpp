#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl




int N,M;
vector<vector<llong>> adj;
vector<llong> counter;




llong sum = 0;
void dfs(int cur, int par, int d){
	for(int son : adj[cur]){
		if(son == par) continue;
		dfs(son, cur, d+1);
	}
	if(d%2 == 0)
		sum += d*counter[cur];
}





void solve(){
	cin >> N >> M;
	adj = vector<vector<llong>>(N);

	for(llong i=0;i<N-1;i++){
		llong a,b; cin >> a >> b; a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	counter = vector<llong>(N,0);

	for(llong i=0;i<M;i++){
		llong type; cin >> type;
		if(type == 1){
			llong a,x; cin >> a >> x; a--;
			counter[a]+=x;
		}else{
			llong a; cin >> a; a--;
			sum = 0;
			dfs(a,a,0);
			print(sum);
		}
	}
}









int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}