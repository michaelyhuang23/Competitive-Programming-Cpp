// #include "debughelp.hpp"


#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000000000LL
#define print(x) cout<<x<<endl

llong n,a,b;
vector<llong> arr;
vector<llong> psum;
const llong D = 43;

void solve_permute(){
	arr = vector<llong>(n);
	for(llong i=0;i<n;i++) cin>>arr[i];


	llong minn = inf;
	for(llong x=a;x<=b;x++){
		llong maxS=1<<(n-1);
		llong k = x-1;
		for(llong s=0;s<maxS;s++){
			llong cc = __builtin_popcount(s);
			if(cc != k) continue;
			llong ps = 0;
			vector<llong> sums;
			for(llong b=0;b<n;b++){
				ps += arr[b];
				if(s & (1<<b)){
					sums.pb(ps);
					ps = 0;
				}
			}
			// assert(ps!=0);
			sums.pb(ps);
			// assert(sums.size() == x);
			llong total = 0;
			for(llong v : sums) total |= v;
			minn = min(minn, total);
		}
	}
	print(minn);
}

bool check(llong pref, llong d){
	vector<vector<bool>> dp(n+1, vector<bool>(n+1, 0));
	// x, i
	dp[0][0] = 1;

	for(llong x=1;x<=n;x++){
		for(llong i=1;i<=n;i++){
			for(llong ip=0;ip<i;ip++){
				llong sum = psum[i]-psum[ip];
				// deb(mt(i,ip,sum))
				dp[x][i] = dp[x][i] || (dp[x-1][ip] && ((sum>>d) | (pref>>d))==(pref>>d));
			}
		}
	}

	// deb(dp)

	bool work = false;
	for(llong x=a;x<=b;x++) {
		work |= dp[x][n];
		// if(work) deb(x);
	}
	return work;
}

void solve_dp(){
	arr = vector<llong>(n+1);
	psum = vector<llong>(n+1,0);
	for(llong i=1;i<=n;i++) cin>>arr[i];
	for(llong i=1;i<=n;i++) psum[i] = psum[i-1] + arr[i];


	// deb(check(4, 1))

	llong pref = 0;
	for(llong d=D-1;d>=0;d--){
		if(!check(pref,d)) pref ^= 1LL<<d;
	}

	print(pref);

}

bool check2(llong pref, llong d){
	vector<llong> dp(n+1, inf);
	// i
	dp[0] = 0;

	for(llong i=1;i<=n;i++){
		for(llong ip=0;ip<i;ip++){
			llong sum = psum[i]-psum[ip];
			if(((sum>>d) | (pref>>d))==(pref>>d)) // submask of pref:
				dp[i] = min(dp[i], dp[ip]+1);
		}
	}

	// deb(dp)

	bool work = dp[n]<=b;
	return work;
}

void solve_dp2(){
	assert(a==1);
	arr = vector<llong>(n+1);
	psum = vector<llong>(n+1,0);
	for(llong i=1;i<=n;i++) cin>>arr[i];
	for(llong i=1;i<=n;i++) psum[i] = psum[i-1] + arr[i];


	// deb(check(4, 1))

	llong pref = 0;
	for(llong d=D-1;d>=0;d--){
		if(!check2(pref,d)) pref ^= 1LL<<d;
	}

	print(pref);

}


void solve(){
	cin >> n >> a >> b;

	if(a==1)
		solve_dp2();
	else 
		solve_dp();
}




int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}