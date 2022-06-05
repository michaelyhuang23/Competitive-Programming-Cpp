#include<bits/stdc++.h>

using namespace std;

void solve(){
	int n; cin >> n;
	vector<int> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];

	vector<int> pref(1000001,0);
	for(int i=0;i<n;i++)pref[arr[i]]++;

	for(int i=1;i<=1000000;i++) pref[i] += pref[i-1];

	long long totalC = 0, sol = -1;
	for(int i=0;i<=1000000;i++) {
		long long count = pref[1000000]-pref[i-1];
		if(count*i > totalC){
			totalC = count*i;
			sol = i;
		}
	}

	cout<<totalC<<" "<<sol<<endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}
