#include<bits/stdc++.h>


using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define MOD 1000000007LL
#define inf 100000000000000000LL
#define print(x) cout<<x<<endl

llong n, m, s, t;
vector<vector<pair<llong,llong>>> adj;

// vector<llong> normal_djikstra(llong source){
// 	vector<llong> dist(n, inf);
// 	vector<bool> visited(n, false);
// 	priority_queue<pair<llong,llong>, vector<pair<llong,llong>>, greater<pair<llong,llong>>> pq;
// 	pq.push(mp(0, source));
// 	dist[source] = 0;

// 	while(!pq.empty()){
// 		auto elem = pq.top(); pq.pop();
// 		llong id = elem.second;
// 		if(visited[id]) continue;
// 		visited[id]=true;
// 		for(auto& edge : adj[id]){
// 			llong to = edge.first;
// 			llong w = edge.second;
// 			if(dist[id]+w < dist[to]){
// 				dist[to] = dist[id]+w;
// 				pq.push(mp(dist[to], to));
// 			}
// 		}
// 	}

// 	return dist;
// }

void correct(llong& val){
	val = (val+MOD)%MOD;
}

vector<pair<llong,llong>> special_djikstra(llong source){
	vector<pair<llong, llong>> dist(n, mp(inf, 0));
	vector<bool> visited(n, false);
	priority_queue<pair<llong,llong>, vector<pair<llong,llong>>, greater<pair<llong,llong>>> pq;
	pq.push(mp(0, source));
	dist[source] = mp(0, 1);

	while(!pq.empty()){
		auto elem = pq.top(); pq.pop();
		llong id = elem.second;
		if(visited[id]) continue;
		visited[id]=true;
		for(auto& edge : adj[id]){
			llong to = edge.first;
			llong w = edge.second;
			if(dist[id].first+w < dist[to].first){
				dist[to] = mp(dist[id].first+w, dist[id].second);
				pq.push(mp(dist[to].first, to));
			}else if(dist[id].first+w == dist[to].first){
				dist[to].second+=dist[id].second; 
				dist[to].second = (dist[to].second+MOD)%MOD;
			}
		}
	}

	return dist;
}

llong power(llong num, llong pow){
	if(pow==0) return 1;
	if(pow%2==0){
		llong mid = power(num, pow/2);
		return ((mid*mid)%MOD+MOD)%MOD;
	}else{
		return ((power(num, pow-1)*num)%MOD+MOD)%MOD;
	}
}

llong inverse(llong num){
	return power(num, MOD-2);
}

llong choose(llong n, llong k){
	if(k>n) return 0;
	llong num = 1;
	for(llong i=n; i>=n-k+1; i--) num=((num*i)%MOD+MOD)%MOD;
	llong den = 1;
	for(llong i=k; i>=1; i--) den=((den*inverse(i))%MOD+MOD)%MOD;
	return ((num*den)%MOD+MOD)%MOD;
}

void solve(){
	cin >> n >> m;
	cin >> s >> t;
	s--; t--;
	adj = vector<vector<pair<llong, llong>>>(n, vector<pair<llong,llong>>());
	vector<tuple<int,int,llong>> edges;
	for(llong i=0;i<m;i++){
		llong a, b, w; cin >> a >> b >> w;
		a--; b--;
		adj[a].pb(mp(b,w));
		adj[b].pb(mp(a,w));
		edges.pb(mt(a,b,w));
	}

	vector<pair<llong,llong>> distS = special_djikstra(s);
	vector<pair<llong,llong>> distT = special_djikstra(t);

	// you see old-sport, any vertex with the same time to s as to t cannot work because it's an interception
	// so we simply mark those vertices and deal with the paths created from them. 

	llong w = distS[t].first;
	llong c = distS[t].second;
	//assert(c>0);
	for(int i=0;i<n;i++){
		assert(distS[i].first < inf);
		assert(distT[i].first < inf);
	}

	assert(w == distT[s].first);
	assert(c == distT[s].second);

	llong total = choose(c,2)%MOD; // we need to *2 at the end for the permutation of the paths

	llong totalEC = 0;
	for(llong i=0;i<n;i++){
		if(distS[i].first*2 == w && distT[i].first*2 == w){
			assert(distS[i].first + distT[i].first == w); // this could be a bad point
			llong ec = (distS[i].second * distT[i].second)%MOD;
			totalEC += ec;
			totalEC %= MOD;
			// non of these edges can be paired within this group
			total -= choose(ec, 2);
			total = (total+MOD)%MOD;
		}
	}

	for(int i=0;i<edges.size();i++){
		int a = get<0>(edges[i]);
		int b = get<1>(edges[i]);
		llong weight = get<2>(edges[i]);
		if(distS[b].first < distS[a].first) swap(a,b);
		// assume a --> b when going from s --> t
		// collision condition
		if(distS[a].first < distT[a].first && distS[b].first > distT[b].first){
			if(distS[a].first + weight + distT[b].first == w){
				llong ec = (distS[a].second * distT[b].second)%MOD;
				totalEC += ec;
				totalEC %= MOD;
				// non of these paths can with one another
				total -= choose(ec, 2);
				total = (total+MOD)%MOD;
			}
		}
	}

	//assert(totalEC <= c);
	
	total *= 2;
	total = (total+MOD)%MOD;
	assert(total>=0);
	print(total);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	while(tt--) solve();
}