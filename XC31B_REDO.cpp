#include<bits/stdc++.h>

using namespace std;

#define print(x) cout<<x<<endl


void solve(){
	int n; cin >> n;
	vector<int> P(n+1,inf);
	for(int i=1;i<=n;i++) cin >> P[i];

	priority_queue<int,vector<int>,greater<int>> slopedp;
	vector<int> finalVal(n+1);
	// initialize

	for(int i=1;i<=n;i++){
		// f[i](x) = max(f[i-1](x), f[i-1](x-1)-p, f[i+1](x+1)+p)
		slopedp.push(-P[i]);
		slopedp.push(-P[i]);
		slopedp.pop();
		finalVal-=P[i];
	}

	vector<int> changes(slopedp.begin(),slopedp.end());
	for(int c : changes)
		finalVal -= c;
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