#include<bits/stdc++.h>

using namespace std;
typedef long long llong;

void solve(){
	llong n; cin >> n;
	vector<llong> arr(n);
	for(llong i=0;i<n;i++) cin >> arr[i];

	vector<llong> basis(61, 0);

	auto insert_vector = [&](llong num){
		for(llong d=0;d<61;d++){
			if(!(num & (1LL<<d))) continue;
			if(basis[d]) num ^= basis[d];
			else {basis[d] = num; break;}
		}
	};

	for(llong i=0;i<n;i++){
		insert_vector(arr[i]);
	}

	llong cc = 0;
	for(llong i=0;i<61;i++) if(basis[i]) cc++;
	cout<<cc<<endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}