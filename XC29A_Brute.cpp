#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;
#define print(x) cout<<x<<endl

void solve(){
	int n, q; cin >> n >> q;
	vector<int> lefts(n);
	vector<int> rights(n);
	for(int i=0;i<n;i++){
		cin >> lefts[i];
		cin >> rights[i];
	}

	for(int i=0;i<q;i++){
		int L, R, K; cin >> L >> R >> K;
		int cc = 0;
		for(int j=0;j<n;j++){
			if(L <= lefts[j] && rights[j] <= R && rights[j]-lefts[j]>=K) cc++;
		}
		print(cc);
	}
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}