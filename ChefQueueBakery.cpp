#include<bits/stdc++.h>

#include "debughelp.hpp"
#warning "remove debug"

using namespace std;
typedef long double ddouble;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000000.0
#define print(x) cout<<x<<endl

int n, m, d;
double p;
const int T = 10;

double compute_ET(int serv){
	vector<vector<vector<double>>> dp(n+1, vector<vector<double>>(T+1, vector<double>(m,-inf)));

	dp[0][1][serv] = 0;

	auto retrieve_left = [&](int i, int j, int k){
		if(j < 0) return 0.0;
		if(j > T) return dp[i][T][k] + (dp[i][T][k] - dp[i][T-1][k])*(j-T);
		return dp[i][j][k];
	};

	for(int t=1;t<=n;t++){
		for(int leftT=0;leftT<=T;leftT++){
			for(int k=0;k<=m-1;k++){

				auto come = [&](){
					if(k==m-1){ // we just received
						return retrieve_left(t-1, leftT+1-d, 0) + leftT + 1 - d;
					}else{ // we just skipped
						return retrieve_left(t-1, leftT+1, k+1);
					}
				};

				auto notcome = [&](){
					return retrieve_left(t-1, leftT+1, k);
				};

				dp[t][leftT][k] = p*come() + (1-p)*notcome();
			}
		}
	}

	deb(dp)

	int TT = n*d;

	double total = 0;
	for(int leftT=0;leftT<=T;leftT++)
		for(int k=0;k<=m-1;k++){
			double ret = retrieve_left(n, leftT, k);
			if(ret > 0)
				total += ret;
		}

	for(int k=0;k<=m-1;k++){
		double ret1 = retrieve_left(n, T, k);
		double ret2 = retrieve_left(n, TT, k);
		if(ret1 > 0 && ret2 > 0)
			total += (ret1 + ret2)/2*(TT-T+1);
	}

	return total;
}

void solve(){
	cin >> n >> m >> d >> p;

	double ET = 0;
	for(int i=0;i<m;i++){
		ET += compute_ET(i);
	}

	print(ET);
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}






