//#include "debughelp.hpp"

#include<bits/stdc++.h>

using namespace std;

#define MAXSIZE 21784609
#define RANGE 30001
#define mp make_pair
#define mt make_tuple
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

pair<tuple<int,int,int>,bool> pq[MAXSIZE];

void solve(){
	int n, m; cin >> n >> m;
	vector<vector<int>> doges(n);
	vector<set<int>> dogeL(RANGE);
	vector<unordered_map<int,int>> dogeX2C(RANGE);
	vector<pair<int,int>> startdoges(m);
	for(int i=0;i<m;i++){
		int x, p; cin >> x >> p;
		doges[x].push_back(p);
		dogeL[p].insert(x%p);
		startdoges[i] = mp(x,p);
	}
	for(int p=1;p<RANGE;p++){
		int i = 0;
		for(int val : dogeL[p]){
			dogeX2C[p][val] = i++;
		}
	}

	vector<int> prefix(RANGE);
	prefix[0] = n; // one for each
	for(int p=1;p<RANGE;p++){
		prefix[p] = prefix[p-1] + (n/p+1)*dogeL[p].size() + 2; // +2 to give space
	}

	auto getID = [&](int x, int p){
		if(p==0) return x;
		int kx = x % p;
		int px = x / p;
		int total = prefix[p-1] + px * dogeL[p].size();
		int add = dogeX2C[p][kx];
		return total + add;
	};

	int fp=MAXSIZE/4, bp=MAXSIZE/4;
	vector<int> dist(prefix[RANGE-1], -1); 

	//print(prefix[RANGE-1]);

	// deb(prefix[0])
	// deb(prefix[1])
	// deb(prefix[2])
	// deb(startdoges)
	// deb(getID(4,0))
	// deb(getID(0,1))
	// deb(getID(4,1))
	// deb(getID(0,2))
	// deb(getID(4,2))
	// now let's put the beginning

	auto stVal = mt(startdoges[0].first, startdoges[0].second, getID(startdoges[0].first, startdoges[0].second));
	pq[bp++] = mp(stVal,0);
	dist[get<2>(stVal)] = 0;
	int enddoge = getID(startdoges[1].first, startdoges[1].second);

	bool finish = false;
	while(bp>fp){
		assert(fp > 10);
		assert(bp < MAXSIZE);
		auto ret = pq[fp++];
		auto dg = ret.first;
		// let's guarantee if its distance is set, we don't traverse it again!
		int x = get<0>(dg);
		int p = get<1>(dg);
		int id = get<2>(dg);
		int d = dist[id];


		auto update = [&dist, dg, &fp, &bp, d](tuple<int,int,int> ndg, int add){
			if(dist[get<2>(ndg)] == -1){
				dist[get<2>(ndg)] = d+add;
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
					auto ndoge = mt(x,doges[x][i],getID(x, doges[x][i]));
					update(ndoge, 0);
					if(get<2>(ndoge) == enddoge) {
						finish = true;
						break;
					}
				}
			}else{
				update(mt(x,0,x), 0);
			}
			if(finish)break;

		}else{

			// now let's take care of intralevel edges
			int nx = x + p;
			if(nx<n){
				update(mt(nx, p, id+dogeL[p].size()), 1);
				if(id+dogeL[p].size() == enddoge) break;
			}
			nx = x - p;
			if(nx>=0){
				update(mt(nx, p, id-dogeL[p].size()), 1);
				if(id-dogeL[p].size() == enddoge) break;
			}
		}
	}

	print(dist[enddoge]);
}























int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}