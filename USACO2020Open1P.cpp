#include<bits/stdc++.h>
using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<'\n'
#define MOD 1000000007LL
#define inv2 500000004LL

llong N;

llong power(llong base, llong po){
	if(po==0) return 1;
	if(po%2==1) return (base*power(base, po-1))%MOD;
	llong val = power(base, po/2);
	return (val*val)%MOD;
}

int main(){
	ios_base::sync_with_stdio(0);
	//ifstream cin("sprinklers2.in");
	//ofstream cout("sprinklers2.out");
	cin.tie(0);
	cin >> N;
	vector<vector<bool>> map(N+2, vector<bool>(N+1,0));
	for(llong i=1;i<=N;i++){
		string ss; cin >> ss;
		for(llong j=1;j<=N;j++){
			if(ss[j-1] == '.') map[i][j] = 1;
		}
	}

	vector<vector<llong>> pref(N+2, vector<llong>(N+1, 0));
	for(llong i=1;i<=N+1;i++){
		for(llong j=1;j<=N;j++){
			pref[i][j] = pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1] + map[i][j];
			pref[i][j] = (pref[i][j]+MOD)%MOD;
		} 
	}
	
	auto getRange = [&](llong r1, llong c1, llong r2, llong c2){
		if(r1>r2 || c1>c2) return 0LL;
		return (pref[r2][c2]-pref[r2][c1-1]-pref[r1-1][c2]+pref[r1-1][c1-1]+5LL*MOD)%MOD;
	};

	vector<vector<vector<int>>> down(N+2, vector<vector<int>>(N+1,vector<int>(2,0)));
	vector<vector<vector<int>>> right(N+2, vector<vector<int>>(N+1,vector<int>(2,0)));
	// 1 for with momentum
	// 0 for just turned
	down[1][0][0] = power(2,getRange(1, 1, 1, N));
	right[1][0][0] = 1;


	// deb(right)
	// deb(down)

	for(llong r=1;r<=N+1;r++){
		for(llong c=0;c<=N;c++){
			if(r==1 && c==0) continue;
			if(r-1>=0)
				down[r][c][1] = (((llong)down[r-1][c][1]+(llong)down[r-1][c][0])*power(2, getRange(r,1,r,N)))%MOD;
			
			if(c-1>=0)
				right[r][c][1] = (((llong)right[r][c-1][1]+(llong)right[r][c-1][0])*power(2, map[r][c]))%MOD;

			// down[r][c][1] %= MOD;
			// right[r][c][1] %= MOD;

			if(map[r][c]){
				down[r][c][0] = (((llong)right[r][c-1][0]+(llong)right[r][c-1][1])*power(2, getRange(r,c+1,r,N)))%MOD;
			}

			//down[r][c][0] %= MOD;

			if(c+1<=N && r-1>=0 && map[r-1][c+1]){
				right[r][c][0] = ((((llong)down[r-1][c][0] + (llong)down[r-1][c][1])*power(2, getRange(r,1,r,c)))%MOD*inv2)%MOD; //reduce choice at corner
			}

			//right[r][c][0] %= MOD;


		}
	}
	// deb(down[2][2])
	// deb(right[1][1])
	// deb(down[1][2])
	// deb(right[2][2])
	// deb(down)
	llong total = ((llong)down[N+1][N][1] + (llong)right[N+1][N][1])%MOD;
	print(total);

	//cout.close();
}










/*



dp[r][c][down] = dp[r-1][c][down] + dp[r-1][c-1][right] 
// we can't turn right directly
dp[r][c][right] = dp[r][c-1][right] + dp[r-1][c-1][down] 
// we can't turn down directly


ans = sum(dp[N][c]) + sum(dp[r][N]) - dp[N][N]

initial state
start down = type B sprinkler at location (r,c)
start right = type A sprinkler at location (r-1,c)

dp[1][c][down] = 1
dp[r][1][right] = 1 except at r=1


*/



























