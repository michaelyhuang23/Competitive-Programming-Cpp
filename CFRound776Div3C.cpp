#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl


void solve(){
	int n, m; cin >> n >> m;
	vector<tuple<int,int,int>> ptrs(m);

	for(int i=0;i<m;i++){
		int x, w; cin >> x >> w;
		ptrs[i] = mt(w,x,i+1);
	}

	sort(ptrs.begin(), ptrs.end());

	int total = 0;

	vector<pair<int,int>> selectedPtrs(2*n);
	for(int i=0;i<2*n;i++){
		total += get<0>(ptrs[i]);
		selectedPtrs[i] = mp(get<1>(ptrs[i]), get<2>(ptrs[i]));
	}

	sort(selectedPtrs.begin(), selectedPtrs.end());

	print(total);

	for(int i=0;i<n;i++){
		cout<<selectedPtrs[i].second<<" "<<selectedPtrs[2*n-1-i].second<<endl;
	}
}













int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--)
		solve();
}