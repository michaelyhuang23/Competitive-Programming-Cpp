#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define inf 1000000000


vector<vector<llong>> adj;
vector<bool> mark;
vector<llong> fa,vals;

llong dfs_mark(llong cur){
	if(mark[cur]) return 0;
	mark[cur] = true;
	llong pa = fa[cur];
	if(pa == cur) return vals[cur];

	return max(dfs_mark(pa), vals[cur]);
}

void solve(llong tt){
	llong n; cin >> n;
	vals = vector<llong>(n+1,0);
	mark = vector<bool>(n+1,0);
	adj = vector<vector<llong>>(n+1);
	for(llong i=1;i<=n;i++) cin >> vals[i];
	fa = vector<llong>(n+1,0);
	for(llong i=1;i<=n;i++) cin >> fa[i];

	for(llong i=1;i<=n;i++) {adj[fa[i]].pb(i); adj[i].pb(fa[i]);}

	vector<llong> idx(n);
	iota(idx.begin(), idx.end(), 1);

	llong maxval = 0;
	do{
		llong val = 0;
		mark = vector<bool>(n+1,0);
		for(llong i : idx){
			if(adj[i].size() == 1 && !mark[i]) // is leaf
				val+=dfs_mark(i);
		}
		maxval = max(maxval, val);
	}while(next_permutation(idx.begin(), idx.end()));
	
	cout<<"Case #"<<tt<<": "<<maxval<<endl;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	for(llong t=1;t<=tt;t++)
		solve(t);
}