#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define inf 4611686018427387904LL
#define print(x) cout << x << endl

struct segtree
{
	static llong pow_up(llong num){
		for(llong i=0;i<65;i++) if(1<<i >= num) return 1<<i;
	}
	vector<llong> tree;
	llong n;
	segtree(){}
	segtree(vector<llong>& arr, llong size){
		// first is right end point
		// second is id
		n = pow_up(size);
		tree = vector<llong>(n*2, -1); 
		copy(arr.begin(), arr.end(), tree.begin()+n); 
		build();
	}
	inline llong op(llong l, llong r){ return max(l, r); }
	inline void build(){
		for(llong i = n-1; i>=1; i--) tree[i] = op(tree[i<<1],tree[i<<1|1]);
	}
	inline void query(llong idx, llong ts, llong te, llong ll, llong rr, vector<llong>& result){
		if(ts == te){
			if(ts<=ll && tree[idx]>=rr) {result.pb(ts); tree[idx]=-1;}
			return;
		}
		llong tm = (ts+te)>>1;
		if(ts<=ll && rr<=tree[idx<<1]) query(idx<<1, ts, tm, ll, rr, result);
		if(tm+1<=ll && rr<=tree[idx<<1|1]) query(idx<<1|1, tm+1, te, ll, rr, result);
		tree[idx] = op(tree[idx<<1], tree[idx<<1|1]);
	}
	inline vector<llong> query(llong ll, llong rr){ 
		vector<llong> result;
		if(rr<=tree[1] && ll>=0) query(1,0,n-1,ll,rr,result);
		return result;
	}
};

llong N, K;
vector<tuple<llong,llong,llong,llong>> edges;

void djikstra(vector<llong>& dist, vector<llong>& distE, vector<llong>& ends){
	segtree etree(ends,N);
	priority_queue<pair<llong,int>, vector<pair<llong,int>>, greater<pair<llong,int>>> pq;
	for(int i=0;i<dist.size();i++) pq.push(mp(dist[i],i));
    //deb(dist)
	vector<bool> visited(N,0);

	while(!pq.empty()){
		auto cur = pq.top(); pq.pop();
		llong cd = cur.first;
        if(cd >= inf/4) break;
		int idx = cur.second;
		visited[idx]=1;
        //deb("query") deb(idx)
        auto ret = upper_bound(edges.begin(), edges.end(), mt(idx,inf,inf,inf)); ret--;
        int eid = distance(edges.begin(), ret);
		vector<llong> es = etree.query(eid, idx); // disable those edges
		for(llong ei : es){
			int ci = get<2>(edges[ei]);
			llong d = get<3>(edges[ei]);
			//deb(cd) deb(ei) deb(distE[ei])
			if(cd>distE[ei]) continue;
			//assert(cd<=distE[ei]);
			if(cd<distE[ei]) {
				distE[ei] = cd;
			}
            // deb(mp(ci, N))
            // deb(cd+d)
            // deb(dist[ci])
            // deb(visited[ci])
			if(cd+d<dist[ci] && (!visited[ci])){
				//deb("set")
				//deb(mp(dist[ci], cd+d))
				dist[ci] = cd+d;
				pq.push(mp(dist[ci], ci));
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> K;
	edges = vector<tuple<llong,llong,llong,llong>>(K);
	for(llong i=0;i<K;i++){
		llong c,p,a,b;
		cin >> c >> p >> a >> b; a--; b--; c--;
		edges[i] = mt(a,b,c,p);
	}
	sort(edges.begin(), edges.end());
	vector<llong> ends(K);
	for(int i=0;i<K;i++){
		auto& edge = edges[i];
		ends[i] = get<1>(edge);
	}

	vector<llong> ends0 = ends;
	vector<llong> dist0(N,inf);
	vector<llong> distE0(K,inf);
	dist0[0] = 0;
	djikstra(dist0,distE0,ends0);

	//deb(dist0[N-1])

	vector<llong> endsN = ends;
	vector<llong> distN(N,inf);
	vector<llong> distEN(K,inf);
	distN[N-1] = 0;
	//deb(distEN)
	djikstra(distN,distEN,endsN);

	//deb(distN[N-1])

	vector<llong> distT(N, inf);
	vector<llong> distET(N, inf);
	for(int i=0;i<N;i++) if(dist0[i]<=inf/4 && distN[i]<=inf/4) distT[i] = dist0[i] + distN[i]; else distT[i]=inf;
	for(int i=0;i<K;i++) if(distE0[i]<=inf/4 && distEN[i]<=inf/4) distET[i] = distE0[i] + distEN[i]; else distET[i]=inf;
	for(int i=0;i<K;i++){
		int t = get<2>(edges[i]);
		llong p = get<3>(edges[i]);
		distT[t] = min(distT[t], distET[i]+p);
	}
	djikstra(distT, distET, ends);

	//deb(distT[N-1])

	for(int i=0;i<N;i++) {
        if(distT[i]>= inf/4) print(-1); else print(distT[i]);
    }
    //deb(distT[N-1])
}







