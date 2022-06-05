#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define inf 1000000007

int n;
vector<int> vals, costs;
vector<vector<int>> adj;
vector<vector<int>> dpk, dpv;

void solve(){
	cin >> n;
	adj = vector<vector<int>>(n);
	vals = vector<int>(n);
	for(int i=0;i<n;i++) cin >> vals[i];
	costs = vector<int>(n);
	for(int i=0;i<n;i++) cin >> costs[i];

	for(int i=0;i<n-1;i++){
		int a,b; cin >> a >> b; a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	dpk = vector<vector<int>>(n, vector<int>(2,0));
	dpv = vector<vector<int>>(n, vector<int>(2,inf));
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}