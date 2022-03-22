// #define _GLIBCXX_DEBUG 1

#include<bits/stdc++.h>


using namespace std;
#define mt make_tuple
#define pb push_back
#define mp make_pair
#define inf 1000000000
#define print(x) cout<<x<<endl

int n, m, C, T;
int maxD, maxC;
vector<int> Ps,Cs;
vector<vector<pair<int,int>>> adj;
vector<int> Ss, Qs, Ds;

void bellmanford(int s, vector<vector<vector<int>>>& mincost){
	mincost[s][0][0] = 0;
	for(int t=0;t<maxD*2;t++){
		for(int id=0;id<n;id++){
			for(int d=0;d<=maxD;d++){
				for(int c=0;c<=maxC;c++){
					int cost = mincost[id][d][c]; 
					int cn = Cs[id];
					mincost[id][d][cn] = min(mincost[id][d][cn], cost + Ps[id]);
					if(c>0){
						for(auto& edge : adj[id]){
							int to = edge.first;
							int w = edge.second;
							int pd = min(d+w,maxD+1); 
							if(mincost[to][pd][c-1] > cost){
								mincost[to][pd][c-1] = cost;
							}
						}
					}
				}
			}
		}
	}
}

void djikstra(int s, vector<vector<vector<int>>>& mincost){
	// vtx, dist, fuel
	mincost[s][0][0] = 0;
	priority_queue<tuple<int,int,int,int>, vector<tuple<int,int,int,int>>, greater<tuple<int,int,int,int>>> pq;
	// cost id dist fuel
	pq.push(mt(0,s,0,0));
	vector<vector<vector<bool>>> visited(n,vector<vector<bool>>(maxD+2, vector<bool>(maxC+1,0)));

	while(!pq.empty()){
		auto ret = pq.top(); pq.pop();
		int id = get<1>(ret);
		int c = get<3>(ret);
		int d = get<2>(ret);
		int cost = get<0>(ret);

		// assert(!visited[id][d][c]);
		// visited[id][d][c] = true;

		if(d > maxD) continue;
		// deb(mt(id, d, c, cost))
		cost = mincost[id][d][c];
		if(c>0){
			for(auto& edge : adj[id]){
				int to = edge.first;
				int w = edge.second;
				int pd = min(d+w,maxD+1); 
				if(mincost[to][pd][c-1] > cost){
					mincost[to][pd][c-1] = cost;
					pq.push(mt(cost, to, pd, c-1));
				}
			}
		}

		int nc = Cs[id];
		if(mincost[id][d][nc] > cost + Ps[id]){
			mincost[id][d][nc] = cost + Ps[id];
			pq.push(mt(cost+Ps[id], id, d, nc));
		}
	}
}

void solve3(){
	vector<vector<vector<vector<int>>>> mincost(n, vector<vector<vector<int>>>(n, vector<vector<int>>(maxD+2,vector<int>(maxC+1,inf))));
	for(int i=0;i<n;i++){
		djikstra(i, mincost[i]);
	}


	for(int i=0;i<T;i++){
		int minC = inf;
		for(int t=0;t<n;t++){
			for(int d=Ds[i];d<=maxD+1;d++){
				for(int c=0;c<=maxC;c++){
					minC = min(minC,mincost[Ss[i]][t][d][c]);
				}
			}
		}
		if(minC > Qs[i]) print(-1);
		else print(Qs[i] - minC);
	}
}

void solve2(){

}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> C >> T;
	Ps = vector<int>(n);
	Cs = vector<int>(n);
	maxC = 0;
	for(int i=0;i<n;i++){
		int p,c; cin >> p >> c;
		Ps[i] = p;
		Cs[i] = min(C,c);
		maxC = max(maxC, Cs[i]);
	}
	adj = vector<vector<pair<int,int>>>(n);
	for(int i=0;i<m;i++){
		int a,b,l; cin >> a >> b >> l;
		a--; b--;
		adj[a].pb(mp(b,l));
		adj[b].pb(mp(a,l));
	}
	Ss = vector<int>(T);
	Qs = vector<int>(T);
	Ds = vector<int>(T);
	maxD = 0;
	for(int i=0;i<T;i++){
		int s,q,d; cin >> s >> q >> d;
		s--;
		Ss[i] = s;
		Qs[i] = q;
		Ds[i] = d;
		maxD = max(d,maxD);
	}
	// deb(maxD)
	// deb(maxC)
	if(maxD <= 1000){
		maxD += 100;
		solve3();
	}
	else 
		solve2();
}