

#include<bits/stdc++.h>
//#include "debughelp.hpp"

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000008

#define print(x) cout<<x<<endl


void solve(){
	int n, m; cin >> n >> m;
	vector<int> due(n);
	for(int i=0;i<n;i++) cin >> due[i];

	vector<vector<tuple<int,int,int>>> options(n, vector<tuple<int,int,int>>());
	for(int i=0;i<m;i++){
		int e, t, p; cin >> e >> t >> p;
		e--;
		options[e].pb(mt(p,t,i+1));
	}

	// p, t

	vector<int> mintime(n,inf);

	vector<vector<int>> usedO(n, vector<int>());

	//deb(options)

	for(int type=0;type<n;type++){
		int mm = options[type].size();
		vector<vector<int>> dp(mm+1, vector<int>(201, inf));
		for(int i=0;i<=mm;i++) dp[i][0] = 0;

		for(int i=1;i<=mm;i++){
			for(int p=0;p<=200;p++){
				dp[i][p] = dp[i-1][p];
				int newp = p - get<0>(options[type][i-1]); 
				int ct = get<1>(options[type][i-1]);
				if(newp >= 0){
					dp[i][p] = min(dp[i][p], dp[i-1][newp] + ct);
				}
			}
		}
		int minT = inf;
		int minP = 0;
		for(int p=100;p<=200;p++) {
			if(dp[mm][p] < minT){
				minT = dp[mm][p];
				minP = p;
			}
		}
		mintime[type] = minT;

		for(int i=mm;i>=1;i--){
			int newp = minP - get<0>(options[type][i-1]); 
			int ct = get<1>(options[type][i-1]);
			if(dp[i][minP] == dp[i-1][minP]) continue; // don't use
			if(newp >= 0){
				if(dp[i][minP] == dp[i-1][newp] + ct){
					// use this
					usedO[type].pb(get<2>(options[type][i-1]));
					minP = newp;
				}
			}
		}
	}

	//deb(mintime)

	int ct = 0;
	bool suc = true;
	vector<int> usedOps;
	for(int i=0;i<n;i++){
		if(ct+mintime[i] > due[i]) {
			suc = false; break;
		}
		ct += mintime[i];
		usedOps.insert(usedOps.end(), usedO[i].begin(), usedO[i].end());
	}

	if(!suc) print(-1);
	else {
		print(usedOps.size());
		for(int i : usedOps)
			cout<<i<<" ";
		cout<<endl;
	}
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--) solve();
}