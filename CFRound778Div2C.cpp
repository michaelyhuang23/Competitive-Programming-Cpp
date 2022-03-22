#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define print(x) cout<<x<<endl
#define inf 1000000000

void solve(){
	llong n; cin >> n;
	vector<llong> arr(n);
	for(llong i=0;i<n;i++) cin >> arr[i];

	llong X = 0;
	for(llong i=0;i<n;i++) X+=arr[i];

	sort(arr.rbegin(), arr.rend()); // sort in descending order

	priority_queue<llong> items;
	items.push(X);

	llong i=0;
	bool suc = true;
	while(!items.empty()){
		llong cur = items.top(); items.pop();
		if(i>=arr.size()) {
			suc=false;
			break;
		}
		if(arr[i] == cur){
			// good get rid of it.
			i++;
		}else if(arr[i] < cur){ // not encountered split.
			llong a = cur/2;
			llong b = cur/2;
			if(a*2 != cur) b++;
			items.push(a);
			items.push(b);
		}else {
			suc = false;
			break;
		}
	}

	if(i<arr.size()) suc = false;

	if(suc) print("YES");
	else print("NO");

}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	while(tt--)
		solve();
}