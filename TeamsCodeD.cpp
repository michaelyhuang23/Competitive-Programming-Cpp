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
	int final = 0;

	int maxmid = 0;

	int needOdd = 0; // 1 yes, 2 need even
	for(int i=31;i>=0;i--){
		if((1<<i) & n){
			int cc = 0;
			if((1<<i) & a) cc++;
			if((1<<i) & b) cc++;

			if(cc == 1){
				if(needOdd == 2 || needOdd == 0){
					needOdd = 2;
				}else{
					final ^= (1<<i);
					// would use 0, maxmid doesn't change					
				}
			}else if(cc % 2 == 0){
				if(needOdd == 1 || needOdd == 0){
					needOdd = 1;
					maxmid ^= (1<<i);
				}else{
					final ^= (1<<i);
				}
			}
		}else{
			int cc = 0;
			if((1<<i) & a) cc++;
			if((1<<i) & b) cc++;

			if(cc==0){
				// do nothing , just all 0
				// maxmid doesn't change
			}else if(cc==1){
				final ^= (1<<i);
				// put 0 to everything, maxmid doesnt' change
			}else if(cc==2){
				// might exceed, idk
				if(needOdd == 1 && (maxmid >> i)==(n >> i)){
					final ^= (1<<i);
				}else{
					maxmid ^= (1<<i);
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