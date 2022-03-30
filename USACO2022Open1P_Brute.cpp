#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define print(x) cout<<x<<endl
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000

void solve(){
	llong n; cin >> n;
	vector<llong> A(n);
	for(llong i=0;i<n;i++) cin >> A[i];


	vector<vector<llong>> dp(n, vector<llong>(n, inf));
	for(llong i=0;i<n;i++) dp[i][i] = A[i];

	for(llong r=2;r<=n;r++){
		for(llong s=0;s<n;s++){
			llong e = s+r-1;
			if(e>=n) continue;
			llong minc = inf;
			for(llong k=s;k<e;k++){
				minc = min(minc,max(dp[s][k],dp[k+1][e])+1);
			}
			dp[s][e] = minc;
		}
	}

	llong total = 0;
	for(llong s=0;s<n;s++)
		for(llong e=s;e<n;e++){
			total += dp[s][e];
		}
	print(total);
}





int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}