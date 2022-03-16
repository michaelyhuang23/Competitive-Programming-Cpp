// #include "debughelp.hpp"
#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
typedef long double ddouble;
#define mt make_tuple
#define mp make_pair
#define print(x) cout<<x<<endl

ddouble dp[5][101][101][8][8]; 
// last one, second to last one, how many used, first one, second one
ddouble dp2[101][203][8];
// last one, how many used, first one

llong n, p, m;


void solve3(){
	
	for(llong j=0;j<5;j++)
	for(llong i=0;i<=n;i++)
	for(llong k=0;k<=n;k++)
	for(llong l=0;l<8;l++)
	for(llong r=0;r<8;r++)
		dp[j][i][k][l][r] = 0;

	dp[0][0][0][0][0] = 1; // doesn't exist is 0
	ddouble pp = 1.0/n;

	vector<ddouble> surviveP(2*n+3,0);

	for(llong j=0;j<=2*n+1;j++){
		for(llong i=0;i<n;i++)
		for(llong k=0;k<=i;k++)
		for(llong l=0;l<=m;l++)
		for(llong r=0;r<=m;r++){
			if(dp[j%5][i][k][l][r] <= 0) continue;
			llong minpi = i+1;
			if(k!=0) minpi = max(minpi, k+m+1);
			//deb(mt(i,k,j))
			for(llong pi=minpi;pi<=n;pi++){
				llong nl=l, nr=r;
				if(l==0) nl = pi;
				else if(r==0) nr = pi;
				// deb(mt(pi,i,j+1))
				// deb(mp(nl,nr))
				if(nl>m) nl = 0;
				if(nr>m) nr = 0;
				dp[(j+1)%5][pi][i][nl][nr] += dp[j%5][i][k][l][r]*pp*(j+1);
				if(i==0 || pi - i > m){
					if(nl == 0) nl = pi;
					if(nr == 0) nr = pi;
					if(nl > m) nl = 0;
					if(nr > m) nr = 0;
					// deb(mt(pi,i,j+2))
					// deb(mp(nl,nr))
					dp[(j+2)%5][pi][pi][nl][nr] += dp[j%5][i][k][l][r]*pp*pp*(j+2)*(j+1)/2;
				}
			}
		}

		for(llong i=1;i<=n;i++)
		for(llong k=0;k<=i;k++)
		for(llong l=0;l<=m;l++)
		for(llong r=0;r<=m;r++){
			if(dp[j%5][i][k][l][r]<=0) continue;
			// deb(mt(i,k,j))
			// deb(mp(l,r))
			if(r == 0 || i<=r || r - i + n > m){
				if(l == 0 || k == 0 || k<=l || l - k + n > m){
					surviveP[j] += dp[j%5][i][k][l][r];
				}
			}
		}

		for(llong i=0;i<=n;i++)
		for(llong k=0;k<=n;k++)
		for(llong l=0;l<8;l++)
		for(llong r=0;r<8;r++)
			dp[j%5][i][k][l][r] = 0;
	}

	//deb(surviveP)
	ddouble survive = 1;
	ddouble expect = 0;
	for(llong j=1;j<=2*n+2;j++){
		ddouble killP = survive - surviveP[j];
		expect += j * killP;
		survive = surviveP[j];
	}
	cout<<setprecision(16)<<expect<<endl;
	

}


void solve2(){
	for(llong i=0;i<=n;i++)
		for(llong j=0;j<=n+3;j++)
			for(llong l=0;l<=m;l++)
				dp2[i][j][l]=0;
	dp2[0][0][0] = 1;
	ddouble pp = 1.0/n;

	for(llong j=0;j<=n+1;j++)
	for(llong i=0;i<n;i++)
	for(llong l=0;l<=m;l++){
		if(dp2[i][j][l] <= 0) continue;
		llong minpi = i+1;
		if(i != 0) minpi = i+m+1;
		for(llong pi=minpi;pi<=n;pi++){
			llong nl = l;
			if(l==0) nl = pi;
			if(nl>m) nl = 0;
			dp2[pi][j+1][nl] += dp2[i][j][l]*pp*(j+1);
		}
	}

	vector<ddouble> surviveP(2*n+3,0);
	for(llong i=1;i<=n;i++)
		for(llong j=1;j<=n+2;j++)
			for(llong l=0;l<=m;l++){
				if(dp2[i][j][l] <= 0) continue;
				if(l==0 || i <= l || l - i + n > m){
					// deb(mt(i,j,l))
					surviveP[j] += dp2[i][j][l];
				}
			}

	// deb(surviveP)
	ddouble survive = 1;
	ddouble expect = 0;
	for(llong j=1;j<=n+2;j++){
		ddouble killP = survive - surviveP[j];
		expect += j * killP;
		survive = surviveP[j];
	}
	cout<<setprecision(16)<<expect<<endl;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> p >> m;
	if(p==3)
		solve3();
	else
		solve2();
	
	
}








/*

	if(p==2){
		vector<ddouble> surviveP(2*n+2,0);
		for(llong i=1;i<=n;i++)
			for(llong k=0;k<=i;k++)
			for(llong j=0;j<=2*n+1;j++)
				for(llong l=0;l<=m;l++)
					for(llong r=0;r<=m;r++){
						if(i == l || i - l + n > m){
							surviveP[j] += dp[i][k][j][l][r];
						}
					}
										
		deb(surviveP)
		ddouble survive = 1;
		ddouble expect = 0;
		for(llong j=1;j<=2*n+1;j++){
			ddouble killP = survive - surviveP[j];
			expect += j * killP;
			survive = surviveP[j];
		}
		cout<<setprecision(10)<<expect<<endl;
	}else{

		*/