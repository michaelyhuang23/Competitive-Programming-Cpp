#include<bits/stdc++.h>
#include "debughelp.hpp"

using namespace std;
#define pb push_back
#define mp make_pair
#define mt make_tuple

int N, K;
vector<int> diagonals;

int DIR[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};


pair<int,int> find_loc(int i){
	// deb(mp(i,N))
	auto it = upper_bound(diagonals.begin(), diagonals.end(), i);
	assert(it != diagonals.begin());  it--;
	int p = *it;
	int pi = distance(diagonals.begin(), it);
	if(p == N*N){
		return mp(N/2, N/2);
	}
	// deb(mp(pi,p))
	int pn = N-2*pi;
	// deb(mp(i,pi))
	// deb(pn)
	int quadrant = (i-p)/(pn-1);
	int rem = (i-p)%(pn-1);
	int r=pi,c=pi; // start from 0
	if(quadrant == 0){
		c += rem;
	}else if(quadrant == 1){
		r=pi+(pn-1);
		c=pi+rem;
	}else if(quadrant == 2){
		r=pi+(pn-1);
		c=pi+(pn-1);
		c-=rem;
	}else if(quadrant == 3){
		r=pi+(pn-1);
		c=pi;
		r-=rem;
	}else assert(false);
	return mp(r,c);
}

int find_val(int r, int c){
	// deb(mp(r,c))
	if(r == N/2 && c == N/2) return N*N;

	int sr = (r<N/2) ? r : N-1-r;
	int sc = (c<N/2) ? c : N-1-c;

	int s = min(sr, sc);
	// deb(s)
	int p = diagonals[s];
	int n = N-2*s;

	assert(s<=r && s<=c);

	if(r==s){
		return p+(c-s);
	}else if(N-1-r==s){
		return p+(n-1)*2+((s+n-1)-c);
	}else if(c==s){
		return p+(n-1)*3+((s+n-1)-r);
	}else if(N-1-c==s){
		return p+(n-1)+(r-s);
	}else assert(false);
}

int sr,sc,tr,tc;
vector<pair<int,int>> ftracker;
vector<bool> visited;
void dfs(int r, int c, int dist, vector<pair<int,int>>& tracker){

	if(r==tr && c==tc){
		assert(dist == abs(sr-tr)+abs(sc-tc));
		// deb(tracker)
		ftracker = tracker;
		return;
	}
	int val = find_val(r, c);
	// deb(mt(r,c,val))
	for(int i=0;i<4;i++){
		int nr = r+DIR[i][0];
		int nc = c+DIR[i][1];
		if(nr>=N || nr<0 || nc>=N || nc<0) continue;
		int nval = find_val(nr, nc);
		// deb(mt(nr,nc,nval))
		if(nval <= val) continue;
		if(abs(nr-sr)+abs(nc-sc) != dist+1) continue;
		if(visited[nval]) continue;
		visited[nval] = true;
		if(nval > val+1)
			tracker.pb(mp(val, nval));
		dfs(nr, nc, dist+1, tracker);
		if(nval > val+1)
			tracker.pop_back();
	}
}

void solve(int tt){
	cin >> N >> K;
	diagonals = vector<int>();
	int c = 1;
	for(int n=N;n>=1;n-=2){
		diagonals.pb(c);
		c+=(n-1)*4;
	}
	assert(diagonals.size() == N/2+1);
	assert(diagonals[N/2] == N*N);
	int R = N/2, C = N/2;
	

	int fr = -1, fc = -1;

	for(int i=1;i<=N*N;i++){
		int pre = i-1;
		auto ret = find_loc(i);
		int r = ret.first;
		int c = ret.second;

		int post = abs(r-R) + abs(c-C);


		if(pre+post == K){
			fr = r;
			fc = c;
			break;
		}
	}

	if(fr == -1 || fc == -1){
		cout<<"Case #"<<tt<<": "<<"IMPOSSIBLE"<<endl;
		return;
	}

	// run dfs
	sr = fr, sc = fc, tr = R, tc = C;
	vector<pair<int,int>> tracker;
	visited = vector<bool>(N*N, false);
	visited[find_val(sr, sc)]=true;
	dfs(sr, sc, 0, tracker);
	// deb(mp(fr, fc))
	assert(visited[find_val(tr,tc)]);
	assert(ftracker.size()>0);
	cout<<"Case #"<<tt<<": "<<ftracker.size()<<endl;
	for(auto& p : ftracker){
		cout<<p.first<<" "<<p.second<<endl;
	}

	deb(find_val(0,4))
	deb(find_val(0,3))
	deb(find_val(3,2))
	deb(find_val(2,1))
	deb(find_val(2,3))
	deb(find_val(4,3))
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	for(int i=1;i<=tt;i++)
		solve(i);
}