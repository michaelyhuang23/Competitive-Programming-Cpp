#include "debughelp.hpp"
#include<bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 1000000000

int n;
vector<vector<pair<int,int>>> adj;
vector<priority_queue<int>> pqs;
vector<vector<int>> fpqs;
vector<int> lx,ly,lslope;

void dfs(int i, int pi){
	if(adj[i].size()==1 && i!=pi){ // leaf
		pqs[i].push(adj[i][0].second);
		pqs[i].push(adj[i][0].second);

		fpqs[i].pb(adj[i][0].second);
		fpqs[i].pb(adj[i][0].second);

		lx[i]=adj[i][0].second;
		ly[i]=0;
		lslope[i]=1;
		return;
	}

	for(auto& edge : adj[i]){
		int ci = edge.first;
		if(ci == pi) continue;
		int w = edge.second;
		dfs(ci, i);
		if(pqs[i].size() < pqs[ci].size()){
			swap(pqs[i], pqs[ci]);
			swap(fpqs[i], fpqs[ci]);
		}
		if(lx[i]<lx[ci]){
			swap(lx[i],lx[ci]);
			swap(lslope[i],lslope[ci]);
			swap(ly[i],ly[ci]);
		}
		// assert(lslope[i]==0 && lslope[ci]==0);
		int dx=lx[i]-lx[ci];
		int dy=lslope[ci]*dx+ly[ci];
		ly[i]+=dy;
		lslope[i]+=lslope[ci];

		while(!pqs[ci].empty()){
			pqs[i].push(pqs[ci].top());
			fpqs[i].pb(pqs[ci].top());
			pqs[ci].pop();
		}
	}
	sort(fpqs[i].begin(), fpqs[i].end());
	while(lslope[i]>0){
		int ltx = pqs[i].top(); pqs[i].pop();
		fpqs[i].pop_back();
		assert(ltx == lx[i]);
		int lltx = pqs[i].top();
		ly[i] = ly[i] - (lx[i]-lltx)*lslope[i];
		lx[i] = lltx;
		lslope[i]--;
	}
	deb(i)
	deb(fpqs[i])
	deb(mt(lx[0],ly[0],lslope[0]))
}

void solve(){
	int N, M; cin >> N >> M;
	n = N+M;
	adj = vector<vector<pair<int,int>>>(n);
	pqs = vector<priority_queue<int>>(n);
	fpqs = vector<vector<int>>(n);
	lslope = vector<int>(n,0);
	lx = vector<int>(n,0);
	ly = vector<int>(n,0);
	for(int i=1;i<n;i++){
		int p, c; cin >> p >> c; p--;
		adj[p].pb(mp(i,c));
		adj[i].pb(mp(p,c));
	}

	dfs(0,0);
	int minC = inf;
	deb(mt(lx[0],ly[0],lslope[0]))
	while(!pqs[0].empty()){
		minC = min(minC, ly[0]);
		int ltx = pqs[0].top(); pqs[0].pop();
		assert(ltx == lx[0]);
        if(pqs[0].empty()) break;
		int lltx = pqs[0].top();
		ly[0] = ly[0] - (lx[0]-lltx)*lslope[0];
		lx[0] = lltx;
		lslope[0]--;
		minC = min(minC, ly[0]);
	}

	print(minC);
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();
}