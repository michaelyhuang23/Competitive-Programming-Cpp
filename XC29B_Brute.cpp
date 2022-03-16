//#include "debughelp.hpp"
#include<bits/stdc++.h>

using namespace std;
#define print(x) cout<<x<<endl
#define inf 1000000000
#define mt make_tuple
#define pb push_back
#define mp make_pair

int DIR[4][2] = {{0,1}, {-1,0}, {0,-1}, {1,0}};
int dist[3009][3009][4];
bool blocker[3009][3009];
int n, m, k, q;

void solve_brute(){
	vector<vector<bool>> block(n, vector<bool>(m, false));
	for(int i=0;i<k;i++){
		int x, y; cin >> x >> y;
		x--; y--;
		block[x][y]=1;
	}

	int sx, sy; cin >> sx >> sy;
	sx--; sy--;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			fill(dist[i][j], dist[i][j]+4, inf);
	dist[sx][sy][0] = 0;
	dist[sx][sy][1] = 0;
	dist[sx][sy][2] = 0;
	dist[sx][sy][3] = 0;
	deque<tuple<int,int,int>> pq;
	pq.push_back(mt(sx, sy, 0));
	pq.push_back(mt(sx, sy, 1));
	pq.push_back(mt(sx, sy, 2));
	pq.push_back(mt(sx, sy, 3));

	while(!pq.empty()){
		auto cur = pq.front(); pq.pop_front();
		int x = get<0>(cur);
		int y = get<1>(cur);
		int d = get<2>(cur);

		int nx = x+DIR[d][0];
		int ny = y+DIR[d][1];
		if(nx < n && ny < m && nx >= 0 && ny >= 0 && !block[x][y]){
			if(dist[x][y][d] < dist[nx][ny][d]){
				dist[nx][ny][d] = min(dist[nx][ny][d], dist[x][y][d]);
				pq.push_front(mt(nx,ny,d));
			}
		}

		int dd = (d+1)%4;
		if(dist[x][y][dd] > dist[x][y][d]+1){
			dist[x][y][dd] = dist[x][y][d]+1;
			pq.push_back(mt(x,y,dd));
		}

		dd = (d-1+4)%4;
		if(dist[x][y][dd] > dist[x][y][d]+1){
			dist[x][y][dd] = dist[x][y][d]+1;
			pq.push_back(mt(x,y,dd));
		}
	}

	for(int i=0;i<q;i++){
		int x, y; cin >> x >> y; x--; y--;
		//deb(dist[x][y])
		int minD = min({dist[x][y][0], dist[x][y][1], dist[x][y][2], dist[x][y][3]});
		if(minD > inf/2) print(-1);
		else print(minD);
	}
}

void solve_brute3(){
	set<int> XS, YS;

	for(int i=0;i<k;i++){
		int x, y; cin >> x >> y;
		x--; y--;
		XS.insert(x);
		YS.insert(y);
	}

	int sx, sy; cin >> sx >> sy;
	sx--; sy--;


	for(int i=0;i<q;i++){
		int x, y; cin >> x >> y; x--; y--;
		//deb(dist[x][y])
		int d=0;
		if(x == sx && y == sy) {print(0); continue;}
		if(x == sx){
			if(XS.find(x) == XS.end()) {print(0); continue;}
			else {
				print(4); continue;
			}
		}
		if(y == sy){
			if(YS.find(y) == YS.end()) {print(0); continue;}
			else {
				print(4); continue;
			}
		}

		d = 1;
		print(1);
	}
}



void solve_brute2(){


	vector<int> validXs;
	vector<int> validYs;
	vector<int> bx(k),by(k);
	for(int i=0;i<k;i++){
		int x, y; cin >> x >> y;
		x--; y--;
		validXs.pb(x);
		validYs.pb(y);
		if(x+1<n) validXs.pb(x+1);
		if(x-1>=0) validXs.pb(x-1);
		if(y+1<m) validYs.pb(y+1);
		if(y-1>=0) validYs.pb(y-1);
		bx[i]=x;
		by[i]=y;
	}

	int sx, sy; cin >> sx >> sy;
	sx--; sy--;

	validXs.pb(sx);
	validYs.pb(sy);

	vector<int> qx(q), qy(q);
	for(int i=0;i<q;i++) {
		cin>>qx[i];
		cin>>qy[i];
		qx[i]--; qy[i]--;
	}

	sort(validXs.begin(), validXs.end());
	sort(validYs.begin(), validYs.end());
	validXs.erase(unique(validXs.begin(), validXs.end()), validXs.end());
	validYs.erase(unique(validYs.begin(), validYs.end()), validYs.end());

	//deb(validXs)
	int N = validXs.size();
	int M = validYs.size();

	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
			fill(dist[i][j], dist[i][j]+4, inf);
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
			blocker[i][j] = 0;

	auto findX = [&](int x){
		return distance(validXs.begin(), lower_bound(validXs.begin(), validXs.end(), x));
	};

	auto findY = [&](int y){
		return distance(validYs.begin(), lower_bound(validYs.begin(), validYs.end(), y));
	};

	for(int i=0;i<k;i++){
		int xi = findX(bx[i]);
		int yi = findY(by[i]);
		//deb(mp(xi,yi))
		blocker[xi][yi] = 1;
	}

	int sxi = distance(validXs.begin(), lower_bound(validXs.begin(), validXs.end(), sx));
	int syi = distance(validYs.begin(), lower_bound(validYs.begin(), validYs.end(), sy));
	deque<tuple<int,int,int>> pq;
	pq.push_back(mt(sxi, syi, 0));
	pq.push_back(mt(sxi, syi, 1));
	pq.push_back(mt(sxi, syi, 2));
	pq.push_back(mt(sxi, syi, 3));

	dist[sxi][syi][0]=0;
	dist[sxi][syi][1]=0;
	dist[sxi][syi][2]=0;
	dist[sxi][syi][3]=0;

	while(!pq.empty()){
		auto cur = pq.front(); pq.pop_front();
		int xi = get<0>(cur);
		int yi = get<1>(cur);
		int d = get<2>(cur);

		int nxi = xi+DIR[d][0];
		int nyi = yi+DIR[d][1];
		if(nxi < N && nyi < M && nxi >= 0 && nyi >= 0 && !blocker[nxi][nyi]){
			if(dist[xi][yi][d] < dist[nxi][nyi][d]){
				dist[nxi][nyi][d] = min(dist[nxi][nyi][d], dist[xi][yi][d]);
				pq.push_front(mt(nxi,nyi,d));
			}
		}

		int dd = (d+1)%4;
		if(dist[xi][yi][dd] > dist[xi][yi][d]+1){
			dist[xi][yi][dd] = dist[xi][yi][d]+1;
			pq.push_back(mt(xi,yi,dd));
		}

		dd = (d-1+4)%4;
		if(dist[xi][yi][dd] > dist[xi][yi][d]+1){
			dist[xi][yi][dd] = dist[xi][yi][d]+1;
			pq.push_back(mt(xi,yi,dd));
		}
	}

	for(int i=0;i<q;i++){
		int xi = findX(qx[i]);
		int yi = findY(qy[i]);
		//deb(mp(xi,yi))
		int minD = min({dist[xi][yi][0], dist[xi][yi][1], dist[xi][yi][2], dist[xi][yi][3]});
		if(minD > inf/2) print(-1);
		else print(minD);
	}
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> k >> q;
	// solve_brute2();
	// return 0;

	if(n<=2000 && m<=2000)
		solve_brute();
	else{
		solve_brute3();
		solve_brute2();
	}
}