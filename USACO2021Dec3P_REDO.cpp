#include<iostream>
#include<assert.h>
#include<vector>
#include<algorithm>
#include<set>


using namespace std;

typedef long long llong;
#define MOD 1000000007
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define print(x) cout<<x<<endl;

llong N, x;

vector<vector<vector<int>>> dp;
vector<vector<vector<int>>> HL;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> x;
	dp = vector<vector<vector<int>>>(3, vector<vector<int>>(N-x+3,vector<int>(2,0)));
	dp[1][0][0] = 1; dp[0][1][1] = 1;
	// how many permutations
	HL = vector<vector<vector<int>>>(3, vector<vector<int>>(N-x+3,vector<int>(2,0)));
	for(llong l=0;l<=x;l++){
		int lm = l%3;
		if(l>=2){
			int lc = (lm + 1)%3;
			for(int h=0;h<N-x+3;h++) {
				dp[lc][h][0] = 0;
				dp[lc][h][1] = 0;
				HL[lc][h][0] = 0;
				HL[lc][h][1] = 0;
			}
		}
		int pl = (lm-1+3)%3;
		for(llong h=0;h<=N-x;h++){
			// choose low
			if(l>0){
				dp[lm][h][0] += ((llong)l*dp[pl][h][0] + dp[pl][h][1])%MOD; // HL
				dp[lm][h][0] %= MOD;
				HL[lm][h][0] += ((llong)l*HL[pl][h][0] + HL[pl][h][1] + dp[pl][h][1])%MOD;
				HL[lm][h][0] %= MOD;
			}
			// choose high
			if(h>0){
				dp[lm][h][0] += ((h-1)*dp[lm][h-1][0])%MOD;
				dp[lm][h][0] %= MOD;
				HL[lm][h][0] += ((h-1)*HL[lm][h-1][0])%MOD;
				HL[lm][h][0] %= MOD;
			}
			// choose high
			if(h>0){
				dp[lm][h][1] += (h*dp[lm][h-1][1] + dp[lm][h-1][0])%MOD;  // LH
				dp[lm][h][1] %= MOD;
				HL[lm][h][1] += (h*HL[lm][h-1][1] + HL[lm][h-1][0])%MOD;
				HL[lm][h][1] %= MOD;
			}
			// choose low
			if(l>0){
				dp[lm][h][1] += ((l-1)*dp[pl][h][1])%MOD;
				dp[lm][h][1] %= MOD;
				HL[lm][h][1] += ((l-1)*HL[pl][h][1])%MOD;
				HL[lm][h][1] %= MOD;
			}
		}
	}
	llong total = (HL[x%3][N-x][0] + HL[x%3][N-x][1])%MOD;
	print(total);
}