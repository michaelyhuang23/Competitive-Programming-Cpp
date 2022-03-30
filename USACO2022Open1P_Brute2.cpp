
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
			int ll = s, rr = e-1, ans = ll;
			while(ll<=rr){
				int mm = (ll+rr)/2;
				if(dp[s][mm] <= dp[mm+1][e]){ans=mm; ll=mm+1;}
				else rr=mm-1;
			}

			dp[s][e] = max(dp[s][ans],dp[ans+1][e])+1;
			if(ans+2<=e)
				dp[s][e] = min(dp[s][e], max(dp[s][ans+1], dp[ans+2][e])+1);
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