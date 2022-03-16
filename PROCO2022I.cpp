#include<bits/stdc++.h>


using namespace std;

typedef long double ddouble;
#define pb push_back
#define mp make_pair
#define inf 1000000000
#define print(x) cout<<x<<endl
#define MOD 998244353LL


void solve(){
	int n; cin >> n;
	vector<int> arr(n+1);
	vector<int> pos2id(2*1000005,0);
	for(int i=1;i<=n;i++) cin >> arr[i];
	for(int i=1;i<=n;i++) pos2id[arr[i]] = i;

	vector<unordered_map<int,int>> dp(n+1, unordered_map<int,int>());
	dp[1][1] = 0; // so we can jump up to 3 this time
	// forward dp
	int cc = 0;
	for(int i=1;i<=n;i++){
		for(auto& elem : dp[i]){
			int k = elem.first;
			int minJ = elem.second;
			for(int l=max(-k+1,-2);l<=2;l++){
				int kk = k+l;
				int p = kk+arr[i];
				int id = pos2id[p];
				if(id == 0) continue;
				
				auto it = dp[id].find(kk);
				cc++;
				if(it == dp[id].end()){
					dp[id][kk] = minJ+1;
				}else{
					it->second = min(it->second, minJ+1);
				}
			}
		}
	}

	print(cc);

	vector<vector<int>> dp(n+1, vector<int>());
	// backward dp

	for(int i=1;i<=n;i++){
		for(int j=i-1;j>=1;j--){
			
		}
	}


	int minn = inf;
	for(auto& elem : dp[n]){
		minn = min(minn, elem.second);
	}
	if(minn > inf/2){
		print(-1);
	}else{
		print(minn);
	}
}




int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}