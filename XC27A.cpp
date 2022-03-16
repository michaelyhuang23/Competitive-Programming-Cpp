#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl

int n, m; 
vector<vector<pair<int,int>>> adj;
vector<vector<int>> pd;
vector<int> labels, edlabels;
vector<int> label2id;

inline int countBit(int num){
	for(int i=0;i<32;i++) if((1<<i) > num) return i;
	return -1;
}

inline bool bitContain(int a, int b, int la, int lb){
	if(la>lb) return false;
	// check if a is contained in b as prefix
	a <<= (lb-la);
	int diff = a ^ b;
	diff >>= (lb-la);
	return diff == 0; // this is sketchy, check!
}
int cc = 0;

void label(int cur){
	if(cur>n) return;
	labels[cur]=cc++;
	label2id[labels[cur]] = cur;
	label(cur*2);
	label(cur*2+1);
    edlabels[cur]=cc;
}

bool  isall1(int num){
    bool suc=true;
    int len = countBit(num);
    for(int i=0;i<len;i++) suc = suc && ((num >> i)&1);
    return suc;
}

void dfs(int cur){
    if(cur>n) return;
	int len = countBit(cur);
	
	int stlabel = labels[cur], edlabel = edlabels[cur]-1;
	int subtreesize = edlabel - stlabel + 1;


	vector<int> dist(subtreesize, inf);
	dist[0] = 0;
	priority_queue<pair<int,int>> pq;
	pq.push(mp(0,cur));
	for(int i=1;i<len;i++){
		pq.push(mp(pd[cur][i], cur>>(len-i)));
	}

	while(!pq.empty()){
		auto& elem = pq.top(); pq.pop();
		int w = elem.first;
		int id = elem.second;
		int l = countBit(id);
		
		if(bitContain(id, cur, l, len) && id != cur){
			// id is parent
			int padist = pd[cur][l];
			for(auto& edge : adj[id]){
				int id2=edge.first;
				int w=edge.second;
				int l2=countBit(id2);
				if(!bitContain(cur, id2, len, l2)) continue;
				// must go back down to a children

				int loc2=labels[id2]-stlabel;
				if(dist[loc2]>padist+w){
					dist[loc2] = padist+w;
					pq.push(mp(dist[loc2], id2));
				}
			}
		}else{
			int loc = labels[id]-stlabel;
			for(auto& edge : adj[id]){
				int id2=edge.first;
				int w=edge.second;
				int l2=countBit(id2);
				if(!bitContain(cur, id2, len, l2)) continue;
				// only look at children
				int loc2=labels[id2]-stlabel;
				if(dist[loc2]>dist[loc]+w){
					dist[loc2] = dist[loc]+w;
					pq.push(mp(dist[loc2], id2));
				}				
			}
		}
	}


	for(int i=0;i<subtreesize;i++){
		int id = label2id[i+stlabel];
		pd[id][len] = dist[i];
	}


	dfs(cur*2);
	dfs(cur*2+1);
}

void solve(){
	cin >> n >> m;
	adj = vector<vector<pair<int,int>>>(n+1, vector<pair<int,int>>());
	pd = vector<vector<int>>(n+1, vector<int>());
	for(int i=1;i<=n;i++){
		pd[i] = vector<int>(countBit(i)+1,inf);
	}
	for(int i=0;i<m;i++){
		int u, v, w; cin >> u >> v >> w;
		adj[u].pb(mp(v,w));
		adj[v].pb(mp(u,w));
	}
	cc = 0;
	label2id = vector<int>(n,-1);
	labels = vector<int>(n+1,-1);
    edlabels = vector<int>(n+1, -1);
	label(1);

    //deb(labels)
	dfs(1);


	//deb(pd)

	int q; cin >> q;

	for(int i=0;i<q;i++){
		int u, v; cin >> u >> v;
		int pu = u, pv = v;
		int lu = countBit(u);
		int lv = countBit(v);
		if(lv > lu){
			v >>= lv-lu;
		}else if(lu > lv){
			u >>= lu-lv;
		}
		while(u!=v) {
			u>>=1;
			v>>=1;
		}
		int minD = inf;
		for(int x = u; x>0; x>>=1){
			int len = countBit(x);
			minD = min(minD, pd[pu][len] + pd[pv][len]);
		}
		if(minD>inf/2) print(-1);
		else print(minD);
	}
}


int main(){

    //deb(bitContain(2,1,2,1))
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}