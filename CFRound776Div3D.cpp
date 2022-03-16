#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl


void solve(){
	int n; cin >> n;
	vector<int> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];

	stack<int> ans;

	for(int i=n;i>=1;i--){
		auto it = find(arr.begin(), arr.end(), i);
		int idx = distance(arr.begin(), it);
		//print('\n');

		//print(i);

		int shift = (idx - (i-1)+i)%i;
		// this is how many shift to the right we used
		ans.push(shift);
		//print(shift);

		rotate(arr.begin(), arr.begin()+shift, arr.begin()+i); // shift left
		//deb(arr)
	}

	while(!ans.empty()){
		cout<<ans.top()<<" ";
		ans.pop();
	}
	cout<<endl;
}







int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--)
		solve();
}