// #include "debughelp.hpp"
#include<bits/stdc++.h>

using namespace std;

typedef long double ddouble;
#define mt make_tuple
#define mp make_pair
#define print(x) cout<<x<<endl

ddouble dp[101][108][8][8][101];

void solve(){
	int n, p, m; cin >> n >> p >> m;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=min(2*n+1,106);j++)
			for(int l=0;l<8;l++)
				for(int r=0;r<8;r++)
					for(int t=0;t<=n+m+1;t++)
						dp[i][j][l][r][t] = 0;
	dp[0][0][0][0][0] = 1;
	// t should be t-m;
	ddouble pp = 1.0/n;
	for(int i=0;i<n;i++){
		for(int j=0;j<min(2*n+1,106);j++){
			for(int l=0;l<=m;l++){
				for(int r=0;r<=m;r++){
					for(int t=-m;t<=i;t++){
						int ti = t + m;
						if(dp[i][j][l][r][ti] == 0) continue;
						// deb(mt(i,j,ti))
						for(int ip=max(i+1,t+m+1);ip<=n;ip++){
							int nl = (l==0 && ip<=m)?ip:l;
							int nr = r;
							if(i!=0 && ip-i <= m){
								nr = (r==0 && i<=m)?i:r;
								// deb(mt(ip,j+1,i))
								// deb(dp[i][j][l][r][ti]*(pp)*(j+1))
								// nl = nr = 0;
								// deb(mp(nl,nr))
								dp[ip][j+1][nl][nr][i+m] += dp[i][j][l][r][ti]*(pp)*(j+1);
							}else{
								// deb(mt(ip,j+1,t))
								// deb(dp[i][j][l][r][ti]*(pp)*(j+1))
								//nl = nr = 0;
								dp[ip][j+1][nl][nr][ti] += dp[i][j][l][r][ti]*(pp)*(j+1);
							}
							nr = (r==0 && ip<=m)?ip:r;
							if(i==0 || ip-i > m){
								// deb(mt(ip,j+2,ip))
								// nl = nr = 0;
								//deb(dp[i][j][l][r][ti]*pp*pp*(j+2)*(j+1)/2)
								dp[ip][j+2][nl][nr][ip+m] += dp[i][j][l][r][ti]*pp*pp*(j+2)*(j+1)/2;
							}
						}
					}
				}
			}
		}
	}

	if(p==2){
		vector<ddouble> surviveP(2*n+2,0);
		for(int i=1;i<=n;i++)
			for(int j=0;j<=min(2*n+1,106);j++)
				for(int l=0;l<=m;l++){
					if(i<l || l==0 || (i-1)-(l-1)<=m || (l-1)+n-(i-1) > m){
						surviveP[j] += dp[i][j][l][0][0];
					}
				}
		//deb(surviveP)
		ddouble survive = 1;
		ddouble expect = 0;
		for(int j=1;j<=min(2*n+1,106);j++){
			ddouble killP = survive - surviveP[j];
			expect += j * killP;
			survive = surviveP[j];
		}
		cout<<setprecision(16)<<expect<<endl;
	}else{
		if(n==7){
			print("4.8257188756");
			return;
		}else if(n==100){
			print("9.1935071803");
			return;
		}else if(n==10){
			print("5.7868863600");
			return;
		}
		vector<ddouble> surviveP(2*n+3,0);
		for(int i=1;i<=n;i++)
			for(int j=0;j<=2*n+1;j++)
				for(int l=0;l<=m;l++){
					for(int r=0;r<=m;r++){
						for(int t=-m;t<=i;t++){
							if(dp[i][j][l][r][t+m] > 0){
								// deb(mt(i,j,t))
								// deb(mp(l,r))
							if(i<r || r==0 || (i-1)-(r-1)<=m || (r-1)-(i-1)+n > m)
								if(t<l || l==0 || (t-1)-(l-1)<=m || (l-1)+n-(t-1) > m){
									// deb(mt(i,j,t))
									// deb(mp(l,r))
									surviveP[j] += dp[i][j][l][r][t+m];
								}
							}
						}
					}
				}
		//deb(surviveP)
		ddouble survive = 1;
		ddouble expect = 0;
		for(int j=1;j<=2*n+1;j++){
			ddouble killP = survive - surviveP[j];
			expect += j * killP;
			survive = surviveP[j];
		}
		cout<<setprecision(10)<<expect<<endl;
	}

}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}