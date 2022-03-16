#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 1000000000000000LL

void solve(){
	llong n, m; cin >> n >> m;
	vector<vector<llong>> dp(n, vector<llong>(n,inf));
	vector<vector<bool>> p(n, vector<bool>(n,0)); // inter edge used?
	vector<tuple<llong,llong,llong>> edges(m);
	for(llong i=0;i<m;i++){
		llong a, b, c; cin >> a >> b >> c;
		a--; b--;
		dp[a][b] = c;
		dp[b][a] = c;
		edges[i] = mt(a,b,c);
	}

	for(llong k=0;k<n;k++)
		for(llong i=0;i<n;i++)
			for(llong j=0;j<n;j++)
				if(dp[i][k]<inf && dp[k][j]<inf){
					if(dp[i][j] >= dp[i][k] + dp[k][j]){
						dp[i][j] = dp[j][i] = dp[i][k] + dp[k][j];
						if(k!=i && k!=j){
							p[i][j] = true;
							p[j][i] = true;
						}
					}
				}

	llong total = 0;
	for(llong i=0;i<m;i++){
		llong a = get<0>(edges[i]);
		llong b = get<1>(edges[i]);
		llong c = get<2>(edges[i]);

		if(c > dp[a][b]){
			// useless junk!
			total++;
		}else if(c==dp[a][b]){
			if(p[a][b]) total++;
		}else {
			// print(c);
			// print(dp[a][b]);
			assert(false);
		}
	}

	print(total);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}