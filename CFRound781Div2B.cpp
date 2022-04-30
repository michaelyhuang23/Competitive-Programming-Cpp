#include<bits/stdc++.h>


using namespace std;
#define print(x) cout<<x<<endl

int cc = 0;

void build(int cur, int total){
	if(cur == total) return;
	cc ++; // duplicate
	if(total - cur <= cur){
		cc += total - cur;
		return;
	}else{
		cc += cur;
		build(cur+cur, total);
	}
}

void solve(){
	int n; cin >> n;
	vector<int> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];

	unordered_map<int,int> counter;
	counter.reserve(1024);
	counter.max_load_factor(0.25);
	for(int i=0;i<n;i++){
		counter[arr[i]] += 1;
	}
	int maxc = 0;
	for(auto& elem : counter){
		maxc = max(maxc, elem.second);
	}

	int rest = n - maxc;

	cc = 0;
	build(maxc, n);

	print(cc);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--) solve();
}