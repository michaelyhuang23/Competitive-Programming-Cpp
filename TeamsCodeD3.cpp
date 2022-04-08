#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl

void solve(){
	llong n,a,b; cin >> n >> a >> b;

	llong maxmid = 0;
	llong needOdd = 0; // 1 yes, 2 no

	for(llong i=30;i>=0;i--){
		if((1LL<<i) & n){
			llong cc = 0;
			if((1LL<<i) & a) cc++;
			if((1LL<<i) & b) cc++;

			if(cc==1 && needOdd==0){
				needOdd = 2;
			}else if(cc%2==0 && needOdd==0){
				needOdd = 1;
			}
		}
	}


	if(needOdd == 2 || needOdd == 0){
		print((a^b^n));
		return;
	}

	for(llong i=31;i>=0;i--){
		llong maxmid0 = maxmid;
		llong maxmid1 = maxmid ^ (1LL<<i);

		// deb(maxmid)

		llong val1 = max(a ^ maxmid1 ^ n, b ^ maxmid1 ^ n);
		llong val0 = max(a^maxmid0^n, b^maxmid0^n);

		// deb(mp(val0,val1))
		if(val1 < val0){
			maxmid = maxmid1;
		}else{
			maxmid = maxmid0;
		}
	}
	// assert(final <= max(a,b));

	print(max(a ^ maxmid ^ n, b ^ maxmid ^ n));
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	while(tt--)
		solve();
}