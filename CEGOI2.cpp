#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define inf 1000000000000000LL

void solve(){
	int n; cin >> n;
	vector<vector<llong>> diff(n, vector<llong>(n));
	for(llong i=0;i<n;i++){
		for(llong j=i;j<n;j++){
			cin >> diff[i][j];
			diff[j][i] = diff[i][j];
		}
	}

	vector<llong> brr(n); brr[0]=0;
	for(llong i=1;i<n;i++){
		llong p1 = brr[i-1]+diff[i-1][i];
		brr[i] = p1;
		bool suc = true;
		llong minn = inf, maxx = -inf;
		for(llong j=i;j>=0;j--){
			minn = min(minn, brr[j]);
			maxx = max(maxx, brr[j]);
			suc &= maxx-minn == diff[j][i];
		}
		if(suc) continue;
		
		llong p2 = brr[i-1]-diff[i-1][i];
		brr[i] = p2;
		suc = true;
		minn = inf; maxx = -inf;
		for(llong j=i;j>=0;j--){
			minn = min(minn, brr[j]);
			maxx = max(maxx, brr[j]);
			suc &= maxx-minn == diff[j][i];
		}
		if(suc) continue;

		assert(false);
	}

	for(int i=0;i<n-1;i++) cout<<brr[i]<<" ";
	cout<<brr[n-1]<<endl;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}
