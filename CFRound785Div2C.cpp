#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<endl
#define MOD 1000000007

vector<int> ps;
vector<int> dp;

void solve(){
	int n; cin >> n;

	
	print(dp[n]%MOD);
}

int main(){
	ps.pb(-1);
	for(int i=1;i<=9;i++) ps.pb(i); // 1 digit
	for(int i=1;i<=9;i++) ps.pb(i*10+i); // 2 digits
	for(int i=10;i<=99;i++) ps.pb(i*10 + i/10); // 3 digits
	for(int i=10;i<=99;i++) ps.pb(i*100 + (i%10)*10 + i/10); // 4 digits
	for(int i=100;i<=400;i++) ps.pb(i*100 + ((i/10))%10*10 + i/100);
	// maybe buggy


	int n = 40000;
	int m = ps.size();
	dp = vector<int>(n+1, 0);
	dp[0] = 1;

	for(int i=1;i<m;i++){
		for(int k=0;k<=n;k++){
			if(k>=ps[i]){
				dp[k] += dp[k-ps[i]];
				dp[k] %= MOD;
			}
		}
	}

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--) solve();
}