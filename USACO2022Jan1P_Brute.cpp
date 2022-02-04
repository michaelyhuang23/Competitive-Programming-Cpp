#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<'\n'

/*

brute force topological sort

*/

int N, K;
vector<int> heights;
vector<int> deg;
vector<vector<int>> adj;

void solve(){
	cin >> N >> K;
	heights = vector<int>(N);
	adj = vector<vector<int>>(N, vector<int>());
	deg = vector<int>(N,0);
	for(int i=0;i<N;i++) cin >> heights[i];

	for(int i=0;i<N;i++){
		for(int j=i+1;j<N;j++){
			if(abs(heights[j]-heights[i]) > K){
				adj[i].pb(j);
				deg[j]++;
			}
		}
	}

	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
	// first = height
	// second = pos

	// init
	for(int i=0;i<N;i++){
		if(deg[i] == 0) pq.push(mp(heights[i],i));
	}

	vector<int> result;

	while(!pq.empty()){
		auto item = pq.top();
		pq.pop();
		int h = item.first;
		int id = item.second;
		result.pb(h);
		for(int cid : adj[id]){
			deg[cid]--;
			if(deg[cid] == 0){
				pq.push(mp(heights[cid],cid));
			}
		}
	}

	assert(result.size() == N);

	for(int i=0;i<N;i++) print(result[i]);

}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();
}
