#include<bits/stdc++.h>

using namespace std;
#define print(x) cout<<x<<endl


void solve(){
	int n; cin >> n;
	vector<int> A(n+1);
	for(int i=1;i<=n;i++) cin >> A[i];
	string Ks; cin >> Ks;
	vector<int> K(Ks.size()+2,2);

	for(int i=0;i<Ks.size();i++)
		K[i+1] = (Ks[i]=='U') ? 1 : 0;

	vector<int> dp(n+1,0);
	for(int i=2;i<=n;i++){
		// update for U
		for(int j=1;j<i;j++){
			if(K[dp[j]+1]==1 && A[i]>A[j]){
				dp[i] = max(dp[i], dp[j]+1);
			}
		}

		// update for D
		for(int j=1;j<i;j++){
			if(K[dp[j]+1]==0 && A[i]<A[j]){
				dp[i] = max(dp[i], dp[j]+1);
			}
		}
	}

	int maxK = 0;
	for(int i=1;i<=n;i++) maxK = max(maxK, dp[i]);

	print(maxK);
}









int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}