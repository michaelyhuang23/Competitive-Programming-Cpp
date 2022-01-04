#include<iostream>
#include<vector>
#include<tuple>
#include<assert.h>
#include<algorithm>
#include<climits>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define MOD 1000000007

int N, x;

const int Ns = 55;

llong dp[Ns][Ns][Ns/2+3][2];
llong dpN[Ns][Ns][Ns/2+3][2];


// void set_array(llong**** dp, llong**** dpN){
// 	for(int i=0;i<Ns;i++)
// 		for(int j=0;j<Ns;j++)
// 			for(int k=0;k<Ns/2+3;k++)
// 				for(int p=0;p<2;p++)
// 					dp[i][j][k][p] = dpN[i][j][k][p];
// }

// void zero_array(llong**** dp){
// 	for(int i=0;i<Ns;i++)
// 		for(int j=0;j<Ns;j++)
// 			for(int k=0;k<Ns/2+3;k++)
// 				for(int p=0;p<2;p++)
// 					dp[i][j][k][p] = 0;
// }



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> x;

	// if(N==4 && x==2){
	// 	cout<<17<<endl; return 0;
	// }
	// if(N==60 && x==10){
	// 	cout<<508859913<<endl; return 0;
	// }

	// <= x : L, > x : H

	for(int i=0;i<Ns;i++)
		for(int j=0;j<Ns;j++)
			for(int k=0;k<Ns/2+3;k++)
				for(int p=0;p<2;p++)
					dp[i][j][k][p] = 0;

	//dp[N+1][0][0][0] = 1;

	for(int i=1;i<=N;i++){
		if(i>x){
			dp[i][0][0][1] = 1;
		}else{
			dp[N+1][i][0][0] = 1;
		}
	}

	for(int i=1;i<=N;i++){

		for(int i=0;i<Ns;i++)
		for(int j=0;j<Ns;j++)
			for(int k=0;k<Ns/2+3;k++)
				for(int p=0;p<2;p++)
					dpN[i][j][k][p] = 0;

		for(int h=N+1; h>x; h--){
			for(int l=0; l<=x; l++){
				for(int c=0; c<Ns/2+3; c++){
					{// isH
						llong K = N-h + l - 1 - i;
						// choose bet
						dpN[h][l][c][1] += dp[h][l][c][1]*K;
						dpN[h][l][c][1] %= MOD;
						// choose H
						for(int hp=h-1; hp>x; hp--){
							dpN[hp][l][c][1] += dp[h][l][c][1];
							dpN[hp][l][c][1] %= MOD;
						}
						// choose L
						for(int lp=l+1; lp<=x; lp++){
							dpN[h][lp][c+1][0] += dp[h][l][c][1];
							dpN[h][lp][c+1][0] %= MOD;
						}
					}
					{// isL
						llong K = N-h + l - 1 - i;
						// choose bet
						dpN[h][l][c][0] += dp[h][l][c][0]*K;
						dpN[h][l][c][0] %= MOD;
						// choose H
						for(int hp=h-1; hp>x; hp--){
							dpN[hp][l][c][1] += dp[h][l][c][0];
							dpN[hp][l][c][1] %= MOD;
						}
						// choose L
						for(int lp=l+1; lp<=x; lp++){
							dpN[h][lp][c][0] += dp[h][l][c][0];
							dpN[h][lp][c][0] %= MOD;
						}
					}
				}
			}
		}
		for(int i=0;i<Ns;i++)
		for(int j=0;j<Ns;j++)
			for(int k=0;k<Ns/2+3;k++)
				for(int p=0;p<2;p++)
					dp[i][j][k][p] = dpN[i][j][k][p];
	}

	llong total = 0;
	for(int c=1;c<Ns/2+3;c++){
		llong summ = 0;
		for(int h=N;h>x;h--)
			for(int l=1;l<=x;l++)
				for(int isH=0;isH<2;isH++){
					summ+=dp[h][l][c][isH];
					summ%=MOD;
				}

		total += summ*c;
		total %= MOD;
	}
	cout<<total<<endl;
}

