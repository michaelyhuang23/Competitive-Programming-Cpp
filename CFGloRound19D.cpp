#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define print(x) cout<<x<<endl
#define inf 9000000000LL
#define mp make_pair

void solve(){
	llong n; cin >> n;
	vector<llong> arr(n+1,0);
	vector<llong> brr(n+1,0);
	vector<llong> pref(n+1,0);
	vector<llong> pref2(n+1, 0);
	for(llong i=1;i<=n;i++) cin >> arr[i];
	for(llong i=1;i<=n;i++) cin >> brr[i];
	for(llong i=1;i<=n;i++) {
		pref[i] = pref[i-1] + arr[i] + brr[i];
		pref2[i] = pref2[i-1] + arr[i]*arr[i] + brr[i]*brr[i];
	}

	//deb(pref)
	//deb(pref2)


	vector<vector<llong>> dp(n+1, vector<llong>(20005,inf));
	dp[0][0] = 0;
	
	for(llong i=1;i<=n;i++){
		for(llong pa=0;pa<=pref[i];pa++){
			{
				llong a = arr[i];
				llong b = brr[i];
				llong ppa = pa-a;
				llong pb = pref[i]-pa;
				llong ppb = pb-b;

				assert(ppa+ppb == pref[i-1]);

				if(ppa>=0 && ppa<=pref[i-1] && ppb>=0 && ppb<=pref[i-1]) {
					llong addA = 2*a*ppa;
					llong addB = 2*b*ppb;

					llong secA = a*a*(i-1);
					llong secB = b*b*(i-1);

					llong cost = pref2[i-1]+addA+addB+secA+secB;
					assert(cost>=0);
					dp[i][pa] = min(dp[i][pa], dp[i-1][ppa]+cost);
					if(i==1)
					//deb(mp(i, pa))
					// if(dp[i][pa] == 0){
					// 	deb(cost)
					// 	deb(ppa)
					// 	deb(dp[i-1][ppa])
					// 	deb(i-1)
					// }
					assert(dp[i][pa]>=0);
				}
			}

			{
				llong a = arr[i];
				llong b = brr[i];
				llong ppa = pa-b;
				llong pb = pref[i]-pa;
				llong ppb = pb-a;

				assert(ppa+ppb == pref[i-1]);

				if(ppa>=0 && ppa<=pref[i-1] && ppb>=0 && ppb<=pref[i-1]) {

					llong addA = 2*b*ppa;
					llong addB = 2*a*ppb;

					llong secA = b*b*(i-1);
					llong secB = a*a*(i-1);

					llong cost = pref2[i-1]+addA+addB+secA+secB;

					dp[i][pa] = min(dp[i][pa], dp[i-1][ppa]+cost);
					if(i==1)
					//deb(mp(i, pa))
					// if(dp[i][pa] == 0){
					// 	deb(cost)
					// 	deb(ppa)
					// 	deb(dp[i-1][ppa])
					// }
					assert(cost>=0);
					assert(dp[i][pa]>=0);
				}
			}
		}
	}
	//deb(dp[1][59])
	//deb(dp[n][515])
	llong minC = inf;
	for(llong pa = 0; pa <= pref[n]; pa++) minC=min(minC, dp[n][pa]);
	assert(minC>=0);
	print(minC);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	llong tt; cin >> tt;
	while(tt--) solve();
}