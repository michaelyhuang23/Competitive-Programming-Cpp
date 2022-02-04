#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<'\n'
#define MOD 1000000007LL

llong N, No, Ne;
vector<llong> heights;
vector<llong> front;
vector<llong> back;
vector<llong> odds, evens; // storing their positions

void preprocess(){
	odds = vector<llong>();
	evens = vector<llong>();
	odds.pb(0);
	evens.pb(0);

	for(llong i=1;i<=N;i++){
		llong h = heights[i];
		if(h%2 == 1) odds.pb(i);
		else evens.pb(i);
	}

	No = odds.size()-1;
	Ne = evens.size()-1;

	front = vector<llong>(Ne+1, 0); // mind initialization
	back = vector<llong>(Ne+1, No+2);

	for(llong i=1;i<=Ne;i++){
		auto it = lower_bound(odds.begin(), odds.end(), evens[i]);
		assert(it != odds.begin());
		it = prev(it);
		llong fr = distance(odds.begin(), it);
		for(;fr>=1;fr--){
			if(abs(heights[odds[fr]]-heights[evens[i]])>1) {
				front[i] = fr+1;
				break;
			}
		}

		it = upper_bound(odds.begin(), odds.end(), evens[i]);
		llong en = distance(odds.begin(), it);
		for(;en<=No;en++){
			if(abs(heights[odds[en]]-heights[evens[i]])>1) {
				back[i] = en;
				break;
			}
		}

	}

	// deb(front)
	// deb(back)
}

void solve(){
	cin >> N;
	heights = vector<llong>(N+1);
	for(llong i=1;i<=N;i++) cin >> heights[i];
	preprocess();
	
	vector<vector<llong>> dp(Ne+1, vector<llong>(No+2,0));
	vector<vector<llong>> pdp(Ne+1, vector<llong>(No+2,0));
	dp[0][0] = 1;
	for(llong po=0;po<=No+1;po++) pdp[0][po] = 1;
	

	for(llong i=1;i<=Ne;i++){
		for(llong po=1;po<=No+1;po++){
			if(front[i]<=po && po<=back[i]){
				dp[i][po] = pdp[i-1][po];
				// something feels fishy about hte transition
			}
			pdp[i][po] = (pdp[i][po-1] + dp[i][po])%MOD;
		}
	}
	// deb(dp[1])
	// deb(dp[2])
	print(pdp[Ne][No+1]%MOD);
}












int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	while(tt--) solve();
}

