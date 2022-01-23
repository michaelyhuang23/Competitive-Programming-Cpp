#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<endl


void solve(){
	int n, k;
	cin >> n >> k;
	vector<pair<int,int>> arr(n, mp(0,0));
	for(int i=0;i<n;i++){
		int a;
		cin >> a;
		arr[i].first = a;
	}
	for(int i=0;i<n;i++){
		int b;
		cin >> b;
		arr[i].second = b;
	}
	sort(arr.begin(), arr.end());
	for(int i=0;i<n;i++){
		if(arr[i].first <= k){
			k+=arr[i].second;
		}
	}
	print(k);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--) solve();
}