#include<vector>
#include<algorithm>
#include<assert.h>
#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<'\n'
#define inf 1000000
#define N 50000
#define N1 50001
#define N2 50002
#define N3 50003


inline void solve(){

	int n; cin >> n;
	//const int N = 50000;

	vector<vector<pair<int,int> > > adj(N2);
	//for(int i=0;i<N2;i++) adj[i].reserve(16);

	int dist[N2];
	fill(dist, dist+N2, 0);

	for(int i=0;i<n;i++){
		int a, b, c; cin >> a >> b >> c;
		a++; b++;

		adj[b].pb(mp(a-1,-c));
	}
	for(int i=0;i<=N;i++) adj[i+1].pb(mp(i,0));
	for(int i=0;i<=N;i++) adj[i].pb(mp(i+1,1));

	int pq[N3];
	int back = 0;
	int front = 0;
	//fill(pq, pq+N+3, -1);
	//queue<int> pq;



	for(int i=N1;i>=0;i--) {
		pq[back++] = i;
		back %= N3;
	}
	// pq.push(i);
	//pq.push(0);
	bool active[N2];
	memset(active, 1, sizeof(active));
	//fill(active, active+N2, 1);

	//int c = 0;
	while(back != front){
		int j = pq[front++];
		front %= N3;
		active[j] = false;
		for(int k=0; k<adj[j].size(); k++){
			int id = adj[j][k].first;
			int w = adj[j][k].second;
			//c++;
			if(dist[id] > dist[j] + w){
				dist[id] = dist[j] + w;
				if(!active[id]){
					active[id] = true;
					pq[back++] = id;
					back %= N3;
					//push(id);
				}
			}
		}
	} // what does shortest path mean in this context?
	print(dist[N1]-dist[0]);
	//print(c);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}






/*

s[bi] - s[ai-1] >= c

// we need ... <= ... for shortest path

s[ai-1] - s[bi] <= -c

if also have

s[ai] <= s[aj] if j > i

so, we have

s[ai] - s[aj] <= 0

finally, we have

s[ai+1] <= s[ai]+1
this translates into
s[ai+1] - s[ai] <= 1 


Now it's not a good system of inequality if there's no connectivity



*/






