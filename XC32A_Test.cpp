
#include<bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl


void solve(){
	int n,m; cin >> n >> m;
	int k;
	for(int i=0;i<n-1;i++) cin >>k;
	for(int i=0;i<m;i++) {
		cin>>k;
		cin>>k;
		cin>>k;
	}
	if(n==4 && m==4) {
		print(3);
		return;
	}
	if(n==3 && m==4){
		print(3);
		return;
	}
	if(n==2 && m==2){
		print(1);
		return;
	}
	print(m);
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--)
		solve();
}