#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define inf 100000000000000LL

void solve(llong tt){
	llong n, p; cin >> n >> p;
	vector<llong> mins(n+1), maxs(n+1);
	for(llong i=1;i<=n;i++){
		vector<llong> pres(p);
		for(llong j=0;j<p;j++) cin >> pres[j];
		llong minn = *min_element(pres.begin(), pres.end());
		llong maxx = *max_element(pres.begin(), pres.end());
		mins[i] = minn;
		maxs[i] = maxx;
	}
	vector<vector<llong>> dp(n+1, vector<llong>(2, inf));
	// 0: increasing
	// 1: decreasing

	mins[0] = maxs[0] = 0;
	dp[0][0] = dp[0][1] = 0;
	for(llong i=1;i<=n;i++){
		llong c1 = dp[i-1][1]+abs(mins[i-1]-mins[i])+maxs[i]-mins[i];
		llong c2 = dp[i-1][0]+abs(maxs[i-1]-mins[i])+maxs[i]-mins[i];
		dp[i][0] = min(c1, c2);

		llong c3 = dp[i-1][1]+abs(mins[i-1]-maxs[i])+maxs[i]-mins[i];
		llong c4 = dp[i-1][0]+abs(maxs[i-1]-maxs[i])+maxs[i]-mins[i];
		dp[i][1] = min(c3, c4);
	}

	llong total = min(dp[n][0], dp[n][1]);
	cout<<"Case #"<<tt<<": "<<total<<endl;
}







int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	for(llong i=1;i<=tt;i++)
		solve(i);
}