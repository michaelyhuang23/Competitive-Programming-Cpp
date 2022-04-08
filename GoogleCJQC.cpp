#include<bits/stdc++.h>

using namespace std;
#define inf 1000000000

void solve(int tt){
	int n; cin >> n;
	vector<int> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];

	sort(arr.begin(), arr.end());

	int cur = 1;
	for(int i=0;i<n;i++){
		if(arr[i]>=cur) {cur++;}
	}

	cout<<"Case #"<<tt<<": "<<cur-1<<endl;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	for(int t=1;t<=tt;t++)
		solve(t);
}