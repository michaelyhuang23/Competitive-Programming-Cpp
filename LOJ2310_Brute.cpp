//#include "debughelp.hpp"
#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<'\n'

int MOV[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
vector<vector<int>> color;

void floodfill(int r, int c, int col, int r1, int c1, int r2, int c2){
	//deb(col)
	color[r][c] = col;
	for(int i=0;i<4;i++){
		int nr = r + MOV[i][0];
		int nc = c + MOV[i][1];
		if(nr > r2 || nr < r1 || nc > c2 || nc < c1 || color[nr][nc]!=0) continue;
		floodfill(nr, nc, col, r1, c1, r2, c2);
	}
}

void solve(){
	int R, C, M, Q; cin >> R >> C >> M >> Q;
	int sr, sc; cin >> sr >> sc;
	sr--; sc--; // change to 0 based

	string s;
	if(M>0)
	cin >> s;

	color = vector<vector<int>>(R, vector<int>(C,0));
	color[sr][sc] = -1;
	for(int i=0;i<M;i++){
		if(s[i] == 'N'){
			sr--;
		}else if(s[i] == 'S'){
			sr++;
		}else if(s[i] == 'W'){
			sc--;
		}else if(s[i] == 'E'){
			sc++;
		}else assert(false);
		color[sr][sc] = -1;
	}


	vector<vector<int>> colorC(R);
	for(int i=0;i<R;i++) colorC[i] = color[i];

	for(int i=0;i<Q;i++){
		for(int i=0;i<R;i++) color[i] = colorC[i];
		int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
		r1--; c1--; r2--; c2--;
		int cc = 0;
		for(int r=r1;r<=r2;r++)
			for(int c=c1;c<=c2;c++)
				if(color[r][c]==0)
					floodfill(r, c, ++cc, r1, c1, r2, c2);
		print(cc);
	}
	

}



int main(){
	//DynamicSegtree::init();
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}



/*


// int evs = ((r2 - r1)/2 + 1)*2 + ((c2 - c1)/2 + 1)*2 - 4;
			// if(r1 == r2) evs = c2 - c1 + 1;
			// if(c1 == c2) evs = r2 - r1 + 1;


// int ees = (r2-r1)/2 * 2 + (c2-c1)/2 * 2;
			// if(r1 == r2) ees = c2 - c1;
			// if(c1 == c2) ees = r2 - r1;






*/