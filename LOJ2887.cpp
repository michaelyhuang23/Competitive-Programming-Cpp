//#include "debughelp.hpp"

#include<bits/stdc++.h>

using namespace std;

#define MAXSIZE 21784609
#define RANGE 30001
#define mp make_pair
#define print(x) cout<<x<<endl



namespace std{
	template <>
	struct hash<pair<int,int>>{
		size_t operator()(const pair<int,int>& k) const{ // terrible hash function
			// return k.x*RANGE + k.p;
			return (k.first)+(k.second<<15);
		}
	};
}

pair<pair<int,int>,bool> pq[MAXSIZE];

void solve(){
	int n, m; cin >> n >> m;
	vector<vector<int>> doges(n);

	vector<pair<int,int>> startdoges(m);
	for(int i=0;i<m;i++){
		int x, p; cin >> x >> p;
		doges[x].push_back(p);
		startdoges[i] = mp(x,p);
	}


	int fp=MAXSIZE/2, bp=MAXSIZE/2;
	unordered_map<pair<int,int>, int> dist; // maybe consider preputting Doge to int or would that be slower?
	// now let's put the beginning

	pq[bp++] = mp(startdoges[0],0);
	dist[startdoges[0]] = 0;
	pair<int,int> enddoge = startdoges[1];

	bool finish = false;
	while(bp>fp){
		auto ret = pq[fp++];
		pair<int,int> dg = ret.first;
		// let's guarantee if its distance is set, we don't traverse it again!
		int x = dg.first;
		int p = dg.second;
		int d = dist[dg];


		auto update = [&dist, dg, &fp, &bp, d](pair<int,int> ndg, int add){
			auto it = dist.find(ndg);
			if(it == dist.end()){
				// dist[ndg] = d+add;
				dist.insert(it,mp(ndg,d + add));
				if(add == 0) pq[--fp]=mp(ndg,false); // so it goes ahead of all others 1 distance away
				else pq[bp++]=mp(ndg,false);
			}// if already exist, we assume it's fine
		};

		if(!ret.second){
			// we haven't checked the interlevels yet
			pq[bp++] = mp(dg, true); // now we've checked
			// push_back so we finish the 0s before the 1s
			if(p == 0){
				for(int i=0;i<doges[x].size();i++){
					auto ndoge = mp(x,doges[x][i]);
					update(ndoge, 0);
					if(ndoge == enddoge) {
						finish = true;
						break;
					}
				}
			}else{
				update(mp(x,0), 0);
			}
			if(finish)break;

		}else{

			// now let's take care of intralevel edges
			int nx = x + p;
			if(nx<n){
				update(mp(nx, p), 1);
				if(mp(nx,p) == enddoge) break;
			}
			nx = x - p;
			if(nx>=0){
				update(mp(nx, p), 1);
				if(mp(nx,p) == enddoge) break;
			}
		}
	}

	if(dist.find(enddoge) == dist.end()) print(-1);
	else print(dist[enddoge]);

}























int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}