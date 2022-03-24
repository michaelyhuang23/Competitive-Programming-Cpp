
#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define print(x) cout<<x<<endl
#define inf 1000000000

void solve(){
	llong n; cin >> n;
	vector<llong> P(n+1,inf);
	for(llong i=1;i<=n;i++) cin >> P[i];

	priority_queue<llong> slopedp;
	// vector<llong> dp;
	llong finalVal = 0;
	// slopedp.push(0);
	// dp.push_back(0);
	// initialize

	for(llong i=1;i<=n;i++){
		// f[i](x) = max(f[i-1](x), f[i-1](x-1)-p, f[i+1](x+1)+p)
		slopedp.push(-P[i]);
		slopedp.push(-P[i]);
		slopedp.pop();

		// dp.push_back(-P[i]);
		// dp.push_back(-P[i]);
		// sort(dp.begin(),dp.end(),less<llong>());
		// dp.pop_back();
		// sort(dp.begin(),dp.end(),greater<llong>());
		// deb(dp)
		finalVal-=P[i];
	}
	// deb(finalVal)

	while(!slopedp.empty()){
		llong c = slopedp.top(); slopedp.pop();
		finalVal -= c;
	}

	print(finalVal);
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}

/*

Gameplan:
1. Build Slope DP:
	1. Record the slope of each segment (between each pair of data ptrs)
	2. Record the final data ptr


*/