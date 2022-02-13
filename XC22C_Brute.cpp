#include<bits/stdc++.h>
 
 
 
using namespace std;
 
typedef long long llong;
#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<endl
 
void floodfill(llong st, vector<bool>& visited, vector<vector<llong>>& badj){
	visited[st] = true;
	for(llong to : badj[st]){
		if(!visited[to]) floodfill(to, visited, badj);
	}
}
 
void solve(){
	llong n, m; cin >> n >> m;
	vector<vector<llong>> adj(n);
	vector<vector<llong>> badj(n);
	vector<llong> comps(n);
	vector<llong> rewards(n);
	for(llong i=0;i<n;i++) cin >> comps[i];
	for(llong i=0;i<n;i++) comps[i]--;
	for(llong i=0;i<n;i++) cin >> rewards[i];
 
	for(llong i=0;i<m;i++){
		llong u, v; cin >> u >> v; u--; v--;
		adj[u].pb(v);
		badj[v].pb(u);
	}
 
	for(llong i=0;i<n;i++) sort(badj[i].rbegin(), badj[i].rend());
 
	vector<unordered_set<llong>> dp(n);
	dp[0].insert(1<<comps[0]);
	for(llong i=1;i<n;i++){
		vector<bool> visited(i, 0);
		for(llong to : badj[i]){
			if(visited[i]) continue;
			floodfill(to, visited, badj);
			//deb("from");
			//deb(mp(to,i))
			for(llong state : dp[to]){
				state |= (1<<comps[i]);
				dp[i].insert(state); // we need to filter the states that are too small. 
			}
		}
		// for(llong st : dp[i]){
 
		// }
	}
	//deb(dp)
 
	for(int v=0;v<n;v++){
		llong maxTotal = 0;
		for(llong state : dp[v]){
			llong total = 0;
			for(llong i=0;i<n;i++){
				if((1<<i) & state){
					total += rewards[i];
				}
			}
			maxTotal = max(maxTotal, total);
		}
		print(maxTotal);
	}
 
 
}
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}