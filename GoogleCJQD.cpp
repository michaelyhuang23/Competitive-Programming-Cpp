#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define inf 10000000000LL

vector<llong> fa,vals,minn,childc;
vector<vector<llong>> adj;
vector<bool> mark;

void dfs_process(llong cur){
	if(adj[cur].size() == 0){
		minn[cur] = vals[cur];
		return;
	}
	minn[cur] = inf;
	for(llong son : adj[cur]){
		dfs_process(son);
		minn[cur] = min(minn[cur], minn[son]);
	}
	minn[cur] = max(minn[cur], vals[cur]);
	// the lowest value path; value of path: max of path.
}

llong dfs(llong cur){
	llong mson = -1, minv = inf;
	mark[cur] = true;
	if(adj[cur].size()==0) return vals[cur];
	for(llong son : adj[cur]){
		if(mark[son]) continue;
		if(minn[son] < minv){
			minv = minn[son];
			mson = son;
		}
	}
	// deb(cur)
	// assert(mson != -1 || adj[cur].size()==0);
	return max(vals[cur], dfs(mson));
}

void mark_fa(llong cur){
	if(mark[cur]) return;
	mark[cur] = true;
	if(cur == 0) return;
	childc[fa[cur]]--;
	if(childc[fa[cur]] == 0) mark_fa(fa[cur]);
}

void solve(llong tt){
	llong n; cin >> n;

	fa = vector<llong>(n+1,0);
	vals = vector<llong>(n+1,0);
	minn = vector<llong>(n+1,0);
	childc = vector<llong>(n+1,0);
	adj = vector<vector<llong>>(n+1);
	mark = vector<bool>(n+1,false);

	for(llong i=1;i<=n;i++) cin >> vals[i];
	for(llong i=1;i<=n;i++) {
		cin >> fa[i];
		adj[fa[i]].pb(i);
	}

	for(llong i=0;i<=n;i++) childc[i] = adj[i].size();


	dfs_process(0);

	vector<pair<llong,llong>> idxs(n);
	for(int i=1;i<=n;i++)
		idxs[i-1] = mp(vals[i],i);

	sort(idxs.rbegin(), idxs.rend());

	// should be in descending order
	llong val = 0;
	for(auto& elem : idxs){
		int i = elem.second;
		if(mark[i]) continue;
		mark_fa(i);
		val += dfs(i);
		// deb(mark)
	}

	cout<<"Case #"<<tt<<": "<<val<<endl;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	for(llong t=1;t<=tt;t++)
		solve(t);
}