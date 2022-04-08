#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl

void solve(){
	int n,a,b; cin >> n >> a >> b;

	int maxmid = 0;
	int needOdd = 0; // 1 yes, 2 no

	for(int i=31;i>=0;i--){
		if((1<<i) & n){
			int cc = 0;
			if((1<<i) & a) cc++;
			if((1<<i) & b) cc++;

			if(cc==1){ // needs even
				if(needOdd == 1){ // we can make it 0/1
					int maxmid1 = maxmid ^ (1<<i);
					int maxmid0 = maxmid;
					int val1 = max(a ^ maxmid1 ^ n, b ^ maxmid1 ^ n);
					int val0 = max(a^maxmid0^n, b^maxmid0^n);
					if(val1 < val0){
						maxmid = maxmid1;
					}else{
						maxmid = maxmid0;
					}
				}else{
					needOdd = 2;
					// no middle
				}
			}else if(cc % 2 == 0){
				if(needOdd == 2){
					// no middle
				}else{
					needOdd = 1;
					if(cc == 0)
						maxmid ^= 1<<i;
					else 
						maxmid ^= 0;
				}
			}
		}else{
			int cc = 0;
			if((1<<i) & a) cc++;
			if((1<<i) & b) cc++;

			if(cc == 1){
				if(needOdd == 1){
					int maxmid1 = maxmid ^ (1<<i);
					int maxmid0 = maxmid;
					int val1 = max(a ^ maxmid1 ^ n, b ^ maxmid1 ^ n);
					int val0 = max(a^maxmid0^n, b^maxmid0^n);
					if(val1 < val0){
						maxmid = maxmid1;
					}else{
						maxmid = maxmid0;
					}
				}else{

				}
			}
		}
	}

	// assert(final <= max(a,b));

	print(final);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--)
		solve();
}