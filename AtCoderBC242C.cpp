#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define inf 1000000000
#define print(x) cout<<x<<endl
#define MOD 998244353LL

void solve(){
	int N; cin >> N;

	vector<vector<llong>> dp(N+1, vector<llong>(10,0));
	for(int i=1;i<=9;i++) dp[1][i] = 1;
	for(int i=2;i<=N;i++){
		for(int j=1;j<=9;j++){
			if(j-1>=1)
				dp[i][j] += dp[i-1][j-1];
			dp[i][j] += dp[i-1][j];
			if(j+1<=9)
				dp[i][j] += dp[i-1][j+1];

			dp[i][j] %= MOD;
		}
	}

	llong total = 0;
	for(int i=1;i<=9;i++) {
		total += dp[N][i];
		total %= MOD;
	}
	print(total);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}