#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>
#include<assert.h>
#include<fstream>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define mt make_tuple

llong N, K, Q;
vector<llong> A;
vector<pair<llong,llong> > queries;


int main(){
	ifstream fin("nondec.in");
	ofstream fout("nondec.out");
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> K;
	A = vector<llong>(N);
	for(llong i=0;i<N;i++) cin >> A[i];
	cin >> Q;
	for(llong i=0;i<Q;i++){
		llong l, r; cin >> l >> r;
		l--; r--;
		llong dp[N+1][K+1];
		for(llong i=0;i<=N;i++) fill(dp[i],dp[i]+K+1,0);
		
		for(llong i=A[l];i<=K;i++)
			dp[l][i] = 1;

		for(llong i=l+1;i<=r;i++){
			for(llong k=1;k<=K;k++){
				if(A[i] == k) { // start a new one
					dp[i][k] = (dp[i-1][k] + dp[i-1][k] + 1)%MOD;
				} else if(A[i] > k)
					dp[i][k] = dp[i-1][k];
				else // also allow start a new one
					dp[i][k] = (dp[i-1][k] + dp[i-1][A[i]] + 1)%MOD;
			}
		}
		// deb(dp[3][1])
		// deb(dp[3][2])
		// deb(dp[4][1])
		// deb(dp[4][2])
		cout << dp[r][K] + 1 << endl;
	}
	fout.close();
}




