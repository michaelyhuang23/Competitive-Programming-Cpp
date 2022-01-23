#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 100000000
#define print(x) cout<<x<<endl

int n,m;
vector<vector<int>> badj;
vector<int> ed, od, dist;
vector<pair<int,int>> dd, sse;

void bfs(int start){
	queue<int> pq;
	pq.push(start);
	dist[start] = 0;
	while(!pq.empty()){
		int c = pq.front();
		pq.pop();
		for(int nei : badj[c]){
			if(dist[nei] > dist[c] + 1) {
				dist[nei] = dist[c] + 1;
				pq.push(nei);
			}
		}
	}
}

void printedge(int a, int b, int c, int d){
	cout<<"("<<a<<", "<<b<<") --> ("<<c<<", "<<d<<")"<<endl;
}

void solve(){
	cin >> n >> m;
	ed = vector<int>(n, inf);
	od = vector<int>(n, inf);
	dist = vector<int>(2*n, inf);
	badj = vector<vector<int>>(2*n);
	for(int i=0;i<m;i++){
		int a, b; cin >> a >> b;
		a--; b--;
		if(a==b){
			badj[a].pb(a+n);
			badj[a+n].pb(a);
			continue;
		}
		badj[a].pb(b+n);
		badj[b+n].pb(a);

		badj[a+n].pb(b);
		badj[b].pb(a+n);
	}

	bfs(0);

	ed = vector<int>(dist.begin(), dist.begin()+n);
	od = vector<int>(dist.begin()+n, dist.end());
	// deb(ed);
	// deb(od);
	dd = vector<pair<int,int>>(n);
	for(int i=0;i<n;i++) dd[i] = mp(min(ed[i],od[i]), max(ed[i],od[i]));
	bool isbi = true;
	for(int i=0;i<n;i++) if(dd[i].second < inf/2) isbi=false;
	if(isbi){
		cout<<n-1<<endl;
		return;
	}

	sort(dd.begin(), dd.end());
	// deb(dd)

	sse = vector<pair<int,int>>(n);
	for(int i=0;i<n;i++) sse[i] = mp(dd[i].first+dd[i].second, dd[i].first);
	sort(sse.begin(), sse.end());

	vector<tuple<int,int,int>> ss;
	pair<int,int> ppr = mp(-1,-1);
	for(int i=0;i<n;i++){
		if(ppr != sse[i]) ss.pb(mt(sse[i].first, sse[i].second, 0));
		get<2>(ss.back())++;
		ppr = sse[i];
	}	

	//deb(ss)
	int N = ss.size();
	vector<unordered_map<int,int>> xtrack(4*n+10);
	int pl = get<0>(ss[0]);
	int prevx = -2;
	int count = 0;
	int s = pl;
	for(int i=0;i<N;i++){
		int j = i;
		xtrack[pl] = unordered_map<int,int>();
		while(s == pl && j<N){
			s = get<0>(ss[j]);
			int x = get<1>(ss[j]);
			int y = s-x;
			if(s!=pl) break;
			xtrack[pl][x] = get<2>(ss[j]);
			j++;
		}
		//deb(pl)
		//deb(xtrack)
		pl = s;
		pair<int,int> req = mp(0,0);
		// [i, j-1] gives the range
		for(int k=i;k<j;k++){
			int su = get<0>(ss[k]);
			int x = get<1>(ss[k]);
			int c = get<2>(ss[k]);
			int y = su-x;
			int half = 0;
			int bhalf = 0;
			int total = 0;
			if(x == 0) half++;
			//deb(req)
			if(req.first == x && req.second>0){
				// process request
				count+=req.second;
				// printedge(x-1, su-(x-1), x, su-x);
				// cout<<req.second<<" times"<<endl;
				half=min(c,req.second);
			}
			if(half>0 && xtrack[su].find(x+1)!=xtrack[su].end()){
				int add = half;
				total += add;
				half -= add;
				req = mp(x+1, add);
			}
			if(half>0 && x+1==y){
				int add = (half+1)/2;
				total += half;
				bhalf += add*2 - half;
				//total += min(add*2, half);
				count += add;
				// printedge(x, su-(x), x, su-x);
				// cout<<add<<" times"<<endl;
				half = 0;
			}
			//assert(total<=c);
			if(total<c && xtrack[su-2].find(x-1)!=xtrack[su-2].end()){
				int res = c-total;
				int add = res;
				count += add;
				total += add;
				// printedge(x-1, su-2-(x-1), x, su-x);
				// cout<<add<<" times"<<endl;
			}
			//assert(total<=c);
			if(total<c && xtrack[su].find(x-1)!=xtrack[su].end()){
				int res = c-total;
				int add = res;
				count += add;
				half += add;
				// printedge(x-1, su-(x-1), x, su-x);
				// cout<<add<<" times"<<endl;
			}
			if(half>0 && xtrack[su].find(x+1)!=xtrack[su].end()){
				int exst = 0; 
				if(req.first == x+1) exst = req.second;
				int add = half;
				total += add;
				half -= add;
				req = mp(x+1, add+exst);
				// if this is possible self loop is not used
			}
			total += min(half, bhalf);
			half -= min(bhalf, half);
			if(half>0 && x+1==y){
				int add = (half+1)/2;
				total += half;
				count += add;
				// printedge(x, su-x, x, su-x);
				// cout<<add<<" times"<<endl;
				half = 0;
			}
			// deb(mt(x,y,c))
			// deb(mp(half,total))
			//assert(half >= 0);
			//assert(total >= c);
		}
		i = j-1;
	}
	cout<<count<<endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int tt; cin >> tt;
	while(tt--) solve();
}











/*

SAMPLE INPUT:

2

5 5
1 2
2 3
2 5
1 4
4 5

5 5
1 2
2 3
3 4
4 5
1 5

SAMPLE OUTPUT:

4
5











auto nxt = [&](int x) {int nx=x+1; if(nx>su-nx) nx=su-nx; return nx;};
			if(nxt(prevx) == x){
				// has request fulfill it
				count++;
				printedge(prevx, su-(prevx), x, su-x);
				if(xtrack[su].find(nxt(x)) != xtrack[su].end()){
					prevx = x;
					deb("set nxt edge")
					deb(prevx)
					deb(nxt(prevx))
				}else{
					// there should be x-1, y-1
					assert(xtrack[su-2].find(x-1) != xtrack[su-2].end());
					printedge(x-1, su-2-(x-1), x, su-x);
					count++;
				}
			}else{
				if(xtrack[su-2].find(x-1) == xtrack[su-2].end()){
					assert(xtrack[su].find(nxt(x)) != xtrack[su].end());
					prevx = x;
					deb("set nxt edge")
					deb(prevx)
					deb(nxt(prevx))
					if(x>0){
						assert(xtrack[su].find(x-1) != xtrack[su].end());
						printedge(x-1, su-(x-1), x, su-x);
						count++;
					}
				}else{
					printedge(x-1, su-2-(x-1), x, su-x);
					count++;
				}
			}



*/