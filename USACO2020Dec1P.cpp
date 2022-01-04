#include<algorithm>
#include<iostream>
#include<vector>
#include<fstream>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;

#define MOD 1000000007LL
#define pb push_back
#define mp make_pair
#define mt make_tuple

llong dp[5][6005][2]; // change back

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n; cin>>n;
	vector<int> ss(n);
	vector<int> tt(n);
	for(int i=0;i<n;i++) cin >> ss[i];
	for(int i=0;i<n;i++) cin >> tt[i];
	vector<pair<int, bool> > ptrs;
	for(int i=0;i<n;i++) ptrs.pb(mp(ss[i],0));
	for(int i=0;i<n;i++) ptrs.pb(mp(tt[i],1));
	ptrs.pb(mp(-1,-1));
	sort(ptrs.begin(), ptrs.end()); 
	//deb(ptrs);
	// dp init
	int in = 0, pi = 0;
	for(int i=0;i<5;i++) for(int k=0;k<6005;k++) {dp[i][k][0]=0; dp[i][k][1]=0;}
	dp[0][0][0] = 1;
	for(int i=1; i<=2*n; i++){
		in = i%2;
		pi = (i+1)%2;
		for(int k=0;k<6005;k++) {dp[in][k][0] = 0; dp[in][k][1] = 0; }
		int v = ptrs[i].first;
		for(int k=0; k<=2*n; k++){
			if(!ptrs[i].second){ // cow
				if(k-1 >= 0) dp[in][k][0] = dp[pi][k-1][0];
				else dp[in][k][0] = 0;
				if(k-1 >= 0) dp[in][k][1] = (dp[pi][k][1] + dp[pi][k-1][1])%MOD;
				else dp[in][k][1] = (dp[pi][k][1])%MOD;
				dp[in][k][1] += dp[pi][k][0]; 
				//if(ptrs[i-1].first < ptrs[i].first) 
				// this is not necessary condition, we can decide to break whenever.
				dp[in][k][1] %= MOD;
			}else{ // barn
				// barn shouldn't allow inter transition
				dp[in][k][0] = (dp[pi][k+1][0]*(k+1) + dp[pi][k][0])%MOD;
				dp[in][k][1] = (dp[pi][k+1][1]*(k+1))%MOD;// overflow here
			}
		}
		// if(ptrs[i].second) cout<<"b "<<ptrs[i].first<<endl;
		// else cout<<"a "<<ptrs[i].first<<endl;
		// for(int k=0; k<=2*n; k++) cout<<dp[in][k][0]<<" ";
		// cout<<endl;
		// for(int k=0; k<=2*n; k++) cout<<dp[in][k][1]<<" ";
		// cout<<endl;
		// cout<<endl;
	}
	llong total = (dp[in][0][0] + dp[in][0][1])%MOD;
	cout<<total<<endl;
}






