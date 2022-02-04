#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<'\n'

llong N;
vector<vector<pair<llong,llong>>> vecs;
vector<pair<llong,llong>> frontier;
llong maxd = 0;

void bfs1(llong i){
	vector<pair<llong,llong>> nfrontier;
	for(auto loc : frontier){
		for(llong c=0;c<vecs[i].size();c++){
			pair<llong,llong> nloc = mp(loc.first+vecs[i][c].first, loc.second+vecs[i][c].second);
			nfrontier.pb(nloc);
		}
	}
	sort(nfrontier.begin(), nfrontier.end());
	deque<pair<llong,llong>> mono;
	for(llong i=0;i<nfrontier.size();i++){
		while(!mono.empty() && mono.back().second<nfrontier[i].second) mono.pop_back();
		mono.pb(nfrontier[i]);
	}
	frontier = vector<pair<llong,llong>>(mono.begin(), mono.end());
}


void solve(){
	cin >> N;
	vecs = vector<vector<pair<llong,llong>>>(N, vector<pair<llong,llong>>());
	for(llong i = 0;i < N;i++){
		llong c; cin >> c;
		vecs[i] = vector<pair<llong,llong>>(c);
		for(llong j=0;j<c;j++) {
			llong a, b; cin >> a >> b;
			vecs[i][j] = mp(a,b);
		}
	}

	frontier = vector<pair<llong,llong>>();
	frontier.pb(mp(0,0));
	for(llong i=0;i<N;i++){
		bfs1(i);
	}
	for(auto loc : frontier){
		maxd = max(maxd, loc.first*loc.first + loc.second*loc.second);
	}

	// frontier = vector<pair<llong,llong>>();
	// frontier.pb(mp(0,0));
	// for(llong i=0;i<N;i++){
	// 	bfs2(i);
	// }
	// for(auto loc : frontier){
	// 	maxd = max(maxd, loc.first*loc.first + loc.second*loc.second);
	// }

	// frontier = vector<pair<llong,llong>>();
	// frontier.pb(mp(0,0));
	// for(llong i=0;i<N;i++){
	// 	bfs3(i);
	// }
	// for(auto loc : frontier)
	// 	maxd = max(maxd, loc.first*loc.first + loc.second*loc.second);
	// }

	// frontier = vector<pair<llong,llong>>();
	// frontier.pb(mp(0,0));
	// for(llong i=0;i<N;i++){
	// 	bfs4(i);
	// }
	// for(auto loc : frontier){
	// 	maxd = max(maxd, loc.first*loc.first + loc.second*loc.second);
	// }


	print(maxd);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
	//print(242);
}