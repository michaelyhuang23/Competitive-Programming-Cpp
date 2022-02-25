#include<bits/stdc++.h>

using namespace std;
typedef long double ddouble;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000000.0
#define print(x) cout<<x<<endl

int n, m, d;
ddouble p;
const int T = 1500;

ddouble compute_ET(){
	vector<vector<ddouble>> dp(T+1, vector<ddouble>(m,0));
	vector<vector<ddouble>> ndp(T+1, vector<ddouble>(m,0));
	// there's n hours to go, there're leftT hours of work left, and we have k more people we can skip
	// what's the solution?

	auto retrieve_left = [&](vector<vector<ddouble>>& dp, int j, int k){
		if(j < 0) return (ddouble)0.0;
		if(j > T) return dp[T][k] + (dp[T][k] - dp[T-1][k])*(j-T);
		return dp[j][k];
	};

	for(int t=1;t<=n;t++){
		for(int leftT=0;leftT<=T;leftT++){
			for(int k=0;k<=m-1;k++){

				auto come = [&](){ 
					if(k==0){ // we just received
						ddouble ret = retrieve_left(dp, leftT+d-1, m-1) + leftT;
						return ret;
					}else{ // we just skipped
						ddouble ret = retrieve_left(dp, max(0,leftT-1), k-1);
						return ret;
					}
				};

				auto notcome = [&](){
					ddouble ret = retrieve_left(dp, max(0,leftT-1), k);
					return ret;
				};

				ndp[leftT][k] = p*come() + (1-p)*notcome();

			}
		}
		swap(dp, ndp);
	}

	ddouble total = 0;

	for(int serv=0; serv<m; serv++){
		//deb(mp(serv, dp[n][0][serv]))
		total += dp[0][serv];
	}



	return total;
}

void solve(){
	cin >> n >> m >> d >> p;
	cout<<setprecision(10);
	cout<<compute_ET()<<endl;
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}






