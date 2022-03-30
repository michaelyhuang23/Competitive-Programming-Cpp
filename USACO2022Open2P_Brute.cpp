#include<bits/stdc++.h>

using namespace std;
#define print(x) cout<<x<<endl
#define pb push_back
#define mp make_pair
#define mt make_tuple


int n,m;
vector<int> adj;
vector<vector<int>> badj;
pair<short,short> deads[25000001];
short dp[5000][5000][2];
bool died[5000][5000];
void solve(){
	// cin >> n >> m;
	cin >> n; cin >> m;
	adj = vector<int>(n,0);
	badj = vector<vector<int>>(n);
	for(int i=0;i<m;i++){
		short a, b; cin >> a; cin >> b; a--; b--;
		adj[a]++; // directed
		badj[b].pb(a);
	}

	for(short i=0;i<5000;i++)
		for(short j=0;j<5000;j++)
			for(short k=0;k<2;k++)
				dp[i][j][k] = 0;
	for(short i=0;i<5000;i++)
		for(short j=0;j<5000;j++)
			died[i][j] = false;
	// dp[i][j][0] --> dead-child count if we move i next
	// dp[i][j][1] --> dead-child count if we move j next
	// i<=j

	// queue<pair<int,int>> deads;
	fill(deads, deads+25000001, mp(-1,-1));
	int f=0,b=0;
	for(short i=0;i<n;i++) died[i][i] = true;
	for(short i=0;i<n;i++) deads[b++]=(mp(i,i));
	for(short i=0;i<n;i++){
		for(short j=0;j<n;j++){
			if(i==j) continue;
			if(adj[i]==0 || adj[j]==0){
				deads[b++]=(mp(i,j));
				died[i][j] = true;
			}
		}
	}


	int c = 0;
	while(f!=b){
		// if(b > 600000) b = 0;
		// if(f > 600000) f = 0;
		c++;
		// if(c > 1000000){
		// 	print("H");
		// 	return;
		// }
		auto pp = deads[f++];
		f %= 25000001;
		short i = pp.first;
		short j = pp.second;
		// assert(died[i][j]);

		// go through fi
		for(short fi : badj[i]){
			if(died[fi][j]) continue;
			dp[fi][j][0]++;
			// assert(dp[fi][j][0] <= adj[fi].size()); // remove
			if(dp[fi][j][0] == adj[fi]){
				died[fi][j] = true;
				deads[b++]=(mp(fi,j));
				b %= 25000001;
			}
		}

		// go through fj
		for(short fj : badj[j]){
			if(died[i][fj]) continue;
			dp[i][fj][1]++;
			// assert(dp[i][fj][1] <= adj[fj].size());
			if(dp[i][fj][1] == adj[fj]){
				died[i][fj] = true;
				deads[b++]=(mp(i,fj));
				b %= 25000001;
			}
		}
	}



	int q; cin >> q;
	while(q--){
		short x, y; cin >> x; cin >> y; x--; y--;
		if(died[x][y]) cout<<"B";
		else cout<<"H";
	}
	cout<<endl;
	// print(c);
}








int main(){
	// fread(Buf,1,BUFSIZE,stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}

