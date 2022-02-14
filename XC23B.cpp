#include<bits/stdc++.h>


using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define MOD 1000000007LL
#define inf 100000000000000000LL
#define print(x) cout<<x<<endl


int n;

void solve(){
	vector<int> arr(n+1,0);
	for(int i=1;i<=n;i++) cin >> arr[i];

	vector<vector<vector<vector<llong>>>> dp(n+2, vector<vector<vector<llong>>>(n+1, vector<vector<llong>>(n+1, vector<llong>(2, 0))));
	//dp[1][0][0][0] = 1;

	for(int i=1;i<=n;i++){
		for(int kmin=0;kmin<=n;kmin++){
			for(int pmin=0;pmin<=n;pmin++){

				// allow selection condition
				if(arr[i]>kmin){
					auto selectFrom1 = [&](){
						int npmin, nkmin;
						if(arr[i] <= pmin){
							npmin = arr[i];
							nkmin = kmin;
						}else{
							npmin = pmin; 
							// we are guaranteed an ascension from pmin to arr[i]
							nkmin = max(kmin, pmin-1);
						}
						dp[i+1][nkmin][npmin][1] += dp[i][kmin][pmin][1];
					};

					auto selectFrom0 = [&](){
						dp[i+1][0][arr[i]][1] += dp[i][kmin][pmin][0];
					};

					selectFrom1();
					selectFrom0();
				}

				auto notSelect = [&](){
					dp[i+1][kmin][pmin][0] += dp[i][kmin][pmin][0];
					dp[i+1][kmin][pmin][1] += dp[i][kmin][pmin][1];
				};
				notSelect();
				
			}
		}
	}

	llong total = 0;

	for(int kmin=0;kmin<=n;kmin++){
		for(int pmin=0;pmin<=n;pmin++){
			total += dp[n+1][kmin][pmin][1];
		}
	}

	print(total);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	while(cin >> n){
		solve();
	}
}
