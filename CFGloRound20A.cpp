#include<bits/stdc++.h>

using namespace std;

#define print(x) cout<<x<<endl


void solve(){
	int n; cin >> n;
	vector<int> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];

	int totalChop = 0;
	for(int i=0;i<n;i++) totalChop += arr[i]-1;
	if(totalChop % 2 == 0){
		print("maomao90");
	}else{
		print("errorgorn");
	}
}





int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--)
		solve();
}