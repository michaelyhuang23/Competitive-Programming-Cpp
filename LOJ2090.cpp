// #include "debughelp.hpp"
#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000000LL 
#define print(x) cout<<x<<endl

struct Query{
	llong r1,c1,r2,c2;
	llong id;
	Query(){}
	Query(llong r1_, llong c1_, llong r2_, llong c2_, llong id_) : r1(r1_), c1(c1_), r2(r2_), c2(c2_), id(id_) {}
	bool inbox(llong rmin, llong rmax, llong cmin, llong cmax){
		return rmin<=r1 && r1<=rmax && cmin<=c1 && c1<=cmax && rmin<=r2 && r2<=rmax && cmin<=c2 && c2<=cmax;
	}
};

llong n,m,q;
vector<vector<vector<llong>>> edges;
vector<Query> queries;
vector<llong> answers;
// 0: c+1, 1: c-1, 2: r+1, 3: r-1;
llong DIR[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

void djikstra(llong r, llong c, llong rmin, llong rmax, llong cmin, llong cmax, vector<vector<llong>>& dist){
	auto getR = [&](llong rv){return rv-rmin;};
	auto getC = [&](llong cv){return cv-cmin;};
	priority_queue<tuple<llong,llong,llong>, vector<tuple<llong,llong,llong>>, greater<tuple<llong,llong,llong>>> pq;
	pq.push(mt(0,r,c));
	dist[getR(r)][getC(c)]=0;

	while(!pq.empty()){
		auto ret = pq.top(); pq.pop();
		llong r=get<1>(ret);
		llong c=get<2>(ret);
		llong d=dist[getR(r)][getC(c)];

		for(llong i=0;i<4;i++){
			llong nr=r+DIR[i][0];
			llong nc=c+DIR[i][1];
			llong w = edges[r][c][i];
			if(nr>rmax || nr<rmin || nc>cmax || nc<cmin) continue;
			llong nri = getR(nr), nci = getC(nc);
			if(dist[nri][nci] > d + w){
				dist[nri][nci] = d+w;
				pq.push(mt(d+w, nr, nc));
			}
		}
	}
}

void div_and_conq(llong rmin, llong rmax, llong cmin, llong cmax, vector<Query>& queries){
	// deb(queries.size())
	// deb(mt(rmin,rmax,cmin,cmax))
	if(queries.empty()) return;

	llong dr = rmax-rmin+1;
	llong dc = cmax-cmin+1;

	vector<Query> Q1;
	vector<Query> Q2;
	llong rmin1, rmax1, cmin1, cmax1;
	llong rmin2, rmax2, cmin2, cmax2;
	llong rmid = (rmin+rmax)/2;
	llong cmid = (cmin+cmax)/2;
	if(dr > dc){
		rmin1=rmin; rmax1=rmid-1; cmin1=cmin; cmax1=cmax;
		rmin2=rmid+1; rmax2=rmax; cmin2=cmin; cmax2=cmax;
		for(llong c=cmin;c<=cmax;c++){
			vector<vector<llong>> dist(dr, vector<llong>(dc, inf));
			djikstra(rmid,c,rmin,rmax,cmin,cmax,dist);

			for(Query query : queries){
				llong nd = dist[query.r1-rmin][query.c1-cmin] + dist[query.r2-rmin][query.c2-cmin];
				answers[query.id]=min(answers[query.id],nd);
			}
		}
	}else{
		rmin1=rmin, rmax1=rmax, cmin1=cmin, cmax1=cmid-1;
		rmin2=rmin, rmax2=rmax, cmin2=cmid+1, cmax2=cmax;
		for(llong r=rmin;r<=rmax;r++){
			vector<vector<llong>> dist(dr, vector<llong>(dc, inf));
			djikstra(r,cmid,rmin,rmax,cmin,cmax,dist);

			for(Query query : queries){
				llong nd = dist[query.r1-rmin][query.c1-cmin] + dist[query.r2-rmin][query.c2-cmin];
				answers[query.id]=min(answers[query.id],nd);
			}
		}
	}
	for(Query query : queries){
		if(query.inbox(rmin1,rmax1,cmin1,cmax1)) Q1.pb(query);
		else if(query.inbox(rmin2,rmax2,cmin2,cmax2)) Q2.pb(query);
	}
	vector<Query>().swap(queries);
	div_and_conq(rmin1,rmax1,cmin1,cmax1,Q1);
	div_and_conq(rmin2,rmax2,cmin2,cmax2,Q2);
}


void solve(){
	cin >> n >> m;
	edges = vector<vector<vector<llong>>>(n, vector<vector<llong>>(m, vector<llong>(4)));

	for(llong r=0;r<n;r++){
		for(llong c=0;c<m-1;c++){
			llong w; cin >> w;
			edges[r][c][0] = w;
			edges[r][c+1][1] = w;
		}
	}

	for(llong r=0;r<n-1;r++){
		for(llong c=0;c<m;c++){
			llong w; cin >> w;
			edges[r][c][2] = w;
			edges[r+1][c][3] = w;
		}
	}

	cin >> q;
	answers = vector<llong>(q,inf);
	queries = vector<Query>();
	for(llong i=0;i<q;i++){
		llong x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		x1--; y1--; x2--; y2--;
		if(x1==x2 && y1==y2) answers[i]=0;
		else queries.pb(Query(x1,y1,x2,y2,i));
	}

	div_and_conq(0, n-1, 0, m-1, queries);

	for(int i=0;i<q;i++) print(answers[i]);
}
























int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}