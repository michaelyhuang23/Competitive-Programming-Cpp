#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define inf 1000000000
#define print(x) cout<<x<<endl
#define MOD 998244353LL


void solve(){
	llong N; cin >> N;
	string S;  cin >> S;
	// first we check if mid equal case works
	llong mid = (N+1)/2;
	bool hasMid = true;
	if(N%2==0){
		string M = S.substr(0,mid);
		string T = M;
		reverse(T.begin(), T.end());
		string H = M+T;
		assert(H.size() == S.size());
		hasMid = H<=S;
	}else{
		string M = S.substr(0,mid-1);
		string T = M;
		reverse(T.begin(), T.end());
		string H = M+S[mid-1]+T;
		assert(H.size() == S.size());
		hasMid = H<=S;
	}
	

	vector<vector<llong>> dp(N+1, vector<llong>(2, 0));
	// 1: already smaller
	// 0: still equal
	// init

	dp[0][0] = 1;
	
	for(llong i=1;i<=mid;i++){
		for(char c='A';c<='Z';c++){
			if(c > S[i-1]) {
				dp[i][1] += dp[i-1][1];
			}else if(c < S[i-1]){
				dp[i][1] += dp[i-1][0] + dp[i-1][1];
			}else if(c==S[i-1]){
				dp[i][1] += dp[i-1][1];
				dp[i][0] += dp[i-1][0];
			}
			dp[i][1] %= MOD;
			dp[i][0] %= MOD;
		}
	}
	llong total = 0;
	total += dp[mid][1];
	total += hasMid;
	total %= MOD;
	print(total);

}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	while(tt--) solve();
}