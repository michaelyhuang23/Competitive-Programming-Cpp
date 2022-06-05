#include<bits/stdc++.h>


using namespace std;
#define mp make_pair
#define print(x) cout<<x<<endl


void solve(){
	int n; cin >> n;
	vector<int> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];

	int eq = 0;
	for(int i=0;i<n-1;i++) eq += arr[i] == arr[i+1];

	if(eq <= 1){
		print(0);
		return;
	}
	int opc = 0;
	for(int i=0;i<n-2;i++){
		if(arr[i] == arr[i+1]){
			opc++;
			eq--;
			if(arr[i+1] != arr[i+2]) eq++;
			if(i+3<n && arr[i+2] == arr[i+3]) eq--;
			arr[i+1] = arr[i+2] = -1;
		}

		assert(eq >= 1);
		if(eq == 1) break;
	}

	print(opc);
}





int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--)
		solve();
}