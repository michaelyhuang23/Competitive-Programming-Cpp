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
	vector<int> compC(n,0);
	for(llong i=0;i<n;i++) cin >> comps[i];
	for(llong i=0;i<n;i++) comps[i]--;
	for(int i=0;i<n;i++) compC[comps[i]]++;
	for(llong i=0;i<n;i++) cin >> rewards[i];

	for(llong i=0;i<m;i++){
		llong u, v; cin >> u >> v; u--; v--;
		adj[u].pb(v);
		badj[v].pb(u);
	}

	for(llong i=0;i<n;i++) sort(badj[i].rbegin(), badj[i].rend());

	vector<int> dcomp;
	for(int i=0;i<n;i++) if(compC[i]>=2) dcomp.pb(i);
	vector<int> comp2D(n,-1);
	for(int i=0;i<dcomp.size();i++) comp2D[dcomp[i]]=i;
	int S = dcomp.size();
	int SM = (1<<S);

	vector<vector<llong>> dp(n, vector<llong>(SM, 0));
	int istate = (compC[comps[0]]>=2) ? (1<<comp2D[comps[0]]) : 0;
	dp[0][istate] = rewards[comps[0]];

	for(int i=1;i<n;i++){
		for(int s=0;s<SM;s++){
			if(compC[comps[i]]>=2 && ((1<<comp2D[comps[i]]) & s) == 0) 
				continue;
			for(int other : badj[i]){
				if(compC[comps[i]]>=2){
					// update take
					auto updateTake = [&](){
						int ni = comp2D[comps[i]];
						dp[i][s] = max(dp[i][s], dp[other][s ^ (1<<ni)] + rewards[comps[i]]);
					};
					updateTake();
					auto updateNotTake = [&](){
						dp[i][s] = max(dp[i][s], dp[other][s]);
					};
					updateNotTake();
				}else{
					dp[i][s] = max(dp[i][s], dp[other][s] + rewards[comps[i]]);
				}
			}
		}
	}

	for(int i=0;i<n;i++){
		llong total = 0;
		for(int s=0;s<SM;s++) total=max(total,dp[i][s]);
		print(total);	
	}


}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}