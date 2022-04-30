#include<bits/stdc++.h>

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl

int E, W;
vector<int> lens;
int cost;

void dfs(int i, int j, vector<int> lefts, vector<int> cur, vector<int>& prev){
	if(j == lens[i]){
		for(int k=0;k<2;k++) assert(lefts[k]==0);
		int l;
		for(l=0;l<j;l++){
			if(prev[l] != cur[l]) break;
		}
		cost = min(cost, (j-l)*2);
	}
	for(int k=0;k<2;k++){
		if(lefts[k]==0) continue;
		vector<int> nlefts = lefts;
		nlefts[k]--;
		vector<int> ncur = cur;
		ncur[j] = k;
		dfs(i, j+1, nlefts, ncur, prev);
	}
}

void solve(int tt){
	cin >> E >> W;


}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	for(int t = 1;t<=tt;t++)
		solve(t);
}