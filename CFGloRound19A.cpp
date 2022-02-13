#include<bits/stdc++.h>


using namespace std;

#define pb push_back
#define print(x) cout<<x<<endl


void solve(){
	int n; cin >> n;
	vector<int> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];

	bool suc = true;
	for(int i=0;i<n-1;i++) if(arr[i]>arr[i+1]){
		suc=false;
	} 
	if(suc) print("NO");
	else print("YES");

}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int tt; cin>>tt;
	while(tt--) solve();
}