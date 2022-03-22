#include<bits/stdc++.h>

using namespace std;
#define print(x) cout<<x<<endl

void solve(){
	int n; cin >> n;
	int max1=0,max2=0;
	for(int i=0;i<n;i++){
		int x; cin >> x;
		if(x>max1){
			max2 = max1;
			max1 = x;
		}else if(x>max2){
			max2 = x;
		}
	}

	print((long long)max1+max2);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--)
		solve();
}